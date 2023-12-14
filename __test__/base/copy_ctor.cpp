#ifndef TEST_BABEL_base_copy_ctor
#define TEST_BABEL_base_copy_ctor
#include <string>
#include "gtest/gtest.h"
#include "babel-log/log.h"

using namespace std;

/**
 * 拷贝构造函数
 */

namespace base_copy_ctor
{
    Logger log(__FILE__);

    class Time
    {
    private:
        int h, m, s;

    public:
        // 普通构造函数
        Time(int h, int m, int s) : h(h), m(m), s(s){};

        // 拷贝构造函数
        Time(const Time &t)
        {
            this->h = t.h;
            this->m = t.m;
            this->s = t.s;
        };

        ~Time()
        {
            std::cout << "~Time" << endl;
        };

        void show()
        {
            std::cout << "h" << h << " m" << m << " s" << s << endl;
        };
    };

    TEST(test_base_copy_ctor, base_copy_ctor__)
    {
        std::cout << "base_copy_ctor" << endl;
        Time t1(13, 30, 25);
        t1.show();

        Time t2 = t1;
        t2.show();
    }
}
#endif // TEST_BABEL_base_copy_ctor