#ifdef __CHECK_MEMORY_LEAKS__
    #define _CRTDBG_MAP_ALLOC
    #include <stdlib.h>
    #include <crtdbg.h>

    #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

#include "data_test/ArrayTest.hpp"
#include "data_test/VectorTest.hpp"
#include "data_test/ListTest.hpp"
#include "performance_test/VectorPerformance.hpp"
#include "performance_test/ListPerformance.hpp"
#include "performance_test/DataStructuresComparison.hpp"

#define __DATA_STRUCTURES_TESTS__ 1
#define __PERFORMANCE_TESTS__ 1
#define __COMPARE_DATA_STRUCTURES__ 1

int main()
{
#if __DATA_STRUCTURES_TESTS__
    {
        ArrayTest::RunAllTest();
        VectorTest::RunAllTest();
        ListTest::RunAllTest();
    }
#endif
#if __PERFORMANCE_TESTS__
    {
        VectorPerformance::RunAllTest();
        ListPerformance::RunAllTest();
    }
#endif
#if __COMPARE_DATA_STRUCTURES__
    {
        DataStructuresComparison::RunAllTest();
    }
#endif

#ifdef __CHECK_MEMORY_LEAKS__
    _CrtDumpMemoryLeaks();
#endif

    return 0;
}
