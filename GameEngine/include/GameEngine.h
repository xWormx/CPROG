#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <String>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_Image.h"

class GameEngine
{

  public:
    GameEngine();
    ~GameEngine();
    SDL_Renderer* get_ren() const;
    TTF_Font* get_font() const;
  
  private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* backgroundSurface;
    TTF_Font* font;
};


extern GameEngine engine;



#endif