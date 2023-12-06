#ifndef TEST_BABEL_base_string_enum
#define TEST_BABEL_base_string_enum

#include "gtest/gtest.h"
#include <rttr/registration>
#include <string>

using namespace std;

namespace base_string_enum
{

    enum charcodes
    {
        a,
        b,
        c,
        d
    };

#define ENUM_VAULE(enumName, name) \
    case enumName::name:           \
        result = #name;            \
        break;

#define ENUM_GETTER(enumName, ...)       \
    string enum_##enumName(enumName key) \
    {                                    \
        string result = "";              \
        switch (key)                     \
        {                                \
            __VA_ARGS__                  \
        };                               \
                                         \
        return result;                   \
    }

    ENUM_GETTER(charcodes, ENUM_VAULE(charcodes, a) ENUM_VAULE(charcodes, b) ENUM_VAULE(charcodes, c) ENUM_VAULE(charcodes, d))

    TEST(test_base_string_enum, base_string_enum_)
    {
        //  rttr::registration::class_<MyClass>("MyClass")
        //         .property("staticVar", &MyClass::staticVar);

        EXPECT_EQ(enum_charcodes(charcodes::a), "a");
        EXPECT_EQ(enum_charcodes(charcodes::b), "b");
        EXPECT_EQ(enum_charcodes(charcodes::c), "c");
        EXPECT_EQ(enum_charcodes(charcodes::d), "d");
    }
}
#endif // TEST_BABEL_base_string_enum