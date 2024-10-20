#include "InputComponent.h"

SDL_Keycode InputComponent::getKeyCodeFromEvent(const SDL_Event& event)
{
    return event.key.keysym.sym;
}