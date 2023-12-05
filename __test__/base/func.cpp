#ifndef TEST_base_func
#define TEST_base_func

#include "gtest/gtest.h"
#include <vector>
#include <iostream>
#include "babel-log/log.h"
#include <cstdarg>
#include <initializer_list>

using namespace std;

namespace base_func
{
    Logger log(__FILE__);

    /**
     * 定义可变参数函数
     * count 参数的个数
    */
    int sum(int count, ...)
    {
        va_list args;
        va_start(args, count);

        int result = 0;
        for (int i = 0; i < count; ++i)
        {
            result += va_arg(args, int);
        }

        va_end(args);

        return result;
    }


    // 使用 initializer_list 的可变参数函数
    int sum2(std::initializer_list<int> args) {
        int result = 0;
        for (int arg : args) {
            result += arg;
        }
        return result;
    }

    TEST(TEST_base_base_func, func_args)
    {
        log.Info("测试可变参数  ==>  ");

        int result = sum(3, 1, 2);

        log.Info(result);

        log.Info(sum2({1, 2, 3}))->Endl(__LINE__);
    }
}
#endif // TEST_base_func