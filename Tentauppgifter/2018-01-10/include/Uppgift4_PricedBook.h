#ifndef PRICEDBOOK_H
#define PRICEDBOOK_H

#include "Uppgift4_Book.h"

class PricedBook : public books::Book
{
    public:
        PricedBook(std::string t, int i , int p);

    private:
        int price;
};



#endif
