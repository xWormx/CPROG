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
        static Sprite* getInstance(int x, int y, int w, int h, std::string srcImage);
        void draw() const;
        void keyDown(const SDL_Event&);        
        const SDL_Rect& getRect() const;
        const SDL_Rect& getAreaToDraw() const;
        void setAreaRectToDraw(int x, int y, int h, int w);
        void move(int x, int y);
        virtual void tick() = 0;

        ~Sprite();
    protected:
        Sprite(int x, int y, int w, int h, std::string srcImage);
    private:
        SDL_Rect rect;
        SDL_Rect areaToDraw;
        SDL_Texture* texture;
        
};


#endif