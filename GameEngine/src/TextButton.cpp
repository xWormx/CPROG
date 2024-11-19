#include "TextButton.h"
#include <stdexcept>

TextButton* TextButton::GetInstance(TextFragment *t, Button *b)
{
    return new TextButton(t, b);
}

TextButton::TextButton(TextFragment *t, Button *b) : MovableSprite(b->GetPosition().x, b->GetPosition().y, b->GetSize().w, b->GetSize().h), text(t), button(b)
{ 
}

void TextButton::Tick(System& system)
{
    if(InputComponent::GetKeyPressed('w'))
        setText("w");
    else
        setText("Not clicking!");

    button->Tick(system);
    text->Tick(system);
}

void TextButton::setText(std::string s)
{
    text->SetText(s);
}

void TextButton::draw() const
{
    SDL_RenderCopy(engine.Get_ren(), button->texture, &button->getSrcRect(), &button->getDestRect());

    SDL_RenderCopy(engine.Get_ren(), text->GetTexture(), &text->getSrcRect(), &text->getDestRect());
}

void TextButton::SetPosition(Position p)
{
    
    text->SetPosition(p);
    button->SetPosition(p);
    setDestRect(p.x, p.y, getDestRect().w, getDestRect().h);
}

TextButton::~TextButton()
{
}