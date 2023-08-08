#include "pch.h"
#include "PlayerProjectile.h"

namespace GalagaPort
{
    void PlayerProjectile::Fly() //Updates position of the missile overtime
    {
        if (IsActive)
        {
            Position.y += speed;
            DirectX::XMFLOAT2 BasicTransform = Position;
            DirectX::XMFLOAT2 SpriteScale(.4, .4);
            DX::Transform2D SpriteTransform(BasicTransform, 0.0f, SpriteScale);
            SetTransform(SpriteTransform);
        }
    }
}