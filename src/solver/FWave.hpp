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
 */
class FWave
{

public:
    /**
     * Compute net updates for the left and right cell of the edge. Nothing is returned as the values are changed inside the given matrices.
     *
     * @param l_h The left heights
     * @param r_h[] The right heights
     * @param l_hu[] The left speeds
     * @param r_hu[] The right speeds
     * @param b_l[] The left Bathymetry
     * @param b_r[] The right Bathymetry
     * @param hNetUpdatesLeft[] The left updates to the heigts
     * @param hNetUpdatesRight[] The right updates to the heights
     * @param huNetUpdatesLeft[] The left updates to the speeds
     * @param huNetUpdatesRight[] The right updates to the speeds
     * @param maxEdgeSpeed maximum wave speed value
     * 
     */
    void computeNetUpdates (float l_h[], float r_h[],
        float l_hu[], float r_hu[],
        float b_l, float b_r,	
        float hNetUpdatesLeft[], float hNetUpdatesRight[],
        float huNetUpdatesLeft[], float huNetUpdatesRight[],
        float maxEdgeSpeed );
    
};

#endif //FWAVE_HPP_
