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

    if ((pos.x + (width / 3)) < 0)
        pos.x = -(width / 3);

    if(txtButtonRef != NULL)
        txtButtonRef->SetPosition(pos);
    
    MovableSprite::setPosition(pos.x, pos.y);

    if(keyPressed('p'))
    {
        static unsigned int tick = 0;
        static int posAdd = 0;
        if(tick++ % 6 == 0)
        {
            particle = Particle::getInstance(pos.x, pos.y, 60 , 60, "Particle.png", 5);
            appRef->addSprite(particle);

        }

    }

}