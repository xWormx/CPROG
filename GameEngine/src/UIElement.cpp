#include "UIElement.h"

UIElement* UIElement::getInstance(int x, int y, int w, int h, std::string txt, std::string srcImage)
{
    return new UIElement(x, y, w, h, txt, srcImage);
}

void UIElement::tick()
{
    if (InputComponent::getKeyPressed('w'))
    {
        setText("KICK");
    }
    else
    {
        setText("JANIS");
    }
}