// Labb2, IntVector.h – klassdefinition

#include <initializer_list>
#include <iostream>
#include <cstring>

class IntVector
{
    public: 
        IntVector() : data(nullptr), iSize(0) {}
        IntVector(const std::initializer_list<int>& initList);
        IntVector(const IntVector&);
        const IntVector& operator=(const IntVector&);
        
        int& operator[](int index) const;
        friend std::ostream& operator<<(std::ostream&, const IntVector&);
        
        void push_back(int value);
        
        const int& size() const;
    
    private:
        int *data;
        int iSize;

};

