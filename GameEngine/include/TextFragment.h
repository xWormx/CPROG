#ifndef TEXTFRAGMENT_H
#define TEXTFRAGMNET_H

#include "System.h"
#include "Sprite.h"
#include <stdexcept>
#include "SDL2\SDL.h"

class TextFragment : public Sprite
{
    public:
        static TextFragment* getInstance(int x, int y, int w, int h, std::string text, SDL_Color c);

        void draw() const;
        void tick(System& system);
    
    protected:
        TextFragment(int x, int y, int w, int h, std::string text, SDL_Color c);

    private:
        SDL_Texture* textTexture;
};


#endif