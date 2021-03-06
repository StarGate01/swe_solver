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
        static double avg_height(const vector2 ql, const vector2 qr)
        {
            return (ql.x1 + qr.x1) * 0.5;
        };

        /**
         * @brief Computes the average particle velocity.
         * 
         * @f[ 
         *      u^{Roe}(q_l, q_r) = \frac{u_l \sqrt{h_l} + u_r \sqrt{h_r}}{\sqrt{h_l} + \sqrt{h_r}} 
         *      \text{  with  } u = \frac{hu}{h}
         * @f]
         * 
         * @param ql The left state
         * @param qr The right state
         * 
         * @return The particle velocity
         */
        static double avg_particle_velocity(const vector2 ql, const vector2 qr)
        {
#ifndef CUSTOM_OPT
        if(std::isnan(ql.x1) || std::isnan(ql.x2) || std::isnan(qr.x1) || std::isnan(qr.x2))
            return std::numeric_limits<double>::quiet_NaN();

    #ifndef NDEBUG  
            assert(ql.x1 > ZERO_PRECISION && qr.x1 > ZERO_PRECISION); //Assert h values of ql and qr are positive
    #endif
#endif


#ifndef CUSTOM_OPT
            double s_ql = sqrt(ql.x1);
            double s_qr = sqrt(qr.x1);
            return (
                ((ql.x2 / ql.x1) * s_ql)
                 + ((qr.x2 / qr.x1) * s_qr)
            ) / (s_ql + s_qr);
#else
            return (
                ((ql.x2 / ql.x1) * sqrt(ql.x1))
                 + ((qr.x2 / qr.x1) * sqrt(qr.x1))
            ) / (sqrt(ql.x1) + sqrt(qr.x1));
#endif
          
        };

        /**
         * @brief Computes the flux using #G_CONST.
         * 
         * @f[ f(q) = \begin{bmatrix} {hu} \\ h u^2 + \frac{1}{2}gh^2 \end{bmatrix} @f]
         * 
         * @param q The state
         * 
         * @return The flux vector
         */
        static vector2 flux(const vector2 q)
        {
            return {
                q.x2, 
                (q.x2 * (q.x2 / q.x1)) + (0.5 * G_CONST * q.x1 * q.x1)
            };
        };

        /**
         * @brief Computes the bathymetry term for solver::FCalc::flux as given in @cite tssim2
         * 
         * @f[ \Delta x \Psi_{i-1/2}(b, h) = \begin{bmatrix} 0 \\ -g (b_r - b_l) \frac{h_l + h_r}{2} \end{bmatrix} @f]
         * 
         * @param bl The left bathymetry
         * @param br The right bathymetry
         * @param hl The left height
         * @param hr The right height
         * 
         * @return The bathymetry term
         */
        static vector2 bathymetry(const double bl, const double br, const double hl, const double hr)
        {
            return {
                0, 
                -G_CONST * (br - bl) * ((hl + hr) / 2.0)
            };
        };

        /**
         * @brief Computes the froude number
         * 
         * @f[ F(u, h) = \frac{u}{\sqrt{gh}} @f]
         * Regions with @f$ F < 1 @f$ are subcritical, @f$ F \approx 1 @f$ are critical and @f$ F > 1 @f$ are supercritical
         * 
         * @param u The particle velocity
         * @param h The height
         * 
         * @return Froude number
        */
        static double froude_number(const double u, const double h)
        {   
            if (h < ZERO_PRECISION) return 0;
            #ifndef NDEBUG
                assert(std::sqrt(G_CONST * h) > ZERO_PRECISION);
            #endif
            return u / (std::sqrt(G_CONST * h));
        }

    };

};

#endif /* FCALC_HPP_ */