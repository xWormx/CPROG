/*#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "System.h"
#include "TextButton.h"
#include "Position.h"

class UIElement : public TextButton
{
    public:
        static UIElement* GetInstance(int x, int y, int w, int h, std::string txt, std::string srcImage);
        void Tick(System& system);

        const Position& GetPosition() const { return pos; } 
        void SetPosition(Position p)
        {
            TextButton::SetPosition(p.x, p.y);
        }
    protected:
        UIElement(int x, int y, int w, int h, std::string txt, std::string srcImage);
    
    private:
        Position pos;
        int s;
};


#endif*/