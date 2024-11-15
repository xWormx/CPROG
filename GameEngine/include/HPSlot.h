#ifndef HPSLOT_H
#define HPSLOT_H

#include <string>
#include "Position.h"
#include "Dimension.h"
#include "MovableSprite.h"
#include "System.h"

class HPSlot : public MovableSprite
{
    public: 
        static HPSlot* getInstance(int x, int y, int w, int h, std::string srcImage);
        void tick(System& system);

        const Position& GetPosition() const {return pos;}
        const Dimension& GetSize() const {return size;}
    
    protected:
        HPSlot(int x, int y, int w, int h, std::string srcImage);
    
    private:
        Position pos;
        Dimension size;
};



#endif