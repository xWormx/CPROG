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

            HPSlot* s = HPSlot::GetInstance(pos.x + (i*hpW), pos.y, hpW, hpH, "HPSlot.png");
            
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
        int startYPos = txtButtonRef->GetPosition().y;
        for(HPSlot* slot : healthBar)
        {
            if((pos.x - offset) + (i * slot->GetSize().w) > ((pos.x + size.w) + offset))
            {
                rows++;
                i = 0;
            }
            slot->setPosition((pos.x - offset) + (i * slot->GetSize().w), startYPos - (rows * slot->GetSize().h));
            i++;

        }
    }

    isMoving = false;
    UpdateHealth(system);
    AnimateSprite({0,0}, {32, 80}, 3, 2);

    if (system.GetKeyPressed('d') || system.GetMousePressed(SDL_BUTTON_LEFT))
    {
        pos.x += moveSpeed;
        isMoving = true;
    }
    if (system.GetKeyPressed('a'))
    {
        pos.x -= moveSpeed;
        isMoving = true;
    }
    if (system.GetKeyPressed('w'))
    {
        pos.y -= moveSpeed;
        isMoving = true;
    }
    if (system.GetKeyPressed('s'))
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
    if(system.GetKeyPressedOnce('a'))
    {
        std::cout << "ONCE\n";
    }
    if(system.GetKeyPressed('p'))
    {
       
        if(particleSpawnTick++ % 1 == 0)
        {
            int px = engine.GetRandomNumberInRange(-8, 8);
            int py = engine.GetRandomNumberInRange(-5, 5);

            int sx = engine.GetRandomNumberInRange(-10, -5);
            int sy = engine.GetRandomNumberInRange(-3, 3);
            Particle* p = Particle::GetInstance(pos.x + px, pos.y + py, 30 , 30, "Particle.png", 30);
            p->SetCollider(true, {pos.x, pos.y, 30, 30});
            p->SetMoveSpeed(sx, sy);
            p->SetTag("particle");
            system.AddCollider(p);
            system.AddSprite(p);
        
        }
    }
}

// Ge varje psrite en std::string tag, och så kan man kolla mot taggen i OnCollision, som i unity typ.
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