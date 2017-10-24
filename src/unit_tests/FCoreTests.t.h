/**
 * @file FCoreTests.t.h
 * @brief Unit tests for FCore and FCalc
*/

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
<<<<<<< HEAD
     * Test the implmentation of the F-Wave solver against some precomputed values
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
     * Test to verify the 'h-func' of FCalc by testing a set of predetermined inputs
     * to the ZERO_PRECISION accuracy defined in FConst
    */
=======
     * Test to verify the FCalc::h_func by testing a set of predetermined inputs to the #ZERO_PRECISION accuracy
     */
>>>>>>> d295215491d43c7e62845a018d02f7b6b376531e
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
        TS_ASSERT(abs(FCalc::h_func(ql, qr)) < ZERO_PRECISION); //Test zero input for zero output
    }

    /**
     * Test to verify the 'u_func' of FCalc by testing a set of predetermined inputs
     * to the ZERO_PRECISION accuracy defined in FConst
    */
    void testu_func(void)
    {
        //TODO: Implement precalculated tests
        TS_ASSERT(true);
    }

    /**
     * Test to verify the 'f_func' of FCalc by testing a set of predetermined inputs
     * to the ZERO_PRECISION accuracy defined in FConst
    */
    void testf_func(void)
    {
        //TODO: Implement precalculated tests            
        TS_ASSERT(true);
    }
};
