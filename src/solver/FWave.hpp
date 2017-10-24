/**
 * @file FWave.hpp
 * @brief Adapter for the F-Wave solver to the surrounding framework
 */

#ifndef FWAVE_HPP_
#define FWAVE_HPP_

#include "FCore.hpp"

/**
 * @brief Adapter to the surrounding framework
 * 
 * This class provides the necessary methods for the F-Wave environment to interact with the F-Wave solver.
 * Supports flout and double as type parametrization argument.
 * 
 */
template <typename T>
class FWave
{

public:

    /**
     * Compute net updates for the left and right cell of the edge.
     * 
     * Nothing is returned as the values are changed inside the given matrices.
     * 
     * @param l_h[] The left heights
     * @param r_h[] The right heights
     * @param l_hu[] The left speeds
     * @param r_hu[] The right speeds
     * @param b_l[] The left Bathymetry
     * @param b_r[] The right Bathymetry
     * @param[out] hNetUpdatesLeft[] The left updates to the heights
     * @param[out] hNetUpdatesRight[] The right updates to the heights
     * @param[out] huNetUpdatesLeft[] The left updates to the speeds
     * @param[out] huNetUpdatesRight[] The right updates to the speeds
     * @param maxEdgeSpeed maximum wave speed value
     * 
     */
    void computeNetUpdates (T l_h[], T r_h[],
        T l_hu[], T r_hu[],
        T b_l, T b_r,	
        T hNetUpdatesLeft[], T hNetUpdatesRight[],
        T huNetUpdatesLeft[], T huNetUpdatesRight[],
        T maxEdgeSpeed );

    
};

#endif //FWAVE_HPP_
