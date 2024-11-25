#include "Player.h"

Player* Player::GetInstance(int x, int y, int h, int w, std::string srcImage, int maxHP)
{
    return new Player(x, y, w, h, srcImage, maxHP);
}

Player::Player(int x, int y, int h, int w, std::string srcImage, int maxHP) : MovableSprite(x,y,w,h,srcImage), pos{x, y}, size{w,h}, maxHealth(maxHP), currentHealth(maxHP), damageTaken(0)
{
}

void Player::Tick(System& system)
{
    if(!healthInitialized)
    {
        for(int i = 0; i < maxHealth; i++)
        {
            int hpW = 20, hpH = 12;

            HPSlot* s = HPSlot::GetInstance(GetDestRect().x + (i*hpW), GetDestRect().y, hpW, hpH, "HPSlot.png");
            
            healthBar.push_back(s);
            system.AddSprite(s);
        }
        healthInitialized = true;
    }
    else
    {
        int i = 0;
        int rows = 1;
        int offset = 100;
        int startYPos = txtButtonRef->GetDestRect().y;
        for(HPSlot* slot : healthBar)
        {
            if((GetDestRect().x - offset) + (i * slot->GetSize().w) > ((GetDestRect().x + size.w) + offset))
            {
                rows++;
                i = 0;
            }
            slot->setPosition((GetDestRect().x - offset) + (i * slot->GetSize().w), startYPos - (rows * slot->GetSize().h));
            i++;

        }
    }

    isMoving = false;
    UpdateHealth(system);
    AnimateSprite({0,0}, {32, 80}, 3, 2);

    if (system.GetKeyPressed('d') || system.GetMousePressed(SDL_BUTTON_LEFT))
    {
        Move(moveSpeed, 0);
        isMoving = true;
    }
    if (system.GetKeyPressed('a'))
    {
        Move(-moveSpeed, 0);
        isMoving = true;
    }
    if (system.GetKeyPressed('w'))
    {
        Move(0, -moveSpeed);
        isMoving = true;
    }
    if (system.GetKeyPressed('s'))
    {
        Move(0, moveSpeed);
        isMoving = true;
    }

    // Restric movment to be inside window
    /* if (GetColliderBounds().x < 5)
        Move(5, 0);
    if(GetColliderBounds().x + GetColliderBounds().w > engine.GetWindowWidth() - 5)
        Move(-5, 0); 
    if((GetColliderBounds().y - 5) < 0)
        Move(0, 5);
    if(GetColliderBounds().y + GetColliderBounds().h > engine.GetWindowHeight() - 5)
        Move(0, -5); */


    if(txtButtonRef != NULL)
        txtButtonRef->SetPosition(pos);

    SetColliderBounds({GetDestRect().x, GetDestRect().y + (2 * size.h/3), size.w, size.h / 3});

    Position p = {GetDestRect().x - size.w/4, GetDestRect().y};
    if(txtButtonRef != nullptr)
        txtButtonRef->SetPosition({p.x, p.y - txtButtonRef->GetSize().h});


    if(system.GetKeyPressed('p'))
    {
       
        if(particleSpawnTick++ % 1 == 0)
        {
            int px = engine.GetRandomNumberInRange(-8, 8);
            int py = engine.GetRandomNumberInRange(-5, 5);

            int sx = engine.GetRandomNumberInRange(-10, -5);
            int sy = engine.GetRandomNumberInRange(-3, 3);
            Particle* p = Particle::GetInstance(GetDestRect().x + px, GetDestRect().y + py, 30 , 30, "Particle.png", 30);
            p->InstallCollider2D(true, {GetDestRect().x, GetDestRect().y, 30, 30}, true, false);
            p->SetMoveSpeed(sx, sy);
            p->SetTag("particle");
            p->SetLayerTag("foreGround");
            
            system.AddSprite(p);
        
        }
    }

    if(system.GetKeyPressedOnce('u'))
        system.LoadLevel(2);

    if(system.GetKeyPressedOnce('y'))
        system.LoadLevel(1);

}

void Player::OnCollision(Sprite* other, System& system)
{

    if(other->CompareTag("enemySmall"))
    {
        std::cout << "Player collided with enemySmall\n";
    }

    if(other->CompareTag("enemyParticle"))
    {
        TakeDamage(1);
        system.RemoveSprite(other);
    }
}

void Player::TakeDamage(int damage)
{
    damageTaken += damage;
}

void Player::UpdateHealth(System& system)
{
    for(int i = 0; i < damageTaken; i++)
    {
        if(healthBar.size() > 0)
        {
            HPSlot* hs = healthBar.back();
            healthBar.pop_back();
            system.RemoveSprite(hs);
            currentHealth -= damageTaken;    
        }
    }

    damageTaken = 0;
}