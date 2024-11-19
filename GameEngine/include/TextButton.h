#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H

#include "Sprite.h"
#include <string>
#include "SDL2\SDL.h"
#include "TextFragment.h"
#include "Button.h"
#include "Position.h"
#include "Dimension.h"

class TextButton : public MovableSprite
{
    public:
        static TextButton* GetInstance(TextFragment *t, Button *b);
        void setFont(std::string strFont);
        void Draw() const;
        void Tick(System& system);
        void setText(std::string s);
        void SetPosition(Position p);

        const Position& GetPosition() {return button->GetPosition();}
        const Dimension& GetSize() { return button->GetSize(); }

        ~TextButton();
    protected:
        TextButton(TextFragment *t, Button *b);

    private:
    TextFragment *text;
    Button *button;
};



#endif