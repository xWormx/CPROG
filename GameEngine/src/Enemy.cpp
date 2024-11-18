#include "Enemy.h"

Enemy* Enemy::getInstance(int x, int y, int h, int w, std::string srcImage, int maxHP)
{
    return new Enemy(x, y, w, h, srcImage, maxHP);
}
Enemy::Enemy(int x, int y, int h, int w, std::string srcImage, int maxHP) : MovableSprite(x,y,w,h,srcImage), pos{x, y}, size{w,h}, maxHealth(maxHP)
{
}

void Enemy::tick(System& system)
{
    isMoving = false;
    
    static int frame = 0;
    
    if (frameTick++ % 12 == 0)
    {
        frame++;
        if (frame > 3)
            frame = 0;
        int size = 124;
        setSpriteRegion(size * frame, 0, size, size);
    }
    

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
    if ((pos.x + (size.w / 3)) < 0)
        pos.x = -(size.w / 3);
    if(pos.x + (size.w - size.w/3) > engine.GetWindowWidth())
        pos.x = engine.GetWindowWidth() - (size.w - (size.w/3)); 
    if((pos.y + 80) < 0)
        pos.y = -80;
    if(pos.y + size.h > engine.GetWindowHeight())
        pos.y = engine.GetWindowHeight() - size.h;


    if(txtButtonRef != NULL)
        txtButtonRef->SetPosition(pos);
    
    MovableSprite::setPosition(pos.x, pos.y);
    SetColliderBounds({pos.x, pos.y, size.w, size.h});
    Position p = {pos.x + size.w/4, pos.y};
    if(txtButtonRef != nullptr)
        txtButtonRef->SetPosition(p);

    if(keyPressed('p'))
    {
       
        if(particleSpawnTick++ % 5 == 0)
        {
            int px = engine.GetRandomNumberInRange(-12, 12);
            int py = engine.GetRandomNumberInRange(-12, 12);

            int sx = engine.GetRandomNumberInRange(-5, 5);
            int sy = engine.GetRandomNumberInRange(-8, 8);
            Particle* p = Particle::getInstance(pos.x + px, pos.y + py, 30 , 30, "Particle.png", 30);
            p->SetMoveSpeed(sx, sy);

            system.addSprite(p);
        
        }

    }

}

void Enemy::OnCollision(Sprite* other)
{
    Player* p = dynamic_cast<Player*>(other);
    if(p != nullptr)
    {
        std::cout << "Enemy collided with Player, from enemy!\n";
    }
}

const bool Enemy::CheckCollision(Sprite* other) const
{
    Enemy *otherEnemy = dynamic_cast<Enemy*>(other);
    if(otherEnemy != nullptr && otherEnemy != this)
    {
        if(pos.x < otherEnemy->pos.x + otherEnemy->width && 
            pos.x + width > otherEnemy->pos.x)
        {   
            //std::cout << "COLLISION: " << collisions++ << "\n";

            return true;
        }
    }

    Particle *particle = dynamic_cast<Particle*>(other);
    if(particle != nullptr)
    {
        if(pos.x < particle->GetPosition().x + particle->GetSize().w && 
            pos.x + width > particle->GetPosition().x)
        {   
            //std::cout << "Particle hit Person!\n";
            return true;
        }
    }
    
    return false;
}