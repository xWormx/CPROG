#ifndef KLOCKA_H
#define KLOCKA_H

#include <stdexcept>
#include <iostream>
#include <string>

class Klocka
{
    public:
        explicit Klocka(int h = 0, int m = 0) : mem(h*60+m){
            if(mem > 60 * 24)
                throw std::out_of_range("Ogiltigt klockslag!");
        }

        // operator+ måste ha const efter sig.
        const Klocka operator+(int min) const{
            Klocka temp;
            temp.mem = mem + min;
            
            if(temp.mem > 24*60)
                throw std::out_of_range("Ogiltigt klockslag!");
            return temp;
        }

        Klocka operator++()
        {
            Klocka temp;
            mem++; 
            if(mem > 24*60)
                throw std::out_of_range("Ogiltigt klockslag!");
            return temp;
        }

        Klocka operator++(int)
        {
            mem++;
            if(mem > 24*60)
                throw std::out_of_range("Ogiltigt klockslag!");
            return *this;
        }

        const Klocka& operator+=(int m){
            mem += m;
            if(mem > 24*60)
                throw std::out_of_range("Ogiltigt klockslag!");
            return *this;
        }

    private:
        int mem; // minuter efter midnatt
        friend std::ostream& operator<<(std::ostream&, const Klocka&);
};


const Klocka operator+(int lhs, const Klocka& rhs){
    return rhs + lhs;
}

std::ostream& operator<<(std::ostream& os, const Klocka& kl){
    return os << kl.mem/60  << ":" << kl.mem%60; 
}

/*

    Klocka start(14, 0);


*/

#endif



std::ostream& operator<<(std::ostream& os, const SomeClass& sc){
    return os << sc.data << ":" << sc.otherData;
}