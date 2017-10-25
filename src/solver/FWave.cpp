/**
 * @file FWave.cpp
 * @brief Implementation of FWave.hpp
 */

#include "FWave.hpp"

using namespace solver;

template <typename T> FWave<T>::computeNetUpdates (const T &hLeft,  const T &hRight,
    const T &huLeft, const T &huRight,
    const T &bLeft,  const T &bRight,
    T &hUpdateLeft, T &hUpdateRight,
    T &huUpdateLeft, T &huUpdateRight,
    T &maxWaveSpeed)
{
        
}

template class FWave<float>;
template class FWave<double>;