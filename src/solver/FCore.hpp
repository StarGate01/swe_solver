/**
 * @file FCore.hpp
 * @brief Core functionality of the F-Wave solver
 */

#ifndef FCORE_HPP_
#define FCORE_HPP_

#include "FStructs.hpp"

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
         * Static method that computes the resulting net-updates and wave speeds from the left and right state as described in @cite bale2002wave and @cite leveque2002finite.
         * 
         * Compute Roe eigenvalues to approximate wave speeds using solver::FCalc::u_func and solver::FCalc::h_func 
         * @f[ \lambda_{1,2}^{Roe}(q_l, q_r) = u^{Roe}(q_l, q_r) \pm \sqrt{gh^{Roe}(q_l, q_r)} @f]
         * Using the intermediate computations for the eigenvectors 
         * @f[ r_{1,2}^{Roe} = \begin{bmatrix} 1 \\ \lambda_{1,2}^{Roe} \end{bmatrix} @f]
         * And the jump in the difference in the flux function and waves using solver::FCalc::f_func
         * @f[ \Delta f = f(q_r) - f(q_l) @f] 
         * And the coefficients of this jump using another representation of the flux difference
         * @f[ \Delta f = \sum_{p=1}^2 \alpha_p r_p = \sum_{p=1}^2 Z_p @f]
         * @f[ 
         *      \begin{bmatrix} \alpha_1 \\ \alpha_2 \end{bmatrix} = 
         *      {\begin{bmatrix} 1 & 1 \\ \lambda_1^{Roe} & \lambda_2^{Roe} \end{bmatrix}}^{-1} \Delta f 
         *      \implies \alpha_{1,2} =  \frac{\Delta f_x \lambda_{2,1}^{Roe} \pm {\Delta f}_y}{\lambda_2^{Roe} - \lambda_1^{Roe}} 
         * @f]
         * Compute the net-updates using the waves and eigenvectors
         * @f[ A^{\mp}\Delta Q = \sum_{p: \{ \lambda_p^{Roe} \lessgtr 0 \}} Z_p \equiv @f]
         * @f[ 
         *      A^{-}\Delta Q = \begin{cases} 
         *          \begin{bmatrix} \alpha_1 r_{1x} \\ \alpha_1 r_{1x} \end{bmatrix} & \text{for } \lambda_1 < 0 \\ \\ 
         *          \begin{bmatrix} \alpha_1 r_{2x} \\ \alpha_1 r_{2x} \end{bmatrix} & \text{for } \lambda_2 < 0 
         *      \end{cases} 
         *      \text{  and  }
         *      A^{+}\Delta Q = \begin{cases} 
         *          \begin{bmatrix} \alpha_1 r_{1x} \\ \alpha_1 r_{1x} \end{bmatrix} & \text{for } \lambda_1 > 0 \\ \\ 
         *          \begin{bmatrix} \alpha_1 r_{2x} \\ \alpha_1 r_{2x} \end{bmatrix} & \text{for } \lambda_2 > 0 
         *      \end{cases} 
         * @f]
         * 
         * @param ql The left state
         * @param qr The right state
         * 
         * @return The resulting net-updates and wave speeds
         */
        static struct fresult compute(qvector ql, qvector qr);

    };

};

#endif /* FCORE_HPP_ */