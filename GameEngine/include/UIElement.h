#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "TextButton.h"
#include "Position.h"

class UIElement : public TextButton
{
    public:
        static UIElement* getInstance(int x, int y, int w, int h, std::string txt, std::string srcImage);
        void tick();

        const Position& GetPosition() const { return pos; } 
        void SetPosition(Position p)
        {
            TextButton::SetPosition(p.x, p.y);
        }
    protected:
        UIElement(int x, int y, int w, int h, std::string txt, std::string srcImage) : TextButton(x, y, w, h, txt, srcImage), pos{x,y} {}
    
    private:
        Position pos;
        int s;
};


#endif