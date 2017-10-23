/**
 * @file FCore.hpp
 * @brief Core functionality of the F-Wave solver
 */

#ifndef FCORE_HPP_
#define FCORE_HPP_

#include "FStructs.hpp"


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
     * Static method, that computes the resulting net-updates and wave speeds from the left and right state.
     *
     * @param ql The left state
     * @param qr The right state
     * 
     * @return The resulting net-updates and wave speeds
     */
    static struct fresult compute(qvector ql, qvector qr);

};


#endif /* FCORE_HPP_ */