/**
 * @file FWave.cpp
 * @brief Implementation of FWave.hpp
 */

#include "FWave.hpp"

 template <typename T> FWave<T>::computeNetUpdates (T l_h[], T r_h[],
    T l_hu[], T r_hu[],
    T b_l, T b_r,	
    T hNetUpdatesLeft[], T hNetUpdatesRight[],
    T huNetUpdatesLeft[], T huNetUpdatesRight[],
    T maxEdgeSpeed )
{
        
}

template class FWave<float>;
template class FWave<double>;