#ifndef TEST_BABEL_base_friend_function
#define TEST_BABEL_base_friend_function
#include <string>
#include "gtest/gtest.h"
#include "babel-log/log.h"

using namespace std;

/**
 * 拷贝构造函数
 */

namespace base_friend_function
{
    Logger log(__FILE__);

    class Calc;

    class Point
    {
    public:
        Point(int x = 0, int y = 0) : X(x), Y(y) {}
        int GetX() { return X; }
        int GetY() { return Y; }
        // 友元函数
        friend float Distance(Point &a, Point &b);
        // 友元类
        friend Calc;

    private:
        int X, Y; // 私有数据成员
    };

    // 通过将一个模块声明为另一个模块的友元，
    // 一个模块能够引用到另一个模块中本是被隐藏的信息。
    // 函数名必须保持一致
    float Distance(Point &a, Point &b)
    {
        double dx = a.X - b.X;
        double dy = a.Y - b.Y;
        return sqrt(dx * dx + dy * dy);
    };

    class Calc
    {
    public:
        float Distance(Point &a, Point &b)
        {
            double dx = a.X - b.X;
            double dy = a.Y - b.Y;
            return sqrt(dx * dx + dy * dy);
        };
    };

    TEST(test_base_friend_function, base_friend_function__)
    {
        std::cout << "base_friend_function" << endl;

        Point p1(3.0, 5.0), p2(4.0, 6.0);

        std::cout << Distance(p1, p2) << endl;

        Calc c;

        std::cout << c.Distance(p1, p2) << endl;
    }
}
#endif // TEST_BABEL_base_friend_function