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
        void move(int x, int y);
        ~Sprite();
    protected:
        Sprite(int x, int y, int w, int h, std::string srcImage);
    private:
        SDL_Rect rect;
        SDL_Texture* texture;
        
};


#endif