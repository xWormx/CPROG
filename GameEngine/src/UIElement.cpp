/*#include "UIElement.h"

UIElement* UIElement::GetInstance(int x, int y, int w, int h, std::string txt, std::string srcImage)
{
    return new UIElement(x, y, w, h, txt, srcImage);
}

UIElement::UIElement(int x, int y, int w, int h, std::string txt, std::string srcImage) : TextButton(x, y, w, h, txt, srcImage), pos{x,y}
{
}

void UIElement::Tick(System& system)
{
    if (InputComponent::GetKeyPressed('w'))
    {
        setText("KICK");
    }
    else
    {
        setText("BRO");
    }
}
*/