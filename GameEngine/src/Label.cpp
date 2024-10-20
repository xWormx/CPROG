#include "Label.h"

Label* Label::getInstance(int x, int y, int w, int h, std::string newText)
{
    return new Label(x, y, w, h, newText);
}

Label::Label(int x, int y, int w, int h, std::string txt) : Component(x,y,w,h), text(txt)
{
    SDL_Surface* surface = TTF_RenderText_Solid(engine.get_font(), text.c_str(), {0,0,0});
    texture = SDL_CreateTextureFromSurface(engine.get_ren(), surface);
    SDL_FreeSurface(surface);
}

void Label::draw () const
{
    SDL_RenderCopy(engine.get_ren(), texture, NULL, &getRect());
}

void Label::tick()
{

}

Label::~Label()
{
    SDL_DestroyTexture(texture);
}

std::string Label::getText() const
{
    return text;
}

void Label::setText(std::string newText)
{
    text = newText;
    SDL_DestroyTexture(texture);
    SDL_Surface* surface = TTF_RenderText_Solid(engine.get_font(), text.c_str(), {0,0,0});
    texture = SDL_CreateTextureFromSurface(engine.get_ren(), surface);
    SDL_FreeSurface(surface);
}   