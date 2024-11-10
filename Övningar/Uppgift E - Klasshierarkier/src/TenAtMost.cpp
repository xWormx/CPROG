#include "TenAtMost.h"


int TenAtMost::count = 0;

TenAtMost* TenAtMost::getInstance(std::string n)
{
    return new TenAtMost(n);
}

TenAtMost::TenAtMost(std::string n) : name(n)
{
    ++count;
    try
    {
        if(count > 10)
            throw std::out_of_range("Fel: Fler än 10 objekt!\n");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

TenAtMost::~TenAtMost()
{
    --count;
}

std::string TenAtMost::getName() const
{
    return name;
}