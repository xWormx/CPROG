#ifndef BUTTON_H
#define BUTTON_H

#include "Label.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class Button : public Component
{

public:
    static Button* getInstance(int x, int y, int w, int h, std::string txt);
    ~Button();
    void draw() const;
    void keyDown(const SDL_Event&);
    void tick();
    void setPosition(SDL_Point newPosition);
    void move(SDL_Point step);
protected:
    Button(int x, int y, int w, int h, std::string txt);

private:
    std::string text;
    SDL_Texture* texture;
    SDL_Texture *iconUp, *iconDown, *currentIcon;
};


#endif