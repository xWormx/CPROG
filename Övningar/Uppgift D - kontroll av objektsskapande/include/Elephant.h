#ifnedf ELEPHANT_H
#define ELEPHANT_H

#include <string>

class Elephant : public Animal
{
    public:
        Elephant(std::string n, int w, int t1);
        int getTrunkLength() const;
    
    private:
        int trunkLength;
};


#endif