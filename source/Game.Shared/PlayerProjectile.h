#pragma once
#include "BasicSprite.h"
#include "VertexDeclarations.h"

namespace GalagaPort
{
	class PlayerProjectile : public DirectXGame::BasicSprite
	{
	public:
		bool IsActive = false;
		float speed = 1; //Speed of the player missile upward
		DirectX::XMFLOAT2 Position{ 350, 625 };
		void Fly();
	};
}