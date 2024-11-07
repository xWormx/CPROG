#ifndef MYTEMPLATE_H
#define MYTEMPLATE_H

template<typename T>
class Test
{
    public:
        Test(T _a, T _b)
        {
            a = _a;
            b = _b;
        }
        
        T bigger();
    private:
        T a, b;
};

template<class T>
T Test<T>::bigger()
{
    return a > b ? a : b;
}

#endif