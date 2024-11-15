#ifndef TENATMOST_H
#define TENATMOST_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <exception>

class Animal
{
    public:
        virtual ~Animal();
        std::string getName() const;
        int getWeight() const;

    protected:
        Animal(std::string n, int w);
    private:
        std::string name;
        int weight;
};




#endif