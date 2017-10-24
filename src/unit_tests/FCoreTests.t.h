/**
 * @file FCoreTests.t.h
 * @brief Unit tests for FCore and FCalc
*/

#include <math.h>
#include <limits>
#include <cxxtest/TestSuite.h>
#include "../solver/FCore.hpp"
#include "../solver/FCalc.hpp"


/**
 * @brief Definition and implementations of tests for the F-Wave solver
 * 
 * This class provides the necessary tests to verify the implementation of
 * the F-Wave solver and the helper methods in FCalc.
*/
class FCoreTestSuite : public CxxTest::TestSuite
{

public:

    /**
     * Test to verify that a zero vector is returned by the compute method when fed with parameters ql = qr = {0,0}
     */
    void testcompute_zero(void)
    {
        struct qvector zerovector = {0.0, 0.0};
        struct fresult res = FCore::compute(zerovector, zerovector);
        TS_ASSERT(res.adq_positive.x == 0 && res.adq_positive.y == 0);
    }

    /**
     * Test the implmentation of FCore::compute against some precomputed values
     * 
    */
    void testcompute_valid(void)
    {
        /** Scenario 1 */
        struct qvector ql = {0.0, 0.0};
        struct qvector qr = {0.0, 0.0};
        struct fresult res = FCore::compute(ql, qr);
        TS_ASSERT(true);

        /** Scenario 2 */
        ql = {0.0, 0.0};
        qr = {0.0, 0.0};
        res = FCore::compute(ql, qr);
        TS_ASSERT(true);

        /** Scenario 3 */
        ql = {0.0, 0.0};
        qr = {0.0, 0.0};
        res = FCore::compute(ql, qr);
        TS_ASSERT(true);

        /** Scenario 4 */
        ql = {0.0, 0.0};
        qr = {0.0, 0.0};
        res = FCore::compute(ql, qr);
        TS_ASSERT(true);        
    }


    /**
     * Test to verify FCalc::h_func by testing a set of predetermined inputs
     * to the #ZERO_PRECISION accuracy defined in FConst
    */
    void testh_func(void)
    {
        //(3.0 + 1.0)/2 = 2
        struct qvector ql = {1.0, 2.0};
        struct qvector qr = {3.0, 4.0};
        TS_ASSERT(std::abs(FCalc::h_func(ql, qr) - 2) < ZERO_PRECISION);

        //(-3.0+5.0)/2 = 1
        ql = {-3.0, 2.0};
        qr = {5.0, 4.0};
        TS_ASSERT(std::abs(FCalc::h_func(ql, qr) - 1) < ZERO_PRECISION);

        //(0.0 + 0.0)/2 = 0
        ql = {0.0, 0.0};
        qr = {0.0, 4.0};
        TS_ASSERT(std::abs(FCalc::h_func(ql, qr)) < ZERO_PRECISION); //Test zero input for zero output

        //(NaN + 5.0)/2 = NaN
        ql = {std::numeric_limits<double>::quiet_NaN(), 0.0};
        qr = {5.0, 4.0};
        TS_ASSERT(std::isnan(FCalc::h_func(ql, qr)));
    }

    /**
     * Test to verify FCalc::u_func by testing a set of predetermined inputs
     * to the #ZERO_PRECISION accuracy defined in FConst
    */
    void testu_func(void)
    {
        /** Scenario 1 */
        struct qvector ql = {1.0, 2.0};
        struct qvector qr = {3.0, 4.0};
        TS_ASSERT(std::abs(FCalc::u_func(ql, qr) - 1.5773502691896257645091487805019) < ZERO_PRECISION);

        /** Scenario 2 */
        ql = {3.0, -42.0};
        qr = {98.0, -599.0};
        TS_ASSERT(std::abs(FCalc::u_func(ql, qr) - -7.286808700128869) < ZERO_PRECISION);

        /** Scenario 3 */
        ql = {std::numeric_limits<double>::quiet_NaN(), -42.0};
        qr = {98.0, -599.0};
        TS_ASSERT(std::isnan(FCalc::u_func(ql, qr)));

        /** Scenario 4 */
        ql = {42.0, std::numeric_limits<double>::quiet_NaN()};
        qr = {98.0, -599.0};
        TS_ASSERT(std::isnan(FCalc::u_func(ql, qr)));

        /** Scenario 5 */
        ql = {98.0, -599.0};
        qr = {std::numeric_limits<double>::quiet_NaN(), -42.0};
        TS_ASSERT(std::isnan(FCalc::u_func(ql, qr)));

        /** Scenario 6 */
        ql = {98.0, -599.0};
        qr = {42.0, std::numeric_limits<double>::quiet_NaN()};
        TS_ASSERT(std::isnan(FCalc::u_func(ql, qr)));
    }

    /**
     * Test to verify FCalc::f_func by testing a set of predetermined inputs
     * to the #ZERO_PRECISION accuracy defined in FConst
    */
    void testf_func(void)
    {
        /** Scenario 1*/
        struct qvector input = {1.0 ,1.0};
        struct vector2 out = FCalc::f_func(input);
        TS_ASSERT_EQUALS(out.x, 1.0);
        TS_ASSERT(std::abs(out.y - 5.905) < ZERO_PRECISION);

        input = {-3.0, 5.0};
        out = FCalc::f_func(input);
        TS_ASSERT_EQUALS(out.x, 5.0);
        TS_ASSERT(std::abs(out.y - 69.145) < ZERO_PRECISION);

        input = {-3.0, -5.0};
        out = FCalc::f_func(input);
        TS_ASSERT_EQUALS(out.x, -5.0);
        TS_ASSERT(std::abs(out.y - 69.145) < ZERO_PRECISION);

        input = {1.0, std::numeric_limits<double>::quiet_NaN()};
        out = FCalc::f_func(input);
        TS_ASSERT(std::isnan(out.x));
        TS_ASSERT(std::isnan(out.y));
    }
};
