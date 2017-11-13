/**
 * @file FCore.hpp
 * @brief Core functionality of the F-Wave solver
 */

#ifndef FCORE_HPP_
#define FCORE_HPP_

#include <cmath>
#include <assert.h>
#include <stdio.h>
#include <cstdlib>
#include <algorithm>
#include "FStructs.hpp"
#include "FConst.hpp"
#include "FCalc.hpp"

/**
 * @brief The F-Wave solver
 */
namespace solver
{

    /**
     * @brief Static implementation of the F-Wave solver
     * 
     * This class provides the necessary functionality to compute the left and right going net-updates 
     *      and wave speeds of the left and right going waves given the left and right state.
     */
    class FCore
    {

    public:
        
        /**
         * @brief Static method that computes the Roe eigenvalues in terms of the left and right quantities
         * 
         * Compute Roe eigenvalues to approximate wave speeds using solver::FCalc::avg_particle_velocity and solver::FCalc::avg_height
         * @f[ \lambda_{1,2}^{Roe}(q_l, q_r) = u^{Roe}(q_l, q_r) \pm \sqrt{gh^{Roe}(q_l, q_r)} @f]
         */
        static vector2 compute_eigenvalues(vector2 ql, vector2 qr)
        {
            double lambda_sqrt = sqrt(G_CONST * FCalc::avg_height(ql, qr)); //Calculate square root in definition of lambdas
            double avg_v = FCalc::avg_particle_velocity(ql, qr); //Compute average velocity
            return {avg_v - lambda_sqrt, avg_v + lambda_sqrt};
        };

        /**
         * @brief Static method that computes the resulting net-updates and wave speeds from the left and right state as described in @cite bale2002wave and @cite leveque2002finite
         * 
         * Using the intermediate computations for the eigenvectors using the eigenvalues computed with solver::FCore::compute_eigenvalues
         * 
         * @f[ r_{1,2}^{Roe} = \begin{bmatrix} 1 \\ \lambda_{1,2}^{Roe} \end{bmatrix} @f]
         * And the jump in the difference in the flux function and waves using solver::FCalc::flux
         * @f[ \Delta f = f(q_r) - f(q_l) @f] 
         * And the coefficients of this jump using another representation of the flux difference
         * @f[ 
         *      \alpha = {\begin{bmatrix} 1 & 1 \\ \lambda_1^{Roe} & \lambda_2^{Roe} \end{bmatrix}}^{-1} \Delta f 
         *      = \frac{1}{\lambda_2^{Roe} - \lambda_1^{Roe}} \begin{bmatrix} f_1 \lambda_2^{Roe} - \Delta f_2 \\ \Delta f_2 - \Delta f_1 \lambda_1^{Roe} \end{bmatrix}
         * @f]
         * Incorporating the baythymetry term computed with solver::FCalc::bathymetry
         * @f[ \Delta f = \sum_{p=1}^2 Z_p + \Delta x \Psi_{i-1/2} = \sum_{p=1}^2 \alpha_p r_p + \Delta x \Psi_{i-1/2} @f]
         * Compute the net-updates by accumulating the waves
         * @f[ A^{\mp}\Delta Q = \sum_{p: \{ \lambda_p^{Roe} \lessgtr 0 \}} Z_p \equiv @f]
         * @f[ 
         *      A^{-}\Delta Q \mathrel{+}= \begin{cases} 
         *          \alpha_1 r_1 & \text{for } \lambda_1^{Roe} < 0 \\
         *          \alpha_2 r_2 & \text{for } \lambda_2^{Roe} < 0 
         *      \end{cases} 
         *      \text{   and   }
         *      A^{+}\Delta Q\ \mathrel{+}= \begin{cases} 
         *          \alpha_1 r_1 & \text{for } \lambda_1^{Roe} > 0 \\
         *          \alpha_2 r_2 & \text{for } \lambda_2^{Roe} > 0 
         *      \end{cases} 
         * @f]
         * 
         * @param ql The left state
         * @param qr The right state
         * 
         * @return The resulting net-updates and wave speeds
         */
        static fresult compute_netupdates(vector2 ql, vector2 qr, double bl, double br)
        {
            //Special case, where inputs are zero or heights are equal and wave speed is zero
            if(ql.x1 < ZERO_PRECISION && ql.x2 < ZERO_PRECISION && qr.x1 < ZERO_PRECISION && qr.x2 < ZERO_PRECISION
            || ql.x1 - qr.x1 < ZERO_PRECISION && ql.x2 < ZERO_PRECISION && qr.x2 < ZERO_PRECISION)
               return {0.0, 0.0, {0.0, 0.0}, {0.0, 0.0}}; //Return output struct, where all values are zero 
            assert(FCalc::avg_height(ql, qr) >= 0); //Assert avg_height(ql, qr) is positive

            //Check dry cells: Reflecting boundary conditions
            if(ql.x1 < ZERO_PRECISION)       //Left cell dry: h==0
            {
                qr.x1 = ql.x1;      //h_r = h_l
                qr.x2 = -ql.x2;     //hu_l = -hu_r
                br = bl;            //b_r = b_l
            }
            else if(qr.x1 < ZERO_PRECISION) //Right cell dry: h==0
            {
                ql.x1 = qr.x1;      //h_l = h_r
                ql.x2 = -qr.x2;     //hu_r = -hu_l
                bl = br;            //b_l = b_r
            }

            vector2 eigenvalues = compute_eigenvalues(ql, qr); //Compute Roe eigenvalues
            assert(std::abs(eigenvalues.x2 - eigenvalues.x1) > ZERO_PRECISION); //Assert lambda_2 - lambda_1 != 0 (potential division by zero) 
            
            fresult res = {eigenvalues.x1, eigenvalues.x2, {0}, {0}}; //initialise result struct
            vector2 r1 = {1, res.lambda_1}; //Create r_1 vector
            vector2 r2 = {1, res.lambda_2}; //Create r_2 vector
            vector2 delta_f = FCalc::flux(qr).substract(FCalc::flux(ql)); //calculate flux delta
            
            delta_f = FCalc::bathymetry(delta_f, bl, br, ql.x1, qr.x1); // calculate bathymetry here

            vector2 alpha = { //Calculate eigencoefficients with the inverse of the eigenvalue matrix
                ((delta_f.x1 * res.lambda_2) - delta_f.x2),
                (delta_f.x2 - (delta_f.x1 * res.lambda_1))
            };
            alpha = alpha.divide(res.lambda_2 - res.lambda_1);

            if(res.lambda_1 < 0) //In case lambda_1 is negative, assign AdQ appropriately
                res.adq_negative = res.adq_negative.add(r1.multiply(alpha.x1));
            else if(res.lambda_1 > 0) //In case lambda_1 is positive, assign AdQ appropriately
                res.adq_positive = res.adq_positive.add(r1.multiply(alpha.x1));
        
            if(res.lambda_2 < 0) //In case lambda_2 is negative, assign AdQ appropriately
                res.adq_negative = res.adq_negative.add(r2.multiply(alpha.x2));
            else if(res.lambda_2 > 0) //In case lambda_2 is positive, assign AdQ appropriately
                res.adq_positive = res.adq_positive.add(r2.multiply(alpha.x2)); 
            
            //Handle special cases
            if(res.lambda_1 < 0 && res.lambda_2 < 0) 
                res.lambda_2 = 0;
            else if(res.lambda_1 > 0 && res.lambda_2 > 0) 
                res.lambda_1 = 0;

            return res;
        };

    };

};

#endif /* FCORE_HPP_ */