#ifndef TEST_BABEL_base_inline_function
#define TEST_BABEL_base_inline_function
#include <string>
#include "gtest/gtest.h"
#include "babel-log/log.h"

using namespace std;

/**
1. 函数体较小： 内联函数的函数体通常应该较小，以免导致代码膨胀。
2. 频繁调用： 内联函数适合在程序中频繁调用的地方，以减小函数调用的开销。
3. 在头文件中定义： 内联函数通常在头文件中定义，以便在多个源文件中共享。
4. 避免递归： 内联函数不应该包含递归调用，因为递归调用会导致无限循环展开。
5. 优化建议： 编译器通常会自动决定是否内联函数，因此不一定需要手动指定 inline。可以使用编译器的优化选项。
 */

namespace base_inline_function
{
    Logger log(__FILE__);

    // 定义内联函数，通常在头文件中定义
    inline int add(int a, int b)
    {
        return a + b;
    }

    TEST(test_base_inline_function, base_inline_function__)
    {
        std::cout << "【inline_function】" << endl;
        std::cout << " add(1, 2) " << add(1, 2) << endl;
    }
}
#endif // TEST_BABEL_base_string