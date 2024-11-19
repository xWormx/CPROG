#ifndef LABEL_H
#define LABEL_H

#include "Component.h"
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "GameEngine.h"

class Label : public Component
{
    public:
        static Label* GetInstance(int x, int y, int w, int h, std::string txt);
        void Draw() const;
        void Tick();
        std::string getText() const;
        void setText(std::string newText);
        ~Label();

    protected:
        Label(int x, int y, int w, int h, std::string txt);
    private:
        std::string text;
        SDL_Texture *texture = nullptr;
};


#endif