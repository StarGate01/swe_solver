/**
 * @file FWave.hpp
 * @brief Adapter for the F-Wave solver to the surrounding framework
 */

#ifndef FWAVE_HPP_
#define FWAVE_HPP_

#include "FCore.hpp"
#include <limits>
#include <algorithm>

namespace solver
{

    /**
     * @brief Adapter to the surrounding framework
     * 
     * This class provides the necessary methods for the F-Wave environment to interact with the F-Wave solver.
     * Supports flout and double as type parametrization argument.
     * 
     */
    template <typename T> class FWave
    {

    public:

        /**
         * Compute net updates for the left and right cell of the edge.
         * 
         * Nothing is returned as the values are changed inside the given references.
         * 
         * @param[in] hLeft height on the left side of the edge.
         * @param[in] hRight height on the right side of the edge.
         * @param[in] huLeft momentum on the left side of the edge.
         * @param[in] huRight momentum on the right side of the edge.
         * @param[in] bLeft bathymetry on the left side of the edge.
         * @param[in] bRight bathymetry on the right side of the edge.
         * @param[out] hUpdateLeft will be set to: Net-update for the height of the cell on the left side of the edge.
         * @param[out] hUpdateRight will be set to: Net-update for the height of the cell on the right side of the edge.
         * @param[out] huUpdateLeft will be set to: Net-update for the momentum of the cell on the left side of the edge.
         * @param[out] huUpdateRight will be set to: Net-update for the momentum of the cell on the right side of the edge.
         * @param[out] maxWaveSpeed will be set to: Maximum (linearized) wave speed -> Should be used in the CFL-condition.
         */
        void computeNetUpdates (const T &hLeft,  const T &hRight,
            const T &huLeft, const T &huRight,
            const T &bLeft,  const T &bRight,
            T &hUpdateLeft, T &hUpdateRight,
            T &huUpdateLeft, T &huUpdateRight,
            T &maxWaveSpeed)
        {
            struct fresult coreres = FCore::compute(
                { .h = (double)hLeft, .hu = (double)huLeft }, 
                { .h = (double)hRight, .hu = (double)huRight }
            );
            hUpdateLeft = (T)coreres.adq_negative.h;
            huUpdateLeft = (T)coreres.adq_negative.hu;
            hUpdateRight = (T)coreres.adq_positive.h;
            huUpdateRight = (T)coreres.adq_positive.hu;
            maxWaveSpeed = (T)std::max(std::abs(coreres.lambda_1), std::abs(coreres.lambda_2));
        };
        
    };

};

#endif //FWAVE_HPP_
