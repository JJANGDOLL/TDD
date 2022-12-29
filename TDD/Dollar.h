#pragma once

#include <typeinfo>
#include <Windows.h>
#include <tchar.h>
#include <debugapi.h>
#include <string>

class Money;

interface IExpression
{
    virtual Money* reduce(std::string to) = 0;
};

class Money : public IExpression
{
public:
    explicit Money(int amount, std::string currency)
    {
        this->amount = amount;
        this->currency = currency;
    }


    Money* reduce(std::string to) override
    {
        return this;
    }

public:
    int amount;


public:
    friend bool operator==(const Money& lhs, const Money& rhs)
    {
        return (lhs.amount == rhs.amount) && (lhs.getCurrency() == rhs.getCurrency());
    }

//     friend IExpression operator+(const Money& lhs, const Money& rhs);

public:
    virtual const type_info& getClass() const
    {
        return typeid(*this);
    }

    static Money* dollar(int amount);
    static Money* franc(int amount);

    Money* times(int multiplier)
    {
        return new Money(amount * multiplier, currency);
    }

    std::string getCurrency() const
    {
        return currency;
    }

protected:
    std::string currency;
};

// class Dollar : public Money
// {
// public:
//     explicit Dollar(int amount, std::string InCurrency)
//         : Money(amount, InCurrency)
//     {
//     };
// 
//     bool equals(Dollar* object)
//     {
//         return amount == object->amount;
//     }
// };

Money* Money::dollar(int amount)
{
    return new Money(amount, "USD");
}

// class Franc : public Money
// {
// public:
//     explicit Franc(int amount, std::string InCurrency)
//         : Money(amount, InCurrency)
//     {
//     };
// 
//     bool equals(Franc* object)
//     {
//         return amount == object->amount;
//     }
// };


Money* Money::franc(int amount)
{
    return new Money(amount, "CHF");
}

class Bank
{
public:
    Money* reduce(IExpression& source, std::string to);
};

class Sum : public IExpression
{
public:
    Sum(const Money& InAugend, const Money& InAddend)
        : augend(InAugend), addend(InAddend)
    {

    }

    Money* reduce(std::string to)
    {
        int amount = augend.amount + addend.amount;
        return new Money(amount, to);
    }

    const Money& augend;
    const Money& addend;
};

Money* Bank::reduce(IExpression& source, std::string to)
{
    return source.reduce(to);
}

IExpression* operator+(const Money& lhs, const Money& rhs)
{
    IExpression* added = new Sum(lhs, rhs);
    return added;
}

