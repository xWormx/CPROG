#ifndef MANAGED_H
#define MANAGED_H

#include <string>
#include <vector>

// Behöver en destructor för att städa undan 

class Managed
{
    public:
        Managed(std::string d) : data(d) {objects.push_back(this);}
        std::string get_data() const { return data; }
        
    private:
        std::string data;
        static std::vector<Managed*> objects;
};

std::vector<Managed*> Managed::objects; // Definition

#endif