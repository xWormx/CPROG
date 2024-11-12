#include "Player.h"

Player* Player::getInstance(int x, int y, int h, int w, std::string srcImage)
{
    return new Player(x, y, w, h, srcImage);
}

void Player::tick()
{
    isMoving = false;
    static int tick = 0;
    static int frame = 0;
    
    if (tick % 7 == 0)
    {
        frame++;
        if (frame > 3)
            frame = 0;
        int size = 124;
        setSpriteRegion(size * frame, 0, size, size);
    }
    
    tick++;

    if (keyPressed('d') || InputComponent::getMousePressed(SDL_BUTTON_LEFT))
    {
        pos.x += moveSpeed;
        isMoving = true;
    }
    if (keyPressed('a'))
    {
        pos.x -= moveSpeed;
        isMoving = true;
    }
    if (keyPressed('w'))
    {
        pos.y -= moveSpeed;
        isMoving = true;
    }
    if (keyPressed('s'))
    {
        pos.y += moveSpeed;
        isMoving = true;
    }

    // Restric movment to be inside window
    if ((pos.x + (width / 3)) < 0)
        pos.x = -(width / 3);
    if(pos.x + (width - width/3) > engine.GetWindowWidth())
        pos.x = engine.GetWindowWidth() - (width - (width/3)); 
    if((pos.y + 80) < 0)
        pos.y = -80;
    if(pos.y + height > engine.GetWindowHeight())
        pos.y = engine.GetWindowHeight() - height;


    if(txtButtonRef != NULL)
        txtButtonRef->SetPosition(pos);
    
    MovableSprite::setPosition(pos.x, pos.y);
    Position p = {pos.x + width/4, pos.y};
    if(txtButtonRef != nullptr)
        txtButtonRef->SetPosition(p);

    if(keyPressed('p'))
    {
        static unsigned int tick = 0;
        if(tick++ % 4 == 0)
        {
            int sx = engine.GetRandomNumberInRange(-5, 5);
            int sy = engine.GetRandomNumberInRange(-8, 8);
            Particle* p = Particle::getInstance(pos.x, pos.y, 60 , 60, "Particle.png", 30);
            p->SetMoveSpeed(sx, sy);
            p->SetAppRef(appRef);

            appRef->addSprite(p);
        
        }

    }

    if(spriteCollection != nullptr)
    {
        for(Sprite *s : *spriteCollection)
        {
            if(CheckCollision(s))
            {
            }
            
        }
    }
    
        

}

const bool Player::CheckCollision(Sprite* other) const
{
    Player *otherPlayer = dynamic_cast<Player*>(other);
    if(otherPlayer != nullptr && otherPlayer != this)
    {
        if(pos.x < otherPlayer->pos.x + otherPlayer->width && 
            pos.x + width > otherPlayer->pos.x)
        {   
            return true;
        }
    }
    
    return false;
}