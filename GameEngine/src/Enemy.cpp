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
    
    if (frameTick++ % 12 == 0)
    {
        frame++;
        if (frame > 3)
            frame = 0;
        int size = 124;
        setSpriteRegion(size * frame, 0, size, size);
    }
    

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
    SetColliderBounds({pos.x, pos.y, size.w, size.h});
    Position p = {pos.x + size.w/4, pos.y};
    if(txtButtonRef != nullptr)
        txtButtonRef->SetPosition(p);

    if(system.GetKeyPressedOnce('o'))
    {
        // Behövs bara om partiklarna ska spawna av sig självt?
        if(particleSpawnTick++ % 5 == 0)
        {
            
        }
        int px = engine.GetRandomNumberInRange(-12, 12);
        int py = engine.GetRandomNumberInRange(-12, 12);
        int sx = engine.GetRandomNumberInRange(-8, -7);
        int sy = engine.GetRandomNumberInRange(-1, 1);

        Particle* p = Particle::GetInstance(pos.x + px, pos.y + py, 30 , 30, "Particle.png", 30);
        p->InstallCollider2D(true, {pos.x, pos.y, 30, 30});
        p->SetMoveSpeed(sx, sy);
        p->SetTag("enemyParticle");
        system.AddSprite(p);
    }

}

void Enemy::OnCollision(Sprite* other, System& system)
{
}
