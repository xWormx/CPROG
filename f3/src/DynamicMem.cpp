#include "DynamicMem.h"

DynamicMem::DynamicMem(int size)
{
    data = new char[size];
}

DynamicMem::~DynamicMem()
{
    delete data;
}