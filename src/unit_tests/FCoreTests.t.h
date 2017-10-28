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
#include "CSVParser.hpp"

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
     * @test Verify that a zero vector is returned by the solver::FCore::compute method when fed with parameters ql = qr = {0,0}
     */
    void test_compute_zero(void)
    {
        struct vector2 zerovector = {0.0, 0.0};
        struct fresult res = FCore::compute_netupdates(zerovector, zerovector);
        TS_ASSERT(res.adq_positive.x1 == 0 && res.adq_positive.x2 == 0);
    }


    /**
     * @test Check the implementation against the reference implementation
    */
    void test_compute_reference(void)
    {
        std::ifstream f("/home/foxtrot/Documents/tmpTsunami/submodules/solvers/src/unit_tests/test.csv");
        if(!f.good())
        {
            TS_WARN("\nFAILED TO OPEN FILE");
            TS_ASSERT(false);
            return;
        }

        while(CSVParser::moreLinesToRead(f))
        {
            struct testdata result = CSVParser::readLine(f);
            //TODO: Test data
            //TODO: React to runtime error: no more lines to read
        }
        
        f.close();
        f.clear();
        TS_ASSERT(true);
    }


    /**
     * @test Chéck the implementation of solver::FCore::compute_eigenvalues against some precalculated numbers
    */
    void test_eigenvalues(void)
    {
        /**@brief Check all input values equal to 1 */
        struct vector2 ql = {1.0, 1.0};
        struct vector2 qr = {1.0, 1.0};
        struct vector2 res = FCore::compute_eigenvalues(ql, qr);
        TS_ASSERT(res.x1 - 2.132091952673165 < ZERO_PRECISION && res.x2 - 4.132091952673165 < ZERO_PRECISION);

        /**@brief Check ql = {2.0, 3.0} and qr = {4.0, 5.0} */
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
        struct vector2 ql = {1.0, 2.0};
        struct vector2 qr = {3.0, 4.0};
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
        struct vector2 ql = {1.0, 2.0};
        struct vector2 qr = {3.0, 4.0};
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
        struct vector2 input = {1.0 ,1.0};
        struct vector2 out = FCalc::flux(input);
        TS_ASSERT_EQUALS(out.x1, 1.0);
        TS_ASSERT(std::abs(out.x2 - 5.905) < ZERO_PRECISION);

        /** @brief Scenario 2: Negative h value */
        input = {-3.0, 5.0};
        out = FCalc::flux(input);
        TS_ASSERT_EQUALS(out.x1, 5.0);
        TS_ASSERT(std::abs(out.x2 - 69.145) < ZERO_PRECISION);

        /** @brief Scenario 3: Negative h and hu value*/
        input = {-3.0, -5.0};
        out = FCalc::flux(input);
        TS_ASSERT_EQUALS(out.x1, -5.0);
        TS_ASSERT(std::abs(out.x2 - 69.145) < ZERO_PRECISION);

        /** @brief Scenario 4: hu is NaN */
        input = {1.0, std::numeric_limits<double>::quiet_NaN()};
        out = FCalc::flux(input);
        TS_ASSERT(std::isnan(out.x1));
        TS_ASSERT(std::isnan(out.x2));
    }

};
