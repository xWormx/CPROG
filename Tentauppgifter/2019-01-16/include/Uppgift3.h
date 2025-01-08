#ifndef UPPGIFT3_H
#define UPPGIFT3_H


unsigned int swap(unsigned int bits)
{
    /*
            bits:
                10101010 20202020 30303030 40404040

            vill returnera:
                30303030 40404040 10101010 20202020 

    */

   unsigned int left = (bits << 16);
   unsigned int right = (bits >> 16);

   return (left | right); 
}

#endif