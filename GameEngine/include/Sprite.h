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

        void setSrcRect(int x, int y, int w, int h);
        void setDestRect(int x, int y, int w, int h);


        const SDL_Rect& getSrcRect() const;
        const SDL_Rect& getDestRect() const;
        const SDL_Texture* getTexture() const;

        virtual ~Sprite(){}
    protected:
        Sprite(int x, int y, int w, int h, std::string srcImage);
    private:
        SDL_Rect srcRect; // What part to draw
        SDL_Rect destRect; // Where to draw it
        SDL_Texture* texture;

        Sprite(const Sprite&) = delete;
        const Sprite& operator=(const Sprite&) = delete;      
};


#endif