#pragma once

#include <typeinfo>
#include <Windows.h>
#include <tchar.h>
#include <debugapi.h>
#include <string>
#include <unordered_map>

class Money;
class Bank;

interface IExpression
{
    virtual Money* reduce(Bank* bank, std::string to) = 0;
};

class Money : public IExpression
{
public:
    explicit Money(int amount, std::string currency)
    {
        this->amount = amount;
        this->currency = currency;
    }


    Money* reduce(Bank *bank, std::string to) override;

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

class Pair;

class Bank
{
public:
    Money* reduce(IExpression& source, std::string to);

    int rate(std::string from, std::string to);

    std::unordered_map<int, int> rates;

    void addRate(std::string from, std::string to, int rate);
};

class Sum : public IExpression
{
public:
    Sum(const Money& InAugend, const Money& InAddend)
        : augend(InAugend), addend(InAddend)
    {

    }

    Money* reduce(Bank* bank, std::string to) override
    {
        int amount = augend.amount + addend.amount;
        return new Money(amount, to);
    }

    const Money& augend;
    const Money& addend;
};

Money* Bank::reduce(IExpression& source, std::string to)
{
    return source.reduce(this, to);
}

IExpression* operator+(const Money& lhs, const Money& rhs)
{
    IExpression* added = new Sum(lhs, rhs);
    return added;
}

Money* Money::reduce(Bank* bank, std::string to)
{
    int rate = bank->rate(currency, to);

    return new Money(amount / rate, to);
}

class Pair
{
public:
    std::string from;
    std::string to;

    Pair(std::string InFrom, std::string InTo)
        : from(InFrom), to(InTo)
    {
    }

    bool equals(void* object)
    {
        Pair* pair = static_cast<Pair*>(object);
        return from == pair->from && to == pair->to;
    }

    int hashCode()
    {
        return 0;
    }
};

void Bank::addRate(std::string from, std::string to, int rate)
{
    Pair* pair = new Pair(from, to);
    rates[pair->hashCode()] = rate;
}

int Bank::rate(std::string from, std::string to)
{
    if (from == to) return 1;

    Pair* pair = new Pair(from, to);
    int rate = rates[pair->hashCode()];
    return rate;
}
