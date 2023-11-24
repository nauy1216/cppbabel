#include "gtest/gtest.h"
 
TEST(test_test1, test1) {
    EXPECT_EQ (0,  0); //通过
    EXPECT_EQ (4, 4); //通过
    EXPECT_EQ (3, 6); //不通过
}