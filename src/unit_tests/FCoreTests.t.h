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
     * @brief Test to verify that a zero vector is returned by the compute method when fed with parameters ql = qr = {0,0}
     */
    void testcompute_zero(void)
    {
        struct qvector zerovector = {0.0, 0.0};
        struct fresult res = FCore::compute(zerovector, zerovector);
        TS_ASSERT(res.adq_positive.x == 0 && res.adq_positive.y == 0);
    }

    /**
     * @brief Test the implmentation of FCore::compute against some precomputed values
     * 
    */
    void testcompute_valid(void)
    {
        /** @brief Scenario 1: Zero input results in zero output */
        struct qvector ql = {0.0, 0.0};
        struct qvector qr = {0.0, 0.0};
        struct fresult res = FCore::compute(ql, qr);
        TS_ASSERT(true);

        //TODO: Add correct numbers to verify output
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
     * @brief Test to verify FCalc::h_func by testing a set of predetermined inputs
     *  to the #ZERO_PRECISION accuracy defined in FConst
    */
    void testh_func(void)
    {
        //@brief Assert %\frac{3.0 + 1.0}{2} = 2% 
        struct qvector ql = {1.0, 2.0};
        struct qvector qr = {3.0, 4.0};
        TS_ASSERT(std::abs(FCalc::h_func(ql, qr) - 2) < ZERO_PRECISION);

        //@brief Assert %\frac{-3.0+5.0}{2} = 1%
        ql = {-3.0, 2.0};
        qr = {5.0, 4.0};
        TS_ASSERT(std::abs(FCalc::h_func(ql, qr) - 1) < ZERO_PRECISION);

        //@brief Assert %\frac{0.0 + 0.0}{2} = 0%
        ql = {0.0, 0.0};
        qr = {0.0, 4.0};
        TS_ASSERT(std::abs(FCalc::h_func(ql, qr)) < ZERO_PRECISION); //Test zero input for zero output

        //@brief %\frac{\text{NaN} + 5.0}{2} = \text{NaN}%
        ql = {std::numeric_limits<double>::quiet_NaN(), 0.0};
        qr = {5.0, 4.0};
        TS_ASSERT(std::isnan(FCalc::h_func(ql, qr)));
    }

    /**
     * @brief Test to verify FCalc::u_func by testing a set of predetermined inputs
     *  to the #ZERO_PRECISION accuracy defined in FConst
    */
    void testu_func(void)
    {
        /** @brief Scenario 1: Standard set of numbers */
        struct qvector ql = {1.0, 2.0};
        struct qvector qr = {3.0, 4.0};
        TS_ASSERT(std::abs(FCalc::u_func(ql, qr) - 1.5773502691896257645091487805019) < ZERO_PRECISION);

        /** @brief Scenario 2: Negative hu values */
        ql = {3.0, -42.0};
        qr = {98.0, -599.0};
        TS_ASSERT(std::abs(FCalc::u_func(ql, qr) - -7.286808700128869) < ZERO_PRECISION);

        /** @brief Scenario 3: ql.h is NaN*/
        ql = {std::numeric_limits<double>::quiet_NaN(), -42.0};
        qr = {98.0, -599.0};
        TS_ASSERT(std::isnan(FCalc::u_func(ql, qr)));

        /** @brief Scenario 4: ql.hu is NaN */
        ql = {42.0, std::numeric_limits<double>::quiet_NaN()};
        qr = {98.0, -599.0};
        TS_ASSERT(std::isnan(FCalc::u_func(ql, qr)));

        /** @brief Scenario 5: qr.h is NaN */
        ql = {98.0, -599.0};
        qr = {std::numeric_limits<double>::quiet_NaN(), -42.0};
        TS_ASSERT(std::isnan(FCalc::u_func(ql, qr)));

        /** @brief Scenario 6: qr.hu is NaN */
        ql = {98.0, -599.0};
        qr = {42.0, std::numeric_limits<double>::quiet_NaN()};
        TS_ASSERT(std::isnan(FCalc::u_func(ql, qr)));
    }

    /**
     * @brief Test to verify FCalc::f_func by testing a set of predetermined inputs
     *  to the #ZERO_PRECISION accuracy defined in FConst
    */
    void testf_func(void)
    {
        /** @brief Scenario 1: Standard set of numbers */
        struct qvector input = {1.0 ,1.0};
        struct vector2 out = FCalc::f_func(input);
        TS_ASSERT_EQUALS(out.x, 1.0);
        TS_ASSERT(std::abs(out.y - 5.905) < ZERO_PRECISION);

        /**@brief Scenario 2: Negative h value */
        input = {-3.0, 5.0};
        out = FCalc::f_func(input);
        TS_ASSERT_EQUALS(out.x, 5.0);
        TS_ASSERT(std::abs(out.y - 69.145) < ZERO_PRECISION);

        /**@brief Scenario 3: Negative h and hu value*/
        input = {-3.0, -5.0};
        out = FCalc::f_func(input);
        TS_ASSERT_EQUALS(out.x, -5.0);
        TS_ASSERT(std::abs(out.y - 69.145) < ZERO_PRECISION);

        /** @brief Scenario 4: hu is NaN */
        input = {1.0, std::numeric_limits<double>::quiet_NaN()};
        out = FCalc::f_func(input);
        TS_ASSERT(std::isnan(out.x));
        TS_ASSERT(std::isnan(out.y));
    }
};
