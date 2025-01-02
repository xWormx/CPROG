#ifndef BITHACKS_H
#define BITHACKS_H

namespace _BITHACKS
{
    
class BitHack
{

};

unsigned int get(unsigned long int uli, int nr)
{
    unsigned int result = 0;
    unsigned int mask = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4);
    result = (uli >> (nr * 4)) & mask;  
    /*      8421
            1111
    */
    return result;
}

void set(unsigned long int& uli, int nr, unsigned int value)
{
    /*
        value = 1100

        1001 1000 1001
    */

    // 15 = 1111 som bitar
    uli &= ~(15 << (nr * 4)); // nollställ den sektionen som värdet ska in i.

    uli |= (value << (nr * 4)); // sätt in värdet i samma sektion.
}
};


#endif