#ifndef OPERATOROVERLOAD_H
#define OPERATOROVERLOAD_H

#include <iostream>



/*

    +=
    const OOL& operator+=(const OOL& other);

    +
    const OOL operator+(const OOL& other) const;
    const OOL operator+(int rhs) const;

    ++prefix
    const OOL& operator++(); // returnera *this;

    postfix++
    const OOL operator++(int); returnera temp;

    friend std::ostream& operator<<(std::ostream& os, const OOL& ool);


*/

class OOL
{
    public:
        explicit OOL(int d) : data(d){}

        const OOL& operator+=(const OOL& other); // påverkar sig själv : ol1 += ol2;
        const OOL& operator+=(int rhs); // OBS! om konstruktor är explicit
        const OOL operator+(const OOL& other) const;  // påverkar inte operanderna, returnerar ett nytt objekt : ol1 = ol2 + ol3; obs, 2 argument som frifunktion
        const OOL operator+(int rhs) const;
        const OOL& operator++();     // prefix
        const OOL operator++(int); // postfix
    private:
        int data;
        friend std::ostream& operator<<(std::ostream& os, const OOL& ool);
};

const OOL operator+(int lhs, const OOL& rhs)
{
    return rhs + lhs;
}

const OOL operator+(const OOL& lhs, const OOL& rhs)
{
    OOL temp(lhs);
    temp += rhs;
    return temp;
}

const OOL& OOL::operator+=(int rhs)
{
    data += rhs;
    return *this;
}

const OOL& OOL::operator++() // prefix
{
    return *this += 1;
}

const OOL OOL::operator++(int) // postfix
{
    OOL temp(*this);
    *this += 1;
    return temp;
}

const OOL OOL::operator+(int rhs) const
{
    OOL temp(*this);
    temp.data += rhs;
    return temp;
}

std::ostream& operator<<(std::ostream& os, const OOL& ool)
{
    return os << ool.data;
}

const OOL& OOL::operator+=(const OOL& other)
{
    data += other.data;
    return *this;
}

const OOL OOL::operator+(const OOL& rhs) const
{
    OOL temp(*this);
    temp += rhs; // går att göra föratt += är implementerad för OOL
    return temp;
}

#endif