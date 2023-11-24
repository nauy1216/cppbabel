#ifndef BABEL_TYPES_TEST_REFLECT_NEW
#define BABEL_TYPES_TEST_REFLECT_NEW

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

struct MyTestStruct
{
    MyTestStruct(){};
    void func(double){};
    int data;
    string name;
    std::vector<int *> *a;

    static std::array<std::string, 3> attr_array;
    static std::array<std::any, 3> attr_pointer_array;
    static void registerRttr()
    {
        attr_array = std::array<std::string, 3>({
            "data",
            "name",
            "a"
        });

        attr_pointer_array = std::array<std::any, 3>({
            &MyTestStruct::data,
            &MyTestStruct::name,
            &MyTestStruct::a,
        });
    }
};

void test_babel_reflect_new()
{
    Logger::Info("test_babel_reflect_new");

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
};

#endif // BABEL_TYPES_TEST_REFLECT_NEW