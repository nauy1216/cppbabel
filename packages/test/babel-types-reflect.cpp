#include <iostream>
#include <any>
#include <map>
#include <tuple>
#include "../babel-types/ast.cpp"
#include "../babel-types/var.cpp"
#include "../babel-types/reflect.cpp"
#include "../babel-log/log.h"

#include <rttr/registration>
using namespace rttr;

struct MyStruct
{
    MyStruct(){};
    void func(double){};
    int data;
    string name;
};

RTTR_REGISTRATION
{
    registration::class_<MyStruct>("MyStruct")
        .constructor<>()
        .property("data", &MyStruct::data)
        .property("name", &MyStruct::name)
        .method("func", &MyStruct::func);
}

void test_babel_types_reflect()
{
    Logger::Info("test_babel_types_reflect");

    type t = type::get<MyStruct>();
    for (auto &prop : t.get_properties())
        std::cout << "name: " << prop.get_name() << std::endl;

    for (auto &meth : t.get_methods())
        std::cout << "name: " << meth.get_name() << std::endl;

    // ast::NumberLiteral numberLiteral;
    // std::tuple range(1,2);

    // numberLiteral.range = &range;

    // MyClass obj(42);
    // auto it = &MyClass::myAttribute;
    // std::cout << "Dynamic attribute value: " << reflect::getProperty(obj, it) << std::endl;
    // reflect::setProperty(obj, it, 55);
    // std::cout << "Dynamic attribute value: " << reflect::getProperty(obj, it) << std::endl;
};