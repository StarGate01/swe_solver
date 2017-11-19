/**
 * @file FCoreTests.t.h
 * @brief Unit tests for FCore and FCalc
*/

//DEBUG
#include <iostream>
#include <iomanip>

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
        struct vector2 zerovector = {0.0, 0.0};
        fresult res = FCore::compute_netupdates(zerovector, zerovector, 0, 0);
        TS_ASSERT(res.adq_positive.x1 == 0 && res.adq_positive.x2 == 0);
    }

    /**
     * @test Check the implementation of solver::FCore::compute_eigenvalues against some precalculated numbers
    */
    void test_eigenvalues(void)
    {
        /**@brief Scenario 1: Check all input values equal to 1 */
        struct vector2 ql = {1.0, 1.0};
        struct vector2 qr = {1.0, 1.0};
        struct vector2 res = FCore::compute_eigenvalues(ql, qr);
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
        bl = -5;
        br = -10;
        hl =5;
        hr = 0;
        result = FCalc::bathymetry(bl, br, hl, hr);
        TS_ASSERT_DELTA(result.x1, 0, ZERO_PRECISION);
        TS_ASSERT_DELTA(result.x2, 122.6250, ZERO_PRECISION);

        /** @brief Scenario 5: NaN */
        bl = std::numeric_limits<double>::quiet_NaN();
        result = FCalc::bathymetry(bl, br, hl, hr);
        TS_ASSERT_DELTA(result.x1, 0, ZERO_PRECISION);
        TS_ASSERT(std::isnan(result.x2));

        /** @brief Scenario 6: bl = 42 */
        bl = 42; 
        hl = std::numeric_limits<double>::quiet_NaN();
        TS_ASSERT_DELTA(result.x1, 0, ZERO_PRECISION);
        TS_ASSERT(std::isnan(result.x2));
    }

    /**
     * @test Verify implementation of FCalc::froude_number
     * by testing against a set of predetermined values
    */
    void test_froude(void)
    {
        //Scenario 1: numerator equal to denominator
        double u,h;
        u = G_CONST;
        h = G_CONST;
        TS_ASSERT_DELTA(FCalc::froude_number(u, h), 1, ZERO_PRECISION);

        //Scenario 2: numerator = 0 results in output 0
        u = 0;
        TS_ASSERT_DELTA(FCalc::froude_number(u, h), 0, ZERO_PRECISION);
    }

    /**
     * @brief Compares two FStructs::fresult structs to be equal in regard to ZERO_PRECISION
    */
    void comparefresult(struct fresult r1, struct fresult r2)
    {
        //Test lambdas
        TS_ASSERT_DELTA(r1.lambda_1, r2.lambda_1, ZERO_PRECISION);
        TS_ASSERT_DELTA(r1.lambda_2, r2.lambda_2, ZERO_PRECISION);

        //Test adq_positive
        TS_ASSERT_DELTA(r1.adq_positive.x1, r2.adq_positive.x1, ZERO_PRECISION);
        TS_ASSERT_DELTA(r1.adq_positive.x2, r2.adq_positive.x2, ZERO_PRECISION);

        //Test adq_negative
        TS_ASSERT_DELTA(r1.adq_negative.x1, r2.adq_negative.x1, ZERO_PRECISION);
        TS_ASSERT_DELTA(r1.adq_negative.x2, r2.adq_negative.x2, ZERO_PRECISION);
    }

    /**
     * @test Verify implementation of FCore::compute_netupdates
     * by testing against a set of predetermined values
    */
    void test_compute_netupdates(void)
    {
        //Input parameters        
        struct vector2 ql;
        struct vector2 qr;
        double br;
        double bl;

        //Output parameters
        struct fresult result;      //fresult computed by solver TODO: remove
        struct fresult exresult;    //Expected result
        struct vector2 exresult_adq_positive;
        struct vector2 exresult_adq_negative;
        
        //NaN
        double nan = std::numeric_limits<double>::quiet_NaN();

        //Trivial test: All values zero
        ql = {0.0, 0.0};
        qr = {0.0, 0.0};
        br = 0;
        bl = 0;
        exresult_adq_positive = {0.0, 0.0};
        exresult_adq_negative = {0.0, 0.0};
        
        exresult = {0.0, 0.0, exresult_adq_positive, exresult_adq_negative};
        comparefresult(FCore::compute_netupdates(ql, qr, bl, br), exresult);

        //Special case: Speeds zero, heights and bathy equal
        ql = {10.0, 0.0};
        qr = {10.0, 0.0};
        br = -10.0;
        bl = -10.0;
        //Expect zero output again
        exresult = {0.0, 0.0, exresult_adq_positive, exresult_adq_negative};
        comparefresult(FCore::compute_netupdates(ql, qr, bl, br), exresult);

        //Dry cells remain dry (Reflecting boundary conditions) I
        ql = {30.0, 20.0};
        qr = {0.0, 0.0};
        bl = -30.0;
        br = 50.0;
        exresult_adq_positive = {0.0, 0.0};
        exresult_adq_negative = {-20, 343.1034829319};
        double lambda = 17.1551741466;      //Reflection
        exresult = {-lambda, lambda, exresult_adq_positive, exresult_adq_negative};
        comparefresult(FCore::compute_netupdates(ql, qr, bl, br), exresult);

        //Dry cells remain dry (Reflecting boundary conditions) II
        //This test uses the exact values, but the scenario is flipped (Parameters of compute_netupdates are intentionally flipped)
        exresult_adq_positive = {20, 343.1034829319};
        exresult_adq_negative = {0.0, 0.0};
        exresult = {-lambda, lambda, exresult_adq_positive, exresult_adq_negative};
        comparefresult(FCore::compute_netupdates(qr, ql, br, bl), exresult);


        //Output for manual verification TODO: Remove after verification
        //std::cout << std::fixed;
        //std::cout << std::setprecision(10);
        //result = FCore::compute_netupdates(ql, qr, bl, br);
        //std::cout << std::endl << "l1 " << result.lambda_1 << std::endl;
        //std::cout << "l2 " << result.lambda_2 << std::endl;
        //std::cout << "a+ " << std::setprecision(3) << result.adq_positive.x1 << " , " << result.adq_positive.x2 << std::endl;
        //std::cout << "a- " << result.adq_negative.x1 << " , " << result.adq_negative.x2 << std::endl;
    }
};
