#include "gtest/gtest.h"
#include "babel-types/ast.h"

TEST(test_babel_types_ast, ast)
{
    ast::ArrayExpression arrayExpression;
    EXPECT_EQ(arrayExpression.type, "ArrayExpression");
}