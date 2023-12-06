#ifndef TEST_BABEL_base_enum
#define TEST_BABEL_base_enum
#include <string>
#include "gtest/gtest.h"
#include "babel-log/log.h"

using namespace std;

/**
 * enum（枚举）是一种用于创建命名整数常量的方式。枚举通过为一组整数值分配符号名称，提高了代码的可读性。
 */

namespace base_enum
{
    Logger log(__FILE__);
    // 定义一个枚举类型
    enum Color
    {
        RED,     // 默认值为 0
        GREEN,   // 默认值为 1
        BLUE = 4 // 手动赋值
    };

    string toString(Color c)
    {
        switch (c)
        {
        case RED:
            return "RED";

        default:
            return "UNKNOW";
        };
    };

    TEST(test_base_enum, base_enum)
    {
        log << "【enum】" << log.endl(__LINE__);

        log << "toString(RED)" << toString(RED) << log.endl(__LINE__);
        log << "toString(Color::GREEN)" << toString(Color::GREEN) << log.endl(__LINE__);
    }
}
#endif // TEST_BABEL_base_enum