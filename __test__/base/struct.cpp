#ifndef TEST_BABEL_TYPES_struct
#define TEST_BABEL_TYPES_struct

#include "gtest/gtest.h"

using namespace std;

struct MyStudent1
{
    MyStudent1(){};
    void func(double){};
    int age;
    string name;
    std::vector<std::string *> *teachers;
};

MyStudent1 s = []() -> MyStudent1
{
    MyStudent1 s;
    s.age = 18;
    return s;
}();

TEST(test_base_struct, 结构体字面量)
{
    // struct MyStudent
    // {
    //     MyStudent(){};
    //     void func(double){};
    //     int age;
    //     string name;
    //     std::vector<std::string *> *teachers;
    // };
    // MyStudent s = []() -> MyStudent {
    //     MyStudent s;
    //     s.age = 18;
    //     return s;
    // }();

    // MyStudent *s;
    // s->age = 18;

    EXPECT_EQ(s.age, 18);
}

#endif //TEST_BABEL_TYPES_struct