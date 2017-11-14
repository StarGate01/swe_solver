/**
 * @file FCoreTests.t.h
 * @brief Unit tests for FCore and FCalc
*/

//DEBUG
#include <iostream>

#include <math.h>
#include <limits>
#include <string>
#include <cxxtest/TestSuite.h>
#include "../solver/FCore.hpp"
#include "../solver/FCalc.hpp"

using namespace solver;

/**
 * @brief Tests for the F-Wave solver
 */
namespace solver_tests
{

    class FCoreTestSuite;

}

/**
 * @brief Definition and implementations of tests for the F-Wave solver
 * 
 * This class provides the necessary tests to verify the implementation of the F-Wave solver and its helper methods
*/
class solver_tests::FCoreTestSuite : public CxxTest::TestSuite
{

public:
    /**
     * @test Verify that a zero vector is returned by the solver::FCore::compute_netupdates method when fed with parameters ql = qr = {0,0}
     */
    void test_compute_zero(void)
    {
        vector2 zerovector = {0.0, 0.0};
        fresult res = FCore::compute_netupdates(zerovector, zerovector, 0, 0);
        TS_ASSERT(res.adq_positive.x1 == 0 && res.adq_positive.x2 == 0);
    }

    /**
     * @test Check the implementation of solver::FCore::compute_eigenvalues against some precalculated numbers
    */
    void test_eigenvalues(void)
    {
        /**@brief Scenario 1: Check all input values equal to 1 */
        vector2 ql = {1.0, 1.0};
        vector2 qr = {1.0, 1.0};
        vector2 res = FCore::compute_eigenvalues(ql, qr);
        TS_ASSERT(res.x1 - 2.132091952673165 < ZERO_PRECISION && res.x2 - 4.132091952673165 < ZERO_PRECISION);

        /**@brief Scenario 2: Check ql = {2.0, 3.0} and qr = {4.0, 5.0} */
        ql = {2.0, 3.0};
        qr = {4.0, 5.0};
        res = FCore::compute_eigenvalues(ql, qr);
        TS_ASSERT(res.x1 - (1.353553390593274 - 5.424942396007538) < ZERO_PRECISION && res.x2 - (1.353553390593274 + 5.424942396007538) < ZERO_PRECISION);
    }

    /**
     * @test Verify solver::FCalc::avg_height by testing a set of predetermined inputs to the #ZERO_PRECISION accuracy
    */
    void test_avg_height(void)
    {
        /** @brief Scenario 1: @f[ \frac{3.0 + 1.0}{2.0} \overset{!}{=} 2.0 @f] */
        vector2 ql = {1.0, 2.0};
        vector2 qr = {3.0, 4.0};
        TS_ASSERT(std::abs(FCalc::avg_height(ql, qr) - 2.0) < ZERO_PRECISION);

        /** @brief Scenario 2: @f[ \frac{-3.0+5.0}{2.0} \overset{!}{=} 1.0 @f] */
        ql = {-3.0, 2.0};
        qr = {5.0, 4.0};
        TS_ASSERT(std::abs(FCalc::avg_height(ql, qr) - 1.0) < ZERO_PRECISION);

        /** @brief Scenario 3: @f[ \frac{0.0 + 0.0}{2.0} \overset{!}{=} 0.0 @f] */
        ql = {0.0, 0.0};
        qr = {0.0, 4.0};
        TS_ASSERT(std::abs(FCalc::avg_height(ql, qr)) < ZERO_PRECISION); //Test zero input for zero output

        /** @brief Scenario 4: @f[ \frac{NaN + 5.0}{2.0} \overset{!}{=} NaN @f] */
        ql = {std::numeric_limits<double>::quiet_NaN(), 0.0};
        qr = {5.0, 4.0};
        TS_ASSERT(std::isnan(FCalc::avg_height(ql, qr)));
    }

