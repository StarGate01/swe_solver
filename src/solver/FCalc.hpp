/**
 * @file FCalc.hpp
 * @brief Auxiliary methods for the F-Wave solver
*/

#ifndef FCALC_HPP_
#define FCALC_HPP_

#include <assert.h>
#include <math.h>
#include <limits>
#include "FStructs.hpp"
#include "FConst.hpp"

// using namespace std;

namespace solver
{

    /**
     * @brief Some static helper methods for the F-Wave solver
     * 
     * This class provides some methods used in the implementation of FCore
     */
    class FCalc
    {

    public:

        /**
         * @brief Computes the average height of two neighboring states.
         * 
         * @f[ h^{Roe}(q_l, q_r) = \frac{1}{2} (h_l + h_r) @f] 
         * 
         * @param ql The left state
         * @param qr The right state
         * 
         * @return The height
         */
        static double avg_height(vector2 ql, vector2 qr)
        {
            return 0.5 * (ql.x1 + qr.x1);
        };

        /**
         * @brief Computes the average particle velocity.
         * 
         * @f[ 
         *      u^{Roe}(q_l, q_r) = \frac{u_l \sqrt{h_l} + u_r \sqrt{h_r}}{\sqrt{h_l} + \sqrt{h_r}} 
         *      \text{  with  } u = \frac{hu}{h}
         * @f]
         * 
         * @param ql The left state
         * @param qr The right state
         * 
         * @return The particle velocity
         */
        static double avg_particle_velocity(vector2 ql, vector2 qr)
        {
            if(std::isnan(ql.x1) || std::isnan(ql.x2) || std::isnan(qr.x1) || std::isnan(qr.x2))
                return std::numeric_limits<double>::quiet_NaN();
                
            assert(ql.x1 > ZERO_PRECISION && qr.x1 > ZERO_PRECISION); //Assert h values of ql and qr are positive

            return (((ql.x2 / ql.x1) * sqrt(ql.x1)) + ((qr.x2 / qr.x1) * sqrt(qr.x1))) / (sqrt(ql.x1) + sqrt(qr.x1));
        };

        /**
         * @brief Computes the flux using #G_CONST.
         * 
         * @f[ f(q) = \begin{bmatrix} {hu} \\ {hu}^2 + \frac{1}{2}gh^2 \end{bmatrix} @f]
         * 
         * @param q The state
         * 
         * @return The flux vector
         */
        static vector2 flux(vector2 q)
        {
            return {
                q.x2, 
                (q.x2 * q.x2) + (0.5 * G_CONST * q.x1 * q.x1)
            };
        };

    };

};

#endif /* FCALC_HPP_ */