#include "pch.h"
#include "../TDD/Math.h"
#include "../TDD/Dollar.h"


TEST(testMultiplication)
{
    Money* five = Money::dollar(5);
    EXPECT_EQ(*(Money::dollar(10)), *(five->times(2)));
    EXPECT_EQ(*(Money::dollar(15)), *(five->times(3)));
};

TEST(testFrancMultiplication)
{
    Money* five = Money::franc(5);
    EXPECT_EQ(*(Money::franc(10)), *(five->times(2)));
    EXPECT_EQ(*(Money::franc(15)), *(five->times(3)));
};

TEST(testEquality)
{
    EXPECT_TRUE(*(Money::dollar(5)) == *(Money::dollar(5)));
    EXPECT_FALSE(*(Money::dollar(5)) == *(Money::dollar(6)));
    EXPECT_TRUE(*(Money::franc(5)) == *(Money::franc(5)));
    EXPECT_FALSE(*(Money::franc(5)) == *(Money::franc(6)));
    EXPECT_FALSE(*(Money::dollar(5)) == *(Money::franc(5)));
}

TEST(testCurrency)
{
    EXPECT_EQ(std::string("CHF"), "CHF");
    EXPECT_EQ(std::string("USD"), "USD");
}

TEST(testDifferenctClassEquality)
{
//     EXPECT_EQ(*(new Money(10, "CHF")), *(new Franc(10, "CHF")));
}

TEST(testSimpleAdditiion)
{
    Money* five = Money::franc(5);
    IExpression* result = *five + *five;
    Sum* sum = static_cast<Sum*>(result);
    EXPECT_EQ(*five, sum->augend);
    EXPECT_EQ(*five, sum->augend);
}

TEST(testReduceSum)
{
    IExpression* sum = new Sum(*Money::dollar(3), *Money::dollar(4));
    Bank bank;
    Money* result = bank.reduce(*sum, "USD");
    EXPECT_EQ(*Money::dollar(7), *result);
}

TEST(testReduceMoney)
{
    Bank* bank = new Bank();
    Money* result = bank->reduce(*Money::dollar(1), "USD");
    EXPECT_EQ(*Money::dollar(1), *result);
}