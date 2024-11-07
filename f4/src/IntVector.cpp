// Labb2, IntVector.cpp – definitioner av icke-triviala medlemsfunktioner

#include "IntVector.h"

IntVector::IntVector(const std::initializer_list<int>& initList) : iSize(initList.size())
{
    data = new int[iSize];
    int i = 0;
    for(int value : initList)
        data[i++] = value;
}

IntVector::IntVector(const IntVector& other) : iSize(other.size())
{    
    data = new int[other.size()];
    for(int i = 0; i < other.size(); i++)
    {
        data[i] = other.data[i];
    }
}

const IntVector& IntVector::operator=(const IntVector& other)
{
    if(this != &other)
    {
        delete [] data;
        iSize = other.size();
        data = new int[iSize];
        for(int i = 0; i < iSize; i++)
        {
            data[i] = other.data[i];
        }
    }
    
    return *this;
}

int& IntVector::operator[](int index) const
{
    return data[index];
}

std::ostream& operator<<(std::ostream& os, const IntVector& iVec)
{
    for(int i = 0; i < iVec.size(); i++)
    {
        os << iVec.data[i] << " ";
    }

    return os;
}

void IntVector::push_back(int value)
{
    int sz = size();
    int *temp = new int[size()];
    memcpy(temp, data, size() * sizeof(int));
    
    delete [] data;
    iSize = size() + 1;
    data = new int[iSize];
    memcpy(data, temp, iSize * sizeof(int));
    
    data[iSize - 1] = value;
}

const int& IntVector::size() const
{
    return iSize;
}
