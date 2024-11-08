#ifndef ELEFANT_H
#define ELEFANT_H

#include "Animal.h"

namespace zoo
{
    class Elefant : public Animal
    {
        public:
            Elefant(std::string n, int a, int t) : Animal(n, a), trunk(t) {}  
            int getTrunk() const {return trunk;}
        private:
            int trunk;
    };
}

#endif