#include "pch.h"
#include "EnemyBullet.h"

using namespace std;
using namespace DX;
namespace GalagaPort
{
    EnemyBullet::EnemyBullet():
       BasicSprite("EnemyBullet")
    {
    }
    void EnemyBullet::Fly() //Updates position of the missile overtime
    {
        Position.y -= Speed; //Changes y position by speed value, then updates it and collision box position accordingly
        DirectX::XMFLOAT2 BasicTransform = Position;
        DirectX::XMFLOAT2 SpriteScale(.4, .4);
        DX::Transform2D SpriteTransform(BasicTransform, 0.0f, SpriteScale);
        SetTransform(SpriteTransform);
    }
}