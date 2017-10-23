#include <cxxtest/TestSuite.h>
#include "../solver/FCore.hpp"
#include "../solver/FStructs.hpp"


class FCoreTestSuite : public CxxTest::TestSuite
{
public:
    void testcompute_zero(void)
    {
        struct qvector zerovector = {0.0, 0.0};
        struct fresult res = FCore::compute(zerovector, zerovector);
        TS_ASSERT(res.adq_positive.x == 0 && res.adq_positive.y == 0);
    }

};
