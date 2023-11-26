#ifndef TEST_BABEL_TYPES_utils
#define TEST_BABEL_TYPES_utils

#include "gtest/gtest.h"
#include "babel-types/utils.h"

TEST(test_babel_types_utils, shallowEqual)
{
    EXPECT_EQ(utils::shallowEqual(1, 1), true);  
    EXPECT_EQ(utils::shallowEqual(1, 2), false);
    EXPECT_EQ(utils::shallowEqual(1, 4), false);
}
#endif //TEST_BABEL_TYPES_utils