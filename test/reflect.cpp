#ifndef BABEL_TYPES_TEST_REFLECT
#define BABEL_TYPES_TEST_REFLECT
#include <iostream>
#include <any>
#include <map>
#include <tuple>
#include <vector>
#include <variant>
#include "../ast.cpp"
#include "../var.cpp"
#include "../reflect.cpp"
#include "../../babel-log/log.h"

#include <rttr/registration>
using namespace rttr;

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

struct SpreadElement
{
};

struct Expression
{
};

struct ArrayExpression
{
    string type = "ArrayExpression";
    std::vector<std::variant<Expression *, Expression *>> *elements;
    static void registerRttr()
    {
        registration::class_<ArrayExpression>("ArrayExpression")
            .constructor<>()
            .property("type", &ArrayExpression::type)
            .property("elements", &ArrayExpression::elements);
    }
};

void test_babel_types_reflect()
{
    Logger::Info("test_babel_types_reflect");

    MyStruct::registerRttr();
    type t = type::get<MyStruct>();
    for (auto &prop : t.get_properties())
        std::cout << "name: " << prop.get_name() << std::endl;

    for (auto &meth : t.get_methods())
        std::cout << "name: " << meth.get_name() << std::endl;

    // type b = type::get<ast::BaseNode>();
    // for (auto &prop : b.get_properties())
    //     std::cout << "attr name: " << prop.get_name() << std::endl;

    // for (auto &meth : b.get_methods())
    //     std::cout << "mthod name: " << meth.get_name() << std::endl;

    std::cout << "ast::ArrayExpression \n"
              << std::endl;
    ast::ArrayExpression::registerRttr();

    type arrayExpression = type::get<ast::ArrayExpression>();

    for (auto &prop : arrayExpression.get_properties())
        std::cout << "attr name: " << prop.get_name() << std::endl;

    ast::ArrayExpression obj;
    property prop_s = type::get(obj).get_property("start");
    prop_s.set_value(obj, 23);

    rttr::variant var_prop = prop_s.get_value(obj);
    int value = var_prop.get_value<int>();
    std::cout << value << std::endl;
};

#endif // BABEL_TYPES_TEST_REFLECT