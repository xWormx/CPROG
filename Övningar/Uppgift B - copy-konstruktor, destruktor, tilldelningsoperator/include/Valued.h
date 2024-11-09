#ifndef VALUED_H
#define VALUED_H


#include <string>
#include <map>

class Valued
{
    public:
        Valued(std::string str);
        static std::map<std::string, int>& getValues();
    
    private:
        std::string data;
        static std::map<std::string, int> values;
};
    
std::map<std::string, int> Valued::values;

Valued::Valued(std::string str) : data(str)
{
    values[str]++; // Blir 1 första gången
}

std::map<std::string, int>& Valued::getValues()
{
    return values;
}

#endif