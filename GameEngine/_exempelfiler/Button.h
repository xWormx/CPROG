#ifndef BUTTON_H
#define BUTTON_H

#include "Label.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class Button : public Component
{

public:
    static Button* GetInstance(int x, int y, int w, int h, std::string txt);
    ~Button();
    void Draw() const;
    void keyDown(const SDL_Event&);
    void Tick();
    void setPosition(SDL_Point newPosition);
    void move(SDL_Point step);
protected:
    Button(int x, int y, int w, int h, std::string txt);

private:
    std::string text;
    SDL_Texture* texture = nullptr;
    SDL_Texture *iconUp = nullptr, *iconDown = nullptr, *currentIcon = nullptr;
};


#endif