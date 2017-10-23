/**
 * @file FCoreTests.t.h
 * @brief Header with implemtentation of tests for the F-Wave solver
*/

#include <cxxtest/TestSuite.h>
#include "../solver/FCore.hpp"
#include "../solver/FCalc.hpp"

/**
 * @bief Definition and implementations of tests for the F-Wave solver
 * 
 * This class provides the necessary tests to verify the implementation of
 * the F-Wave solver and the helper methods in 'FCalc'.
*/
class FCoreTestSuite : public CxxTest::TestSuite
{
    friend class FCore;
public:
    /**
     * Test to verify, that a zero vector is returned by the compute method
     * when feeded with parameters ql=qr={0,0}
    */
    void testcompute_zero(void)
    {
        struct qvector zerovector = {0.0, 0.0};
        struct fresult res = FCore::compute(zerovector, zerovector);
        TS_ASSERT(res.adq_positive.x == 0 && res.adq_positive.y == 0);
    }

    /**
     * Test to verify the 'h-func' of FCalc by testing a set of predetermined inputs
     * to the ZERO_PRECISION accuracy defined in FConst
    */
    void testh_func(void)
    {
        //(3.0 + 1.0)/2 = 2
        struct qvector ql = {1.0, 2.0};
        struct qvector qr = {3.0, 4.0};
        TS_ASSERT(abs(FCalc::h_func(ql, qr) - 2) < ZERO_PRECISION);

        //(-3.0+5.0)/2 = 1
        ql = {-3.0, 2.0};
        qr = {5.0, 4.0};
        TS_ASSERT(abs(FCalc::h_func(ql, qr) - 1) < ZERO_PRECISION);

        //(0.0 + 0.0)/2 = 0
        ql = {0.0, 0.0}
        TS_ASSERT(abs(FCalc::h_func(ql, qr)) < ZERO_PRECISION); /**< Test zero input for zero output*/
    }
};
