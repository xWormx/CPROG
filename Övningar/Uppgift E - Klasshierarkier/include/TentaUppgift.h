#ifndef TENTAUPPGIFT_H
#define TENTAUPPGIFT_H

#include <string>
#include <iostream>

class Person
{
    public:
        Person(std::string n) : name(n){}
        std::string getName() { return name; }
    
    private:
        std::string name;
        int refCount;
        friend class Pointer;

};

class Pointer
{
    public:
        Pointer(Person* p) : pers(p){
            if(pers != nullptr)
                pers->refCount++;
        }

        // Copy constructor
        Pointer(const Pointer& other) : pers(other.pers){
            if(pers != nullptr)
                pers->refCount++;
        }

        ~Pointer(){
            if(pers && --pers->refCount == 0){
                delete pers;
            }
        }

    /*
        ptr1 = ptr3;
        ptr2 = nullptr;
        ptr1 = ptr2;
    */
        const Pointer& operator=(const Pointer& other){
            if(pers != other.pers){
                if(pers && (--pers->refCount == 0)){
                    delete pers;
                }

                pers = other.pers;

                if(pers){
                    pers->refCount++;
                }
            }
            return *this;
        }       

        Person* operator->(){
            if(pers != nullptr)
                return pers;
        }

    private:
        Person* pers;
};


#endif