#include "pch.h"
#include "../TDD/Math.h"
#include "../TDD/Dollar.h"

TEST(testMultiplication, TestName)
{
    Dollar five = Dollar(5);
    five.times(2);
    EXPECT_EQ(10, five.amount);
}

