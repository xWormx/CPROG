#ifndef TEXT_H
#define TEXT_H

#include "Sprite.h"
#include <string>
#include "SDL2\SDL.h"

class TextButton : public Sprite
{
    public:
        static TextButton* getInstance(int x, int y, int w, int h, std::string s, std::string srcImage);
        void setFont(std::string strFont);
        void draw() const;
        void tick();
        void setText(std::string s);
        void SetPosition(int x, int y);

        ~TextButton();
    protected:
        TextButton(int x, int y, int w, int h, std::string s, std::string srcimage);

    private:
    int x, y, width, height;
    std::string strText;
    SDL_Texture* imgTexture = nullptr, *textTexture = nullptr;
};



#endif