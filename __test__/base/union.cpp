#ifndef TEST_BABEL_base_union
#define TEST_BABEL_base_union

#include "gtest/gtest.h"
#include "babel-log/log.h"

using namespace std;

/**
 * union 是一种数据结构，允许在同一内存地址存储不同类型的数据。
 * union 中的所有成员共享同一块内存，这使得 union 的大小等于最大成员的大小。
 */

namespace base_union
{
    Logger log(__FILE__);

    union testunion
    {
        struct
        {
            int x;
            int y;
            int z;
        } u;
        int k;
    };

    TEST(test_base_union, base_union_)
    {
        log << "【union】" << log.endl(__LINE__);
        testunion a;

        // 4
        log << "sizeof(int) ==> " << sizeof(int) << log.endl(__LINE__);

        // 12, 3个int的大小
        log << "sizeof(testunion) ==> " << sizeof(testunion) << log.endl(__LINE__);

        a.k = 12;
        // 12
        log << "a.k ==> " << a.k << log.endl(__LINE__);
        // 12, 因为读取的是同一块内存
        log << "a.u.x ==> " << a.u.x << log.endl(__LINE__);
        // 内存的脏数据
        log << "a.u.y ==> " << a.u.y << log.endl(__LINE__);
        // 内存的脏数据
        log << "a.u.z ==> " << a.u.z << log.endl(__LINE__);

        a.u.x = 13;
        a.u.y = 14;
        a.u.z = 15;

        log << "a.k ==> " << a.k << log.endl(__LINE__);
        log << "a.u.x ==> " << a.u.x << log.endl(__LINE__);
        log << "a.u.y ==> " << a.u.y << log.endl(__LINE__);
        log << "a.u.z ==> " << a.u.z << log.endl(__LINE__);
    }
}
#endif // TEST_BABEL_base_union