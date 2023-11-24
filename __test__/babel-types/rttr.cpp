#include "gtest/gtest.h"
#include "babel-types/reflect.h"
#include "babel-types/ast_macro.h"
#include "babel-types/ast.h"
#include <rttr/registration>

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

TEST(test_babel_types_rttr, rttr)
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
    t = rttr::type::get<MyStudent>();
    printAttrs(t, "MyStudent");
}
