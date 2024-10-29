#ifndef SPRITE_H
#define SPRITE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_Image.h"
#include <string>
#include "Constants.h"
#include "GameEngine.h"
#include "InputComponent.h"

class Sprite : public InputComponent
{
    public:
        virtual void draw() const = 0;     
        virtual void tick() = 0;

        const SDL_Rect& getRect() const;
        const SDL_Rect& getAreaToDraw() const;
        const SDL_Texture* getTexture() const;
        void setAreaRectToDraw(int x, int y, int h, int w);
        void setPosition(int x, int y);
        
        ~Sprite();
    protected:
        Sprite(int x, int y, int w, int h, std::string srcImage);
    private:
        SDL_Rect rect;
        SDL_Rect areaToDraw;
        SDL_Texture* texture;
        
};


#endif