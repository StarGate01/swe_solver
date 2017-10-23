#include <cxxtest/TestSuite.h>
#include "../solver/FCore.hpp"
#include "../solver/FCalc.hpp"

class FCoreTestSuite : public CxxTest::TestSuite
{
    friend class FCore;
public:
    void testcompute_zero(void)
    {
        struct qvector zerovector = {0.0, 0.0};
        struct fresult res = FCore::compute(zerovector, zerovector);
        TS_ASSERT(res.adq_positive.x == 0 && res.adq_positive.y == 0);
    }

    void testh_func(void)
    {
        struct qvector ql = {1.0, 2.0};
        struct qvector qr = {3.0, 4.0};
        TS_ASSERT_EQUALS(FCalc::h_func(ql, qr), 0.5*ql.h*qr.h);
    }
};
