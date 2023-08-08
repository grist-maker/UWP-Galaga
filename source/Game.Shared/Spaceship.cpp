#include "pch.h"
#include "Spaceship.h"

using namespace std;
using namespace std::string_literals;
using namespace DirectX;
using namespace DX;

namespace GalagaPort
{
    Spaceship::Spaceship()
    {
        XMFLOAT2 BasicTransform(0, -40);
        XMFLOAT2 SpriteScale(1, 1);
        Position = BasicTransform;
        Transform2D SpriteTransform(BasicTransform, 0.0f, SpriteScale);
        SetTransform(SpriteTransform);
    }

    std::shared_ptr<PlayerProjectile> Spaceship::Shoot() //Shoot method to create new missile and set initial position.
    {
        auto missile = std::make_shared<PlayerProjectile>();
        if (missile != nullptr)
        {
            missile->Position.x = Position.x;
            missile->Position.y = Position.y + 2;
            missile->IsActive = true;
        }

        return missile;
    }

    void Spaceship::CheckForCollision(std::shared_ptr<EnemyBullet> Bullet[4], int BulletIndex, double PlayerHurtCooldown, double& LastPlayerHit, double currentTime, std::shared_ptr<DirectX::SoundEffect> PlayerHit)
    {
        if (Bullet[BulletIndex] != nullptr &&(Bullet[BulletIndex]->Position.x > Transform().Position().x - 4 && Bullet[BulletIndex]->Position.x < Transform().Position().x + 4) && (Bullet[BulletIndex]->Position.y > Transform().Position().y - 4 && Bullet[BulletIndex]->Position.y < Transform().Position().y + 4))
        {
            Bullet[BulletIndex] = nullptr;
            if (LastPlayerHit == 0 || LastPlayerHit + PlayerHurtCooldown < currentTime)
            {
                life--;
                LastPlayerHit = currentTime;
                PlayerHit->Play();
            }
        }
    }

    void Spaceship::MoveSpaceship(float Amount)
    {
        if ((Amount > 0 && Position.x < 48) || (Amount < 0 && Position.x > -48))
        {
            auto NewTransform = Position;
            NewTransform.x += Amount;
            SetTransform(NewTransform);
            Position = NewTransform;
        }
    }
    
    void Spaceship::PlayerShoot(std::shared_ptr<PlayerProjectile> PlayerMissiles[2], std::shared_ptr<DirectX::SoundEffect> PlayerShotSound)
    {
        if (PlayerMissiles[0] == nullptr || !PlayerMissiles[0]->IsActive)
        {
            PlayerMissiles[0] = Shoot();
            PlayerShotSound->Play();
        }
        else if (PlayerMissiles[1] == nullptr || PlayerMissiles[1]->IsActive)
        {
           PlayerMissiles[1] = Shoot();
           PlayerShotSound->Play();
        }
    }
}