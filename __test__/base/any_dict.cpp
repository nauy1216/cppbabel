#ifndef TEST_BABEL_TYPES_any_dict
#define TEST_BABEL_TYPES_any_dict

#include "gtest/gtest.h"
#include <rttr/registration>
#include <string>
#include <stdexcept>
#include <any>
#include <map>
#include "babel-shared/any_map.h"

using namespace std;
using shared::AnyMap;
using shared::Attr;

#define STRUCT_GETTER(structName, ...)                        \
    Attr get(string attr)                                     \
    {                                                         \
        __VA_ARGS__                                           \
        throw std::runtime_error("This is a runtime error!"); \
    }

#define STUCT_ATTR(structName, attrName)    \
    if (attr == #attrName)                  \
    {                                       \
        auto p = &structName::attrName;     \
        return Attr(#attrName, (*this).*p); \
    }

#define ANY_MAP(structName, attrName)      \
    STRUCT_GETTER(AnyDict,                 \
                  STUCT_ATTR(AnyDict, age) \
                      STUCT_ATTR(AnyDict, name))

struct AnyDict
{
    int age;
    string name;

    STRUCT_GETTER(AnyDict,
                  STUCT_ATTR(AnyDict, age)
                      STUCT_ATTR(AnyDict, name))
};

void test_Attr(){
    //   Attr a1("a1", "string1");
   
    // EXPECT_EQ(a1.exist(), true);
    // EXPECT_EQ(a1.name(), "a1");
    // EXPECT_EQ(a1.value<string>(), "string1");

    Attr a2("a2", 1);
    EXPECT_EQ(a2.exist(), true);
    EXPECT_EQ(a2.name(), "a2");
    EXPECT_EQ(a2.value<int>(), 1);


    Attr a3("a3", true);
    EXPECT_EQ(a3.exist(), true);
    EXPECT_EQ(a3.name(), "a3");
    EXPECT_EQ(a3.value<bool>(), true);

    any test_s = string("ssdsd");
    std::cout << std::any_cast<std::string>(test_s) << std::endl;
};

void test_AnyMap()
{
    AnyMap anyMap;
    anyMap.set("test_int", 1);
    Attr attr1 = anyMap.get("test_int");

    EXPECT_EQ(attr1.exist(), true);
    EXPECT_EQ(attr1.name(), "test_int");
    EXPECT_EQ(attr1.value<int>(), 1);
    EXPECT_EQ(anyMap.get("test_int").value<int>(), 1);

    anyMap.set("test_int", 2);
    Attr attr2 = anyMap.get("test_int");
    EXPECT_EQ(attr1.exist(), true);
    EXPECT_EQ(attr1.name(), "test_int");
    EXPECT_EQ(attr1.value<int>(), 1);
    EXPECT_EQ(attr2.exist(), true);
    EXPECT_EQ(attr2.name(), "test_int");
    EXPECT_EQ(attr2.value<int>(), 2);

    EXPECT_EQ(anyMap.has("test_string"), false);
    // 赋值string类型，必须用string()的形式，否则是一个常量不能进行类型转换
    anyMap.set("test_string", string("a"));
    EXPECT_EQ(anyMap.has("test_string"), true);
    EXPECT_EQ(anyMap.get("test_string").value<string>(), "a");
    EXPECT_EQ(anyMap.value<string>("test_string"), "a");

}

TEST(test_base_any_dict, 任意类型的Map)
{
    test_Attr();
    test_AnyMap();
}
#endif // TEST_BABEL_TYPES_any_dict