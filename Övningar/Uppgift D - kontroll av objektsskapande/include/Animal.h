#ifndef TENATMOST_H
#define TENATMOST_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <exception>

class Animal
{
    public:
        Animal(std::string n, int w);
        virtual ~Animal();
        std::string getName() constM
        int getWeight() const;
    
    private:
        std::string name;
        in weight;
};




#endif