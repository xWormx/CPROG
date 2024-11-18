#ifndef BUTTON_H
#define BUTTON_H


#include "System.h"
#include <string>
#include "MovableSprite.h"

class Button : public MovableSprite
{
    public:
        static Button* getInstance(int x, int y, int w, int h, std::string srcImage);
        void tick(System& system);

        const Position& GetPosition() { return pos; } 
        const Dimension& GetSize() { return size; } 

        void SetPosition(Position p);

    protected:
        Button(int x, int y, int w, int h, std::string srcImage);

    private:
        Position pos;
        Dimension size;
};

#endif