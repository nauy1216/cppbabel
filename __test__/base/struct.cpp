#ifndef TEST_BABEL_base_struct
#define TEST_BABEL_base_struct

#include "gtest/gtest.h"
#include "babel-log/log.h"

using namespace std;

namespace base_struct
{

    Logger log(__FILE__);

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

    TEST(test_base_struct, base_struct__)
    {
        log << "【struct 占用内存大小】" << log.endl(__LINE__);

        MyStudent1 s = OB(MyStudent1,
                          PROP(age, 18)
                              PROP(name, "namedjfhdjfhdjfhdjfdjfdj"));

        // 40
        log << "sizeof(s)" << sizeof(s) << log.endl(__LINE__);
        log << "sizeof(MyStudent1)" << sizeof(MyStudent1) << log.endl(__LINE__);
        log << "sizeof(s.age)" << sizeof(s.age) << log.endl(__LINE__);
        log << "sizeof(int)" << sizeof(int) << log.endl(__LINE__);
        log << "sizeof(s.name)" << sizeof(s.name) << log.endl(__LINE__);
        log << "sizeof(string)" << sizeof(string) << log.endl(__LINE__);
        log << "sizeof(s.teachers)" << sizeof(s.teachers) << log.endl(__LINE__);
        log << "sizeof(std::vector<std::string *>)" << sizeof(std::vector<std::string *>) << log.endl(__LINE__);
        // log << "sizeof(MyStudent1)" << sizeof(s.func) << log.endl(__LINE__);


        EXPECT_EQ(s.age, 18);
    }

}
#endif // TEST_BABEL_base_struct