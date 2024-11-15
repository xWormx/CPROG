#ifndef ELEPHANT_H
#define ELEPHANT_H

#include "Animal.h"
#include <string>

class Elephant : public Animal
{
    public:
        static Elephant* getInstance(std::string n, int w, int t);
        int getTrunkLength() const;
        ~Elephant();
    protected:
        Elephant(std::string n, int w, int t1);
        
    private:
        int trunkLength;
};


#endif