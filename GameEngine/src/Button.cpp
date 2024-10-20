#include "Button.h"
#include "Constants.h"


Button::Button(int x, int y, int w, int h, std::string txt) : Component(x,y,w,h)
{
    SDL_Surface* surf = TTF_RenderText_Solid(engine.get_font(), txt.c_str(), {0,0,0});
    texture = SDL_CreateTextureFromSurface(engine.get_ren(), surf);
    SDL_FreeSurface(surf);
    
    std::string srcIconDown = constants::gResPath + "images/iconDown.png";
    std::string srcIconUp = constants::gResPath + "images/iconUp.png";

    iconUp = IMG_LoadTexture(engine.get_ren(), srcIconUp.c_str());
    if(iconUp == NULL)
        std::cout << "iconUp failed to load" << std::endl;
    currentIcon = iconUp;

    iconDown = IMG_LoadTexture(engine.get_ren(), srcIconDown.c_str());    
    if(iconDown == NULL)
        std::cout << "iconDown failed to load" << std::endl;
}

Button::~Button()
{

}

Button* Button::getInstance(int x, int y, int w, int h, std::string txt)
{
    return new Button(x, y, w, h, txt);
}

void Button::draw() const
{
    SDL_RenderCopy(engine.get_ren(), currentIcon, NULL, &getRect());
    SDL_RenderCopy(engine.get_ren(), texture, NULL, &getRect());
}

void Button::keyDown(const SDL_Event& event)
{
    currentIcon == iconUp ? (currentIcon = iconDown) : (currentIcon = iconUp);
    //if(event.key.keysym.sym == SDL_KeyCode::SDLK_c)

    //std::string key = std::to_string(event.key.keysym.sym);
    
    // OBS TILLFÄÄLIGT, FÅNGA TEXTINPUT I EVENTLOOPEN ISTÄLLET I GAMEENGINE.
    char key = event.key.keysym.sym;
    std::cout << "button '"<< key << "' was pressed" << std::endl;
}

void Button::tick()
{

}

void Button::setPosition(SDL_Point newPosition)
{
    Component::getRect()->x = newPosition.x;
    Component::getRect()->y = newPosition.y;
}

void Button::move(SDL_Point step)
{
    Component::getRect()->x += step.x;
    Component::getRect()->y += step.y;
}