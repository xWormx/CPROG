#include "InputComponent.h"

SDL_Keycode InputComponent::getKeyCodeFromEvent(const SDL_Event& event)
{
    return event.key.keysym.sym;
}

void InputComponent::setKeyCodePressed(const Sint32 keyCode)
{
    keyCodePressed = keyCode;
}

Sint32 InputComponent::getKeyCodePressed()
{
    return keyCodePressed;
}