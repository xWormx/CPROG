#include "HPSlot.h"

HPSlot* HPSlot::GetInstance(int x, int y, int w, int h, std::string srcImage)
{
    return new HPSlot(x,y,w,h,srcImage);
}

HPSlot::HPSlot(int x, int y, int w, int h, std::string srcImage) : MovableSprite(x,y,w,h,srcImage), pos{x,y}, size{w,h}
{

}

void HPSlot::Tick(System& system)
{
    
}