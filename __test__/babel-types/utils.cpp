#include "gtest/gtest.h"
#include "babel-types/utils.h"

TEST(test_babel_types_utils, shallowEqual)
{
    // ast::ArrayExpression arrayExpression;
    EXPECT_EQ(utils::shallowEqual(1, 1), true);  // 通过
    EXPECT_EQ(utils::shallowEqual(1, 2), false); // 通过
    // EXPECT_EQ (4, 4); //通过
    // EXPECT_EQ (3, 6); //不通过
}