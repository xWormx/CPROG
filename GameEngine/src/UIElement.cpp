/*#include "UIElement.h"

UIElement* UIElement::getInstance(int x, int y, int w, int h, std::string txt, std::string srcImage)
{
    return new UIElement(x, y, w, h, txt, srcImage);
}

UIElement::UIElement(int x, int y, int w, int h, std::string txt, std::string srcImage) : TextButton(x, y, w, h, txt, srcImage), pos{x,y}
{
}

void UIElement::tick(System& system)
{
    if (InputComponent::getKeyPressed('w'))
    {
        setText("KICK");
    }
    else
    {
        setText("BRO");
    }
}
*/