#ifndef COUNTED_H
#define COUNTED_H

#include <string>

class Counted
{
    public:
        Counted(std::string d);
        std::string get() const;
        static int getCount();

    private:
        static int count;
        std::string data;
};

int Counted::count = 0;

Counted::Counted(std::string d) : data(d)
{
    count++;
}

std::string Counted::get() const { return data; }
int Counted::getCount() { return count; }

#endif