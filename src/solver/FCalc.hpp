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
         * Computes the height.
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
         * @param ql The left state
         * @param qr The right state
         * 
         * @return The particle velocity
         */
        static double u_func(qvector ql, qvector qr);

        /**
         * Computes the flux.
         * 
         * @param q The state
         * 
         * @return The flux
         */
        static struct vector2 f_func(qvector q);

    };

};

#endif /* FCALC_HPP_ */