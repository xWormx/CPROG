#include "Player.h"

Player* Player::getInstance(int x, int y, int h, int w, std::string srcImage, int maxHP)
{
    return new Player(x, y, w, h, srcImage, maxHP);
}

Player::Player(int x, int y, int h, int w, std::string srcImage, int maxHP) : MovableSprite(x,y,w,h,srcImage), pos{x, y}, size{w,h}, maxHealth(maxHP)
{
}

void Player::tick(System& system)
{
    if(!healthInitialized)
    {
        for(int i = 0; i < maxHealth; i++)
        {
            int hpW = 35, hpH = 20;

            HPSlot* s = HPSlot::getInstance(pos.x + (i*hpW), pos.y, hpW, hpH, "HPSlot.png");
            
            healthBar.push_back(s);
            system.addSprite(s);
        }
        healthInitialized = true;
    }
    else
    {
        int i = 0;
        int rows = 1;
        for(HPSlot* slot : healthBar)
        {
            if(pos.x + (i * slot->GetSize().w) > pos.x + size.w)
            {
                rows++;
                i = 0;
            }
            slot->setPosition(pos.x + (i * slot->GetSize().w), pos.y - (rows * slot->GetSize().h));
            i++;

        }
    }


    isMoving = false;
    
    //static int frame = 0;
    //
    //if (frameTick++ % 12 == 0)
    //{
    //    frame++;
    //    if (frame > 3)
    //        frame = 0;
    //    int size = 124;
    //    setSpriteRegion(size * frame, 0, size, size);
    //}
    
    AnimateSprite({0,0}, {32, 80}, 3, 2);

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

    SetColliderBounds({pos.x, pos.y + (2 * size.h/3), size.w, size.h / 3});

    Position p = {pos.x - size.w/4, pos.y};
    if(txtButtonRef != nullptr)
        txtButtonRef->SetPosition({p.x, p.y - txtButtonRef->GetSize().h});

    if(keyPressed('p'))
    {
       
        if(particleSpawnTick++ % 1 == 0)
        {
            int px = engine.GetRandomNumberInRange(-8, 8);
            int py = engine.GetRandomNumberInRange(-5, 5);

            int sx = engine.GetRandomNumberInRange(-10, -5);
            int sy = engine.GetRandomNumberInRange(-3, 3);
            Particle* p = Particle::getInstance(pos.x + px, pos.y + py, 30 , 30, "Particle.png", 30);
            p->SetCollider(true, {pos.x, pos.y, 30, 30});
            p->SetMoveSpeed(sx, sy);
            system.addCollider(p);


            system.addSprite(p);
        
        }
    }
}

void Player::OnCollision(Sprite* other)
{
    Enemy* enemy = dynamic_cast<Enemy*>(other);
    if(enemy != nullptr)
    {
        std::cout << "OnCollision: Player & Enemy from Player\n";
    }
}

const bool Player::CheckCollision(Sprite* other) const
{
    Player *otherPlayer = dynamic_cast<Player*>(other);
    if(otherPlayer != nullptr && otherPlayer != this)
    {
        static int collisions = 0;
        if(pos.x < otherPlayer->pos.x + otherPlayer->size.w && 
            pos.x + size.w > otherPlayer->pos.x)
        {   
            std::cout << "COLLISION: " << collisions++ << "\n";

            return true;
        }
    }

    Particle *particle = dynamic_cast<Particle*>(other);
    if(particle != nullptr)
    {
        if(pos.x < particle->GetPosition().x + particle->GetSize().w && 
            pos.x + size.w > particle->GetPosition().x)
        {   
            std::cout << "Particle hit Person!\n";
            return true;
        }
    }
    
    return false;
}