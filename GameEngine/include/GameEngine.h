#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <String>
#include <random>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_Image.h"

class GameEngine
{

  public:
    GameEngine();
    ~GameEngine();
    SDL_Window* get_window() const;
    SDL_Renderer* get_ren() const;
    TTF_Font* get_font() const;
    int GetWindowWidth() const;
    int GetWindowHeight() const;
    int GetRandomNumberInRange(int min, int max);

  
  private:
    SDL_Window* window              = nullptr;
    SDL_Renderer* renderer          = nullptr;
    SDL_Surface* backgroundSurface  = nullptr;
    TTF_Font* font                  = nullptr;
    std::random_device rd;
    std::mt19937 gen;
    void SetupRandomGenerator();

};


extern GameEngine engine;



#endif