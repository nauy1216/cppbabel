#ifndef BABEL_TYPES_TEST_AST
#define BABEL_TYPES_TEST_AST

#include <iostream>
#include <any>
#include <map>
#include "../ast.cpp"
#include "../var.cpp"
#include "../../babel-log/log.h"

using namespace std;

class MyClass
{
public:
    int myAttribute;

    MyClass(int value) : myAttribute(value) {}
};

template <typename T>
class ReflectiveObject
{
private:
    std::map<std::string, any> attributeMap;

public:
    ReflectiveObject(std::map<std::string, any> &attributeMap)
    {
        this->attributeMap = attributeMap;
    }

    int getAttributeValue(MyClass &obj, const std::string &attributeName)
    {
        auto it = attributeMap.find(attributeName);
        if (it != attributeMap.end())
        {
            return obj.*(it->second);
        }
        else
        {
            throw std::invalid_argument("Attribute not found");
        }
    }

    void setAttributeValue(MyClass &obj, const std::string &attributeName, int value)
    {
        auto it = attributeMap.find(attributeName);
        if (it != attributeMap.end())
        {
            obj.*(it->second) = value;
        }
        else
        {
            throw std::invalid_argument("Attribute not found");
        }
    }
};

void test_babel_types_ast()
{
    ast::NumberLiteral numberLiteral;
    ast::NullLiteral nullLiteral;
    ast::Directive directive;
    ast::RestProperty restProperty;
};

void test_babel_types()
{
    Logger::Info("test_babel_types");
    test_babel_types_ast();
}

#endif // BABEL_TYPES_TEST_AST