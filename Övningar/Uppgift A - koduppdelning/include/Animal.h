#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <iostream>


namespace zoo
{
    class Animal
    {
        public:
            Animal(std::string n, int a) : name(n), age(a) {}
            std::string getName() const {return name;}
            int getAge() const {return age;}

        private:
            std::string name;
            int age;
    };
}


#endif