#ifndef BUTTON_H
#define BUTTON_H


#include "System.h"
#include <string>
#include "MovableSprite.h"

class Button : public MovableSprite
{
    public:
        static Button* GetInstance(int x, int y, int w, int h, std::string srcImage);
        void Tick(System& system);

        const Position& GetPosition() { return pos; } 
        const Dimension& GetSize() { return size; } 
        virtual void OnMouseHover(System& system){}
        virtual void OnMousePress(System& system){}
        virtual void OnMouseRelease(System& system){}
        void SetPosition(Position p);

    protected:
        Button(int x, int y, int w, int h, std::string srcImage);

    private:
        Position pos;
        Dimension size;
};

#endif