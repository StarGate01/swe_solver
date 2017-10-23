#include <cxxtest/TestSuite.h>
#include "../solver/FDummy.hpp"

class FDummyTestSuite : public CxxTest::TestSuite
{

public:
    
    void testFoo(void)
    {
        TS_ASSERT_EQUALS(FDummy::foo(2, 3), 10);
    }

};