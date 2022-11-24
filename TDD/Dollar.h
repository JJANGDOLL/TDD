#pragma once
class Dollar
{
public:
    explicit Dollar(int amount)
    {
        this->amount = amount;
    };
    
    Dollar* times(int multiplier) 
    {
        return new Dollar(amount * multiplier);
    };

    bool equals(Dollar* object)
    {
        return amount == object->amount;
    }

    friend bool operator==(const Dollar& lhs, const Dollar& rhs)
    {
        return lhs.amount == rhs.amount;
    }

private:
    int amount;
};