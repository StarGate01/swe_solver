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
        static double h_func(qvector ql, qvector qr)
        {
            return 0.5 * (ql.h + qr.h);
        };

        /**
         * Computes the particle velocity.
         * 
         * @f[ u^{Roe}(q_l, q_r) = \frac{u_l \sqrt{h_l} + u_r \sqrt{h_r}}{\sqrt{h_l} + \sqrt{h_r}} = \frac{\frac{{hu}_l}{h_l} \sqrt{h_l} + \frac{{hu}_r}{h_r} \sqrt{h_r}}{\sqrt{h_l} + \sqrt{h_r}} @f]
         * 
         * @param ql The left state
         * @param qr The right state
         * 
         * @return The particle velocity
         */
        static double u_func(qvector ql, qvector qr)
        {
            if(std::isnan(ql.h) || std::isnan(ql.hu) || std::isnan(qr.h) || std::isnan(qr.hu))
                return std::numeric_limits<double>::quiet_NaN();
    
            assert(ql.h > ZERO_PRECISION && qr.h > ZERO_PRECISION); //Assert h values of ql and qr are positive
        
            double ul = ql.hu / ql.h;
            double ur = qr.hu / qr.h;
            return (ul * sqrt(ql.h) + ur * sqrt(qr.h)) / (sqrt(ql.h) + sqrt(qr.h));
        };

        /**
         * Computes the flux using #G_CONST.
         * 
         * @f[ f(q) = \begin{bmatrix} {hu} \\ {hu}^2 + \frac{1}{2}gh^2 \end{bmatrix} @f]
         * 
         * @param q The state
         * 
         * @return The flux vector
         */
        static struct vector2 f_func(qvector q)
        {
            struct vector2 result = {
                q.hu, 
                q.hu * q.hu + 0.5 * G_CONST * q.h * q.h
            };
            return result;
        };

    };

};

#endif /* FCALC_HPP_ */