#ifndef TEST_BABEL_base_struct
#define TEST_BABEL_base_struct

#include "gtest/gtest.h"

using namespace std;

namespace base_struct
{

#define OB(StructName, ...) \
    [] {                    \
        StructName t;       \
        __VA_ARGS__         \
        return t;           \
    }()

#define PROP(name, value) \
    t.name = value;

    struct MyStudent1
    {
        MyStudent1(){};
        void func(double){};
        int age;
        string name;
        std::vector<std::string *> *teachers;
    };

    TEST(test_base_struct, base_struct_)
    {
        MyStudent1 s = OB(MyStudent1,
                          PROP(age, 18)
                          PROP(name, "name"));


        EXPECT_EQ(s.age, 18);
    }





}
#endif // TEST_BABEL_base_struct