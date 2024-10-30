#include "InputComponent.h"

SDL_Keycode InputComponent::getKeyCodeFromEvent(const SDL_Event& event) const
{
    return event.key.keysym.sym;
}

Uint8 InputComponent::getMouseButtonFromEvent(const SDL_Event& event) const
{
    return event.button.button;
}


void InputComponent::setKeyCodePressed(const Sint32 keyCode)
{
    int bitValue = 1;

    // Must OR togheter the new set bits otherwise the previous set bit will be overwritten
    if(keyCode > 0 && keyCode <= 32)        keyCode_1_32   |= (bitValue << (keyCode - 1));    
    else if(keyCode > 32 && keyCode <= 64)  keyCode_33_64  |= (bitValue << (keyCode - 33));        
    else if(keyCode > 64 && keyCode <= 96)  keyCode_65_96  |= (bitValue << (keyCode - 65));
    else if(keyCode > 96 && keyCode <= 128) keyCode_97_128 |= (bitValue << (keyCode - 97));    
        
}

void InputComponent::setKeyCodeReleased(const Sint32 keyCode)
{
    // The bit value must be 1 and not 0 because it is beeing negated!
    int bitValue = 1;

    // &= ~(bitstate) negates the bitpattern leading to the bit corresponding to the keyCode being set to 0.
    if(keyCode > 0 && keyCode <= 32)        keyCode_1_32   &= ~(bitValue << (keyCode - 1));    
    else if(keyCode > 32 && keyCode <= 64)  keyCode_33_64  &= ~(bitValue << (keyCode - 33));        
    else if(keyCode > 64 && keyCode <= 96)  keyCode_65_96  &= ~(bitValue << (keyCode - 65));
    else if(keyCode > 96 && keyCode <= 128) keyCode_97_128 &= ~(bitValue << (keyCode - 97));    
        
}

bool InputComponent::getKeyPressed(const int keyCode) const
{
    int bitValue = 1;

    // Checking to see if the keyCodes corresponding bit is set.
    if(keyCode > 0 && keyCode <= 32)        return keyCode_1_32   & (bitValue << (keyCode - 1));    
    else if(keyCode > 32 && keyCode <= 64)  return keyCode_33_64  & (bitValue << (keyCode - 33));        
    else if(keyCode > 64 && keyCode <= 96)  return keyCode_65_96  & (bitValue << (keyCode - 65));
    else if(keyCode > 96 && keyCode <= 128) return keyCode_97_128 & (bitValue << (keyCode - 97));    
    
    return false;
}

void InputComponent::setMousePressed(const Uint32 button)
{
    int bitValue = 1;
    switch(button)
    {
        case SDL_BUTTON_LEFT:
        {
            buttonBitPattern |= (bitValue << 8);
        } break; 
    }

}
void InputComponent::setMouseReleased(const Uint32 button)
{
    int bitValue = 1;
    switch(button)
    {
        case SDL_BUTTON_LEFT:
        {
            buttonBitPattern &= ~(bitValue << 8);
        } break; 
    }

}

bool InputComponent::getMousePressed(const Uint8 button) const
{
    int bitValue = 1;

    switch(button)
    {
        case SDL_BUTTON_LEFT:
        {
            return buttonBitPattern & (bitValue << 8);
        }
    }

    return false;
    
}


