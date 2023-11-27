#ifndef TEST_BABEL_TYPES_rttr
#define TEST_BABEL_TYPES_rttr

#include "gtest/gtest.h"
#include "babel-types/reflect.h"
#include "babel-types/ast_macro.h"
#include "babel-types/ast.h"
#include <rttr/registration>
// #include "babel-log/log.h"
namespace babel_types_rttr
{

    using rttr::property;
    using rttr::type;

    void printAttrs(rttr::type type, string title)
    {
        for (auto &prop : type.get_properties())
            std::cout << title << ":attrName: " << prop.get_name() << std::endl;
    }

    void printMethods(rttr::type type, string title)
    {
        for (auto &prop : type.get_methods())
            std::cout << title << ":methodName: " << prop.get_name() << std::endl;
    }

    TEST(test_babel_types_rttr, 手写RTTR注册方法)
    {
        struct MyStruct
        {
            MyStruct(){};
            void func(double){};
            int data;
            string name;
            std::vector<int *> *a;

            static void registerRttr()
            {
                registration::class_<MyStruct>("MyStruct")
                    .constructor<>()
                    .property("data", &MyStruct::data)
                    .property("name", &MyStruct::name)
                    .property("a", &MyStruct::a)
                    .method("func", &MyStruct::func);
            }
        };

        MyStruct::registerRttr();
        rttr::type t = rttr::type::get<MyStruct>();
        printAttrs(t, "MyStruct");
        printMethods(t, "MyStruct");
    }

    TEST(test_babel_types_rttr, 宏生成RTTR注册方法)
    {
        struct MyStudent
        {
            MyStudent(){};
            void func(double){};
            int age;
            string name;
            std::vector<std::string *> *teachers;
            RTTR(MyStudent, ATTR3(MyStudent, age, name, teachers))
        };
        MyStudent::registerRttr();
        rttr::type t = rttr::type::get<MyStudent>();
        printAttrs(t, "MyStudent");
    }

    TEST(test_babel_types_rttr, 测试ArrayExpression)
    {
        ast::ArrayExpression::registerRttr();
        rttr::type t = rttr::type::get<ast::ArrayExpression>();
        printAttrs(t, "ast::ArrayExpression");
    }

    struct MyStruct
    {
        const int a = 1;
    };

    TEST(test_babel_types_rttr, 获取常量属性)
    {
        ast::ArrayExpression* c;
        c->end=0;

        int a = c->end;

        ast::RegexLiteral b;
        ast::ArrayExpression::registerRttr();
        ast::ArrayExpression obj;

        // 先获取属性
        property prop = type::get(obj).get_property("type");
        // 获取属性值
        rttr::variant var_prop = prop.get_value(obj);
        // 属性值类型转换

        // Logger::Info("value => " + var_prop.get_value<std::string>());


        MyStruct myStruct;
        EXPECT_EQ(myStruct.a, 1);
        // 或者 auto p = &MyStruct::a;
        const int MyStruct::*p = &MyStruct::a;

        EXPECT_EQ(myStruct.*p, 1);
    }

}
#endif // TEST_BABEL_TYPES_rttr
