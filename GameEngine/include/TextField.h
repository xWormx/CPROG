#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "System.h"
#include "Position.h"
#include "Dimension.h"

class TextField : public Sprite
{
    public:
        static TextField* GetInstance(int x, int y, SDL_Color c);

        void Tick(System& system);
        void Draw() const;

        void UpdateTextInput(System& system);
        void RenderNewTextInput();


    protected:
        TextField(int x, int y, SDL_Color c);
    
    private:
        Position pos;
        Dimension size;
        SDL_Color color;
        std::string currentText = " ";
        SDL_Texture* textTexture = nullptr;
};



#endif