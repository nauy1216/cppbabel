#ifndef TEST_BABEL_base_operator
#define TEST_BABEL_base_operator
#include <string>
#include "gtest/gtest.h"
#include "babel-log/log.h"

using namespace std;

/**
3. operator重载
 */

namespace base_operator
{
    Logger log(__FILE__);

    class Time
    {
    public:
        Time(int h = 0, int m = 0, int s = 0);
        Time operator++();
        Time operator++(int);
        void showTime()
        {
            cout << "当前时间为：" << hour << ":" << minute << ":" << second << endl;
        }

    private:
        int hour, minute, second;
    };

    Time::Time(int h, int m, int s)
    {
        this->hour = h;
        this->minute = m;
        this->second = s;
    };

    Time Time::operator++(int n)
    {
        Time tmp = *this;
        ++(*this);
        return tmp;
    }
    Time Time::operator++()
    {
        ++second;
        if (second == 60)
        {
            second = 0;
            ++minute;
            if (minute == 60)
            {
                minute = 0;
                hour++;
                if (hour == 24)
                {
                    hour = 0;
                }
            }
        }
        return *this;
    }

    TEST(test_base_operator, base_operator__)
    {
        std::cout << "【operator】" << endl;

        Time t(23, 59, 59);
        ++t;
        t.showTime();
        (t++).showTime();
        t.showTime();
    }
}
#endif // TEST_BABEL_base_operator