    /**
     * @test Verify solver::FCalc::avg_particle_velocity by testing a set of predetermined inputs to the #ZERO_PRECISION accuracy
    */
    void test_avg_particle_velocity(void)
    {
        /** @brief Scenario 1: Standard set of numbers */
        vector2 ql = {1.0, 2.0};
        vector2 qr = {3.0, 4.0};
        TS_ASSERT(std::abs(FCalc::avg_particle_velocity(ql, qr) - 1.5773502691896257645091487805019) < ZERO_PRECISION);

        /** @brief Scenario 2: Negative hu values */
        ql = {3.0, -42.0};
        qr = {98.0, -599.0};
        TS_ASSERT(std::abs(FCalc::avg_particle_velocity(ql, qr) - -7.286808700128869) < ZERO_PRECISION);

        /** @brief Scenario 3: ql.x1 is NaN*/
        ql = {std::numeric_limits<double>::quiet_NaN(), -42.0};
        qr = {98.0, -599.0};
        TS_ASSERT(std::isnan(FCalc::avg_particle_velocity(ql, qr)));

        /** @brief Scenario 4: ql.x2 is NaN */
        ql = {42.0, std::numeric_limits<double>::quiet_NaN()};
        qr = {98.0, -599.0};
        TS_ASSERT(std::isnan(FCalc::avg_particle_velocity(ql, qr)));

        /** @brief Scenario 5: qr.x1 is NaN */
        ql = {98.0, -599.0};
        qr = {std::numeric_limits<double>::quiet_NaN(), -42.0};
        TS_ASSERT(std::isnan(FCalc::avg_particle_velocity(ql, qr)));

        /** @brief Scenario 6: qr.x2 is NaN */
        ql = {98.0, -599.0};
        qr = {42.0, std::numeric_limits<double>::quiet_NaN()};
        TS_ASSERT(std::isnan(FCalc::avg_particle_velocity(ql, qr)));
    }

    /**
     * @test Verify solver::FCalc::flux by testing a set of predetermined inputs to the #ZERO_PRECISION accuracy
    */
    void test_flux(void)
    {
        /** @brief Scenario 1: Standard set of numbers */
        vector2 input = {1.0 ,1.0};
        vector2 out = FCalc::flux(input);
        TS_ASSERT_EQUALS(out.x1, 1.0);
        TS_ASSERT(std::abs(out.x2 - 5.905) < ZERO_PRECISION);

        /** @brief Scenario 2: Negative h value */
        input = {-3.0, 5.0};
        out = FCalc::flux(input);
        TS_ASSERT_EQUALS(out.x1, 5.0);
        TS_ASSERT(std::abs(out.x2 - 35.8116666666) < ZERO_PRECISION);

        /** @brief Scenario 3: Negative h and hu value*/
        input = {-3.0, -5.0};
        out = FCalc::flux(input);
        TS_ASSERT_EQUALS(out.x1, -5.0);
        TS_ASSERT(std::abs(out.x2 - 35.8116666666) < ZERO_PRECISION);

        /** @brief Scenario 4: hu is NaN */
        input = {1.0, std::numeric_limits<double>::quiet_NaN()};
        out = FCalc::flux(input);
        TS_ASSERT(std::isnan(out.x1));
        TS_ASSERT(std::isnan(out.x2));
    }

    /**
     * @test Verify solver::FCalc::bathymetry by testing against a set of predetermined inputs to the #ZERO_PRECISION accuracy and NaN-inputs
    */
    void test_bathy(void)
    {
        double bl, br, hl, hr;
        vector2 result;

        /** @brief Scenario 1: All values = 0 */
        result = FCalc::bathymetry(bl, br, hl, hr);
        TS_ASSERT_DELTA(result.x1, 0, ZERO_PRECISION);
        TS_ASSERT_DELTA(result.x2, 0, ZERO_PRECISION);

        /** @brief Scenario 2: Symmetric water height with different ground level */
        bl = -5;
        br = -10;
        hl = 5;
        hr = 10;
        result = FCalc::bathymetry(bl, br, hl, hr);
        TS_ASSERT_DELTA(result.x1, 0, ZERO_PRECISION);
        TS_ASSERT_DELTA(result.x2, 367.8750, ZERO_PRECISION);

        /** @brief Scenario 3: Equal ground level results in zero output */
        bl = -25;
        br = -25;
        result = FCalc::bathymetry(bl, br, hl, hr);
        TS_ASSERT_DELTA(result.x1, 0, ZERO_PRECISION);
        TS_ASSERT_DELTA(result.x2, 0, ZERO_PRECISION);

        /** @brief Scenario 4: One cell dry */
        b = -5;
        br = -10;
        hl =5;
        hr = 0;
        result = FCalc::bathymetry(bl, br, hl, hr);
        TS_ASSERT_DELTA(result.x1, 0, ZERO_PRECISION);
        TS_ASSERT_DELTA(result.x2, 122.6250, ZERO_PRECISION);

        /** @brief Scenario 5: NaN */
        b = std::numeric_limits<double>::quiet_NaN();
        result = FCalc::bathymetry(bl, br, hl, hr);
        TS_ASSERT_DELTA(result.x1, 0, ZERO_PRECISION);
        TS_ASSERT(std::isnan(result.x2));

        /** @brief Scenario 6: bl = 42 */
        bl = 42; 
        hl = std::numeric_limits<double>::quiet_NaN();
        TS_ASSERT_DELTA(result.x1, 0, ZERO_PRECISION);
        TS_ASSERT(std::isnan(result.x2));
    }

};
