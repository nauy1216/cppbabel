#ifndef TEST_BABEL_base_optional
#define TEST_BABEL_base_optional
#include <string>
#include <optional>

#include "gtest/gtest.h"
#include "babel-log/log.h"

using namespace std;

/**
 * std::optional
 * 1. 表示一个可能有值的对象（没有值时就是默认的std::nullopt)。
 * 2. 特别适用于处理可能有或可能没有值的情况。
 */

namespace base_optional
{
    Logger log(__FILE__);

    std::optional<int> get(int a)
    {
        if (a == 1)
        {
            return 100;
        }
        return std::nullopt;
    };

    TEST(test_base_optional, base_optional__)
    {
        log << "【base_optional】" << log.endl(__LINE__);
        // 等同std::optional<int> maybeInt = std::nullopt;
        std::optional<int> maybeInt;                // 未初始化的 optional
        std::optional<double> perhapsDouble = 3.14; // 初始化的 optional，包含一个值

        if (perhapsDouble.has_value())
        {   
            // 第1种取值的方式
            log << "perhapsDouble.value() ==> " << perhapsDouble.value() << log.endl(__LINE__);
            // 第2种取值的方式
            log << "*perhapsDouble ==> " << *perhapsDouble << log.endl(__LINE__);
        }

        // 第3种取值的方式 提供默认值
        log << "maybeInt.value_or(10) ==> " << maybeInt.value_or(10) << log.endl(__LINE__);

        // 赋值
        maybeInt.emplace(5);
        log << "maybeInt.value_or(10) ==> " << maybeInt.value_or(10) << log.endl(__LINE__);

        std::optional<int> maybeRes = get(10);
        // 也可以通过 maybeRes != std::nullopt 判断
        if (!maybeRes.has_value())
        {
            // maybeRes == std::nullopt ==> 1
            log << "maybeRes == std::nullopt ==> " << (maybeRes == std::nullopt) << log.endl(__LINE__);
        }
    }

    TEST(test_base_optional, base_optional__2)
    {

        bool is_even = true;

        // 在 没有赋实际值的情况下 std::optional 对象的默认值为 std::nullopt
        std::optional<int> even_value = is_even ? std::optional<int>(128) : std::nullopt;

        // 可以用 std::optional 对象是否等于 std::nullopt 来判断 std::optional 对象是否有值
        if (even_value != std::nullopt)
        {
            // 采用.value 获取 std::optional 对象的值
            log << "has value, which is " << even_value.value() << log.endl(__LINE__);
        }
        else
        {
            log << "no value" << log.endl(__LINE__);
        }

        std::optional<int> val8 = std::make_optional(128);
        log << "使用 std::make_optional ==> " << val8.value() << log.endl(__LINE__);
    }
}
#endif // TEST_BABEL_base_optional