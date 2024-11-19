#ifndef TEXTFRAGMENT_H
#define TEXTFRAGMENT_H

#include "System.h"
#include <stdexcept>
#include "SDL2\SDL.h"
#include "Position.h"
#include "MovableSprite.h"

class TextFragment : public MovableSprite
{
    public:
        static TextFragment* GetInstance(int x, int y, int w, int h, std::string text, SDL_Color c);

        void draw() const;
        void Tick(System& system);
        void SetText(std::string s);
        void SetPosition(Position p);

        SDL_Texture* GetTexture() {return textTexture;}


    protected:
        TextFragment(int x, int y, int w, int h, std::string text, SDL_Color c);

    private:
        Position pos;
        std::string strText;
        SDL_Color color;
        SDL_Texture* textTexture;

};


#endif