#ifndef TEST_BABEL_TYPES_reflect
#define TEST_BABEL_TYPES_reflect

#include "gtest/gtest.h"
#include "babel-types/reflect.h"
#include "babel-types/ast.h"

TEST(test_babel_types_reflect, reflect)
{
    // 1.访问自己的属性
    ast::BaseNode baseNode;
    auto end = &ast::BaseNode::end;
    reflect::setProperty(baseNode, end, 1);
    EXPECT_EQ(reflect::getProperty(baseNode, end), 1);

    // 2.访问父类的属性，需要先类型转换成父类
    ast::ArrayExpression arrayExpression;
    ast::BaseNode *arrayExpression_p = &arrayExpression;
    reflect::setProperty(*arrayExpression_p, end, 2);
    EXPECT_EQ(reflect::getProperty(*arrayExpression_p, end), 2);
}
#endif // TEST_BABEL_TYPES_reflect