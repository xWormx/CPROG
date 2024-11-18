#include "TextButton.h"
#include <stdexcept>

TextButton* TextButton::getInstance(TextFragment *t, Button *b)
{
    return new TextButton(t, b);
}

TextButton::TextButton(TextFragment *t, Button *b) : MovableSprite(b->GetPosition().x, b->GetPosition().y, b->GetSize().w, b->GetSize().h), text(t), button(b)
{   
}

void TextButton::tick(System& system)
{
    if(InputComponent::getKeyPressed('w'))
        setText("w");
    else
        setText("Not clicking!");
}

void TextButton::setText(std::string s)
{
    text->SetText(s);
}

void TextButton::draw() const
{
    SDL_RenderCopy(engine.get_ren(), texture, &getSrcRect(), &getDestRect());

    SDL_RenderCopy(engine.get_ren(), text->GetTexture(), &text->getSrcRect(), &text->getDestRect());
}

void TextButton::SetPosition(Position p)
{
    text->SetPosition(p);
    button->SetPosition(p);
}

TextButton::~TextButton()
{
}