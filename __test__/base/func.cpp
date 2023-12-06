#ifndef TEST_BABEL_base_func
#define TEST_BABEL_base_func

#include "gtest/gtest.h"
#include <vector>
#include <iostream>
#include "babel-log/log.h"
#include <cstdarg>
#include <initializer_list>

#include "../utils/struct.h"

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
    int sum2(std::initializer_list<int> args)
    {
        int result = 0;
        for (int arg : args)
        {
            result += arg;
        }
        return result;
    }

    /**
     * 函数使用可变参数的2种方式
    */
    TEST(TEST_base_func, base_func_args)
    {
        log << "【可变参数】 " << log.endl(__LINE__);
        int result = sum(3, 1, 2, 3);
        log << " sum(3, 1, 2, 3) => " << result << log.endl(__LINE__);
        log << " sum2({1, 2, 3}) => " << sum2({1, 2, 3}) << log.endl(__LINE__);
    }

    void modifyObj(utils_struct::Student old)
    {
        old.age = 13;
        log << " 传参数之后的地址：  " << &old << log.endl(__LINE__);
    };

    /**
     * 对象作为函数参数会复制一个新的对象
    */
    TEST(TEST_base_func, base_func_args_struct)
    {
        log << "【对象作为参数】 " << log.endl(__LINE__);
        utils_struct::Student s1(12, "aaa");
        log << " 传参数之前的地址：  " << &s1 << log.endl(__LINE__);
        log << " age ==>  " << s1.age << log.endl(__LINE__);
        modifyObj(s1);
        log << " age ==>  " << s1.age << log.endl(__LINE__);
    };


    utils_struct::Student getNewObj(utils_struct::Student s) {
        log << " 参数的地址 ==>  " << &s << log.endl(__LINE__);
        return s;
    };

    /**
     * 返回值也是一个复制对象
    */
    TEST(TEST_base_func, base_func_return_struct)
    {
        log << "【对象作返回值】 " << log.endl(__LINE__);
        utils_struct::Student s1(12, "aaa");
        log << " 传参数之前的地址 ==>  " << &s1 << log.endl(__LINE__);
        utils_struct::Student s2 = getNewObj(s1);
        log << " 返回值的地址 ==>  " << &s2 << log.endl(__LINE__);
    };



    void modifyObj(utils_struct::Student* old)
    {
        old -> age = 13;
        log << " 传参数之后的地址：  " << old << log.endl(__LINE__);
    };

    TEST(TEST_base_func, base_func_args_pointer)
    {
        log << "【指针传参】 " << log.endl(__LINE__);
        utils_struct::Student s1(12, "aaa");
        log << " 传参数之前的地址 ==>  " << &s1 << log.endl(__LINE__);
        log << " s1.age " << s1.age << log.endl(__LINE__);
        modifyObj(&s1);
        log << " s1.age " << s1.age << log.endl(__LINE__);
    };

    utils_struct::Student* getNewObjPointer(utils_struct::Student* old)
    {
        old -> age = 13;
        log << " 传参数之后的地址：  " << old << log.endl(__LINE__);
        return old;
    };


    /**
     * 指针作为参数，返回传入的指针
    */
    TEST(TEST_base_func, base_func_return_pointer)
    {
        log << "【参数是指针，返回指针】 " << log.endl(__LINE__);
        utils_struct::Student s1(12, "aaa");

        log << " 传参数之前的地址 ==>  " << &s1 << log.endl(__LINE__);
        log << " s1.age " << s1.age << log.endl(__LINE__);
        utils_struct::Student* s2 = getNewObjPointer(&s1);
        log << " s2->age " << s2->age << log.endl(__LINE__);
        log << " 返回的指针 " << s2 << log.endl(__LINE__);
    };


    // 错误示例
    // utils_struct::Student* getNewObjPointer(utils_struct::Student old)
    // {
    //     old.age = 13;
    //     log << " 传参数之后的地址：  " << old << log.endl(__LINE__);
    //     return &old;
    // };


    void modifyObjByRef(utils_struct::Student& old)
    {
        old.age = 13;
        log << " 传参数之后的地址：  " << &old << log.endl(__LINE__);
    };

    TEST(TEST_base_func, base_func_args_ref)
    {
        log << "【参数是引用】 " << log.endl(__LINE__);
        utils_struct::Student s1(12, "aaa");

        log << " 传参数之前的地址 ==>  " << &s1 << log.endl(__LINE__);
        log << " s1.age " << s1.age << log.endl(__LINE__);
        modifyObjByRef(s1);
        log << " s1.age " << s1.age << log.endl(__LINE__);
    };

    /**
     * 错误用法
    */
    // utils_struct::Student& getNewObjRef(utils_struct::Student old)
    // {
    //     old.age = 13;
    //     log << " 传参数之后的地址：  " << old << log.endl(__LINE__);
    //     return old;
    // };
    utils_struct::Student& getNewObjRef(utils_struct::Student& old)
    {
        old.age = 13;
        log << " 传参数之后的地址：  " << &old << log.endl(__LINE__);
        return old;
    };


    TEST(TEST_base_func, base_func_return_ref)
    {
        log << "【返回是引用】 " << log.endl(__LINE__);
        utils_struct::Student s1(12, "aaa");

        log << " 传参数之前的地址 ==>  " << &s1 << log.endl(__LINE__);
        log << " s1.age " << s1.age << log.endl(__LINE__);
        utils_struct::Student& s2 = getNewObjRef(s1);
        log << " 返回的地址 " << &s2 << log.endl(__LINE__);
    };

    TEST(TEST_base_func, base_func_lambda)
    {
        log << "【lambda】 " << log.endl(__LINE__);

        int first_num = 1;

        auto add = [first_num](int a) -> int {
            return first_num + a;
        };

        log << " add(2) ==>" << add(2) << log.endl(__LINE__);
    };

}
#endif // TEST_BABEL_base_func