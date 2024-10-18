#ifndef DYNAMICMEM_H
#define DYNAMICMEM_H

class DynamicMem
{
    public:
        DynamicMem(int size);
        ~DynamicMem();
    protected:
    
    private:
        char* data;
};


#endif