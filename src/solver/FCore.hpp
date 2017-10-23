/**
 * @file FCore.hpp
 * @brief Header file of the F-Wave solver
 */

#ifndef FCORE_HPP_
#define FCORE_HPP_

#include "FStructs.hpp"

/**
 * The earth's gravitational acceleration in m/s
 */
#define G_CONST 9.81
#define ZERO_PRECISION 0.00001

/**
 * @brief Static implementation of the F-Wave solver
 * 
 * This class provides the neccessary functionality to compute the left and right going net-updates 
 *      and wave speeds of the left and right going waves given the left and right state.
 */
class FCore
{

public:

     /**
     * Computes the resulting net-updates and wave speeds from the left and right state.
     *
     * @param ql The left state
     * @param qr The right state
     * 
     * @return The resulting net-updates and wave speeds
     */
    static struct fresult compute(qvector ql, qvector qr);


private:
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


#endif /* FCORE_HPP_ */