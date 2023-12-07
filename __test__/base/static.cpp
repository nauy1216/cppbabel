#ifndef TEST_BABEL_base_static
#define TEST_BABEL_base_static
#include <string>
#include "gtest/gtest.h"
#include "babel-log/log.h"

using namespace std;

    // /**
    //  * 在类中声明的变量，使用 static 修饰符，它是该类的所有实例共享的变量。
    //  */
    // class ExampleClass
    // {
    // public:
    //     static int staticMemberVariable; // 静态成员变量
    // };

/**
 * 静态变量是在程序运行期间分配固定内存地址的变量，其生命周期延长到整个程序运行结束。
 * 在不同的上下文中，"静态变量" 可以有不同的含义。
 * 在 C++ 中，有两种主要的静态变量：静态局部变量和静态成员变量。
 */

namespace base_static
{
    Logger log(__FILE__);

    /**
     *  静态局部变量：在函数内部声明的变量，使用 static 修饰符
     *  1. 其生命周期延长到整个程序运行结束。
     *  2. 但只在声明它的函数内可见。
     */
    void exampleFunction()
    {
        static int staticLocalVariable = 0; // 静态局部变量
        staticLocalVariable++;
        log << " staticLocalVariable ==> " << staticLocalVariable << log.endl(__LINE__);
    };

    TEST(test_base_static, base_static__)
    {
        log << "【static】" << log.endl(__LINE__);
        exampleFunction();
        exampleFunction();
        exampleFunction();

        // ExampleClass obj1;
        // ExampleClass obj2;

        // ExampleClass::staticMemberVariable = 0;
        // obj1.staticMemberVariable++;
        // obj2.staticMemberVariable++;
        // log << " obj1.staticMemberVariable ==> " << obj1.staticMemberVariable << log.endl(__LINE__);
        // log << " obj2.staticMemberVariable ==> " << obj2.staticMemberVariable << log.endl(__LINE__);
    };
}
#endif // TEST_BABEL_base_static