#pragma once
#include "pch.h"
#include "BasicSprite.h"
#include <DeviceResources.h>

namespace GalagaPort
{
	class EnemyBullet : public DirectXGame::BasicSprite
	{
	public:
		EnemyBullet();
		float Speed = 0.4f; //Speed of the enemy projectile downward
		DirectX::XMFLOAT2 Position{0.0, 0.0};
		void Fly();
	};
}