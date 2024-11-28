#include "Enemy.h"

Enemy* Enemy::GetInstance(int x, int y, int h, int w, std::string srcImage, int maxHP)
{
    return new Enemy(x, y, w, h, srcImage, maxHP);
}
Enemy::Enemy(int x, int y, int h, int w, std::string srcImage, int maxHP) : MovableSprite(x,y,w,h,srcImage), pos{x, y}, size{w,h}, maxHealth(maxHP)
{
}

void Enemy::Tick(System& system)
{
    isMoving = false;
    
    static int frame = 0;
    
    int maxFramesShooting = 4;
    static int shootFrame = 0;
    static bool shooting = false;
    if(system.GetKeyPressed('k') && shooting == false)
    {
        shooting = true;
        // Behövs bara om partiklarna ska spawna av sig självt?
        if(particleSpawnTick++ % 5 == 0)
        {
            
        }
        int px = engine.GetRandomNumberInRange(-12, 12);
        int py = engine.GetRandomNumberInRange(-12, 12);
        int sx = engine.GetRandomNumberInRange(-8, -7);
        int sy = engine.GetRandomNumberInRange(-1, 1);

        Particle* p = Particle::GetInstance((GetDestRect().x - 20) + px, (GetDestRect().y + (GetDestRect().h/2) + 10) + py, 30, 10, "BulletTest.png", 30);
        p->InstallCollider2D(true, {GetDestRect().x, GetDestRect().y, 30, 30}, true, false);
        p->SetMoveSpeed(sx, sy);
        p->SetTag("enemyParticle");
        system.AddSprite(p);
    }

    if(shooting)
    {
        shootFrame = AnimateSprite({5,0}, {100, 100}, 4, 2);
        if(shootFrame == maxFramesShooting)
        {
            shootFrame = 0;
            shooting = false;
        }    
    }
    else
    {
        AnimateSprite({9,0}, {100, 100}, 5, 4);
    }
    

    /* if (system.GetKeyPressed('d') || system.GetMousePressed(SDL_BUTTON_LEFT))
    {
        Move(-moveSpeed, 0);
        isMoving = true;
    }
    if (system.GetKeyPressed('a'))
    {
        Move(moveSpeed, 0);
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
    } */

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
    
    SetColliderBounds({GetDestRect().x, GetDestRect().y + (2 * size.h/3), size.w, size.h / 3});

    Position p = {GetDestRect().x + size.w/4, pos.y};
    if(txtButtonRef != nullptr)
        txtButtonRef->SetPosition(p);

    if(system.GetKeyPressedOnce('o'))
    {

    }

}

void Enemy::OnCollision(Sprite* other, System& system)
{
}
