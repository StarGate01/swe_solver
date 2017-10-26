/**
 * @file FCalc.hpp
 * @brief Auxiliary methods for the F-Wave solver
*/

#ifndef FCALC_HPP_
#define FCALC_HPP_

#include "FStructs.hpp"
#include "FConst.hpp"

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
        static double h_func(qvector ql, qvector qr);

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
        static double u_func(qvector ql, qvector qr);

        /**
         * Computes the flux using #G_CONST.
         * 
         * @f[ f(q) = \begin{bmatrix} {hu} \\ {hu}^2 + \frac{1}{2}gh^2 \end{bmatrix} @f]
         * 
         * @param q The state
         * 
         * @return The flux vector
         */
        static struct vector2 f_func(qvector q);

    };

};

#endif /* FCALC_HPP_ */