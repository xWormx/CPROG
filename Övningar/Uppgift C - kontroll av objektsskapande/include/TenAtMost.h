#ifndef TENATMOST_H
#define TENATMOST_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <exception>
class TenAtMost
{
    public:
        static TenAtMost* getInstance(std::string n);
        std::string getName() const;
        ~TenAtMost();
    protected:
        TenAtMost(){}
        TenAtMost(std::string n);
        
    private:
        std::string name;
        static int count;
};




#endif