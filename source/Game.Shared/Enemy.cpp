#include "pch.h"
#include "Enemy.h"
#include "PlayerProjectile.h"
#include <iostream>

using namespace std;
using namespace std::string_literals;
using namespace DirectX;
using namespace DX;

namespace GalagaPort
{
	Enemy::Enemy(string color, size_t pt, XMFLOAT2 stopPosition, float offset) :
		BasicSprite(color), Color{color}, Points{pt}, FinalPosition{stopPosition}, Place{offset}
	{
		XMFLOAT2 BasicTransform(0, -400);
		XMFLOAT2 SpriteScale(1, 1);
		Transform2D SpriteTransform(BasicTransform, 0.0f, SpriteScale);
		SetTransform(SpriteTransform);
	}
	bool Enemy::CheckForMissileHit(std::shared_ptr<PlayerProjectile> missile, size_t& score)
	{
		if((missile->Position.x > Transform().Position().x - 4 && missile->Position.x < Transform().Position().x + 4) && (missile->Position.y > Transform().Position().y - 4 && missile->Position.y < Transform().Position().y + 4))
		{
			IsAlive = false;
			score += Points;
			missile->IsActive = false;
			return true;
		}
		return false;
	}

	void Enemy::IdleMove(bool& movingLeft) //Idly moves the enemy left and right at their final position
	{
		if (IsAlive) //Only move if enemy is alive
		{
			if (movingLeft == true) //Moves left as long as it is not over or exactly ten units away from default space
			{
				if (FinalPosition.x - CurrentPosition.x >=1)
				{
					movingLeft = false;
				}
				else
				{
					CurrentPosition = { CurrentPosition.x - Speed, CurrentPosition.y };
				}
			}
			else
			{
				if ((FinalPosition.x - CurrentPosition.x) < -1)//Moves right as long as it is not over or exactly ten units away from default space
				{
					movingLeft = true;
				}
				else
				{
					CurrentPosition = { CurrentPosition.x + Speed, CurrentPosition.y };
				}
			}
			XMFLOAT2 SpriteScale(1, 1);
			Transform2D SpriteTransform(CurrentPosition, 0.0f, SpriteScale);
			SetTransform(SpriteTransform);
		}
	}
	
	void Enemy::FollowWave(float& yVar, float offset, float multiplier, float insideMultiplier, float xModifier) //Follows the path defined for the corresponding wave
	{
		if (CurrentPosition.y >= FinalPosition.y)
		{
			CurrentPosition.y = FinalPosition.y;
			FinalPosition = { CurrentPosition.x, CurrentPosition.y };
			DonePath = true;
		}

		else //If path isn't done, keep moving on it.
		{
			CurrentPosition.y += 0.025f; //Change y variable value slightly to move upward
			yVar = CurrentPosition.y;

			CurrentPosition.x = (multiplier * sin(insideMultiplier * (yVar-(Place * 12)) + offset)) / xModifier; //Sin wave function to make basic wave movement for enemies coming onto the screen
			if (CurrentPosition.x < -48 && yVar > -200) //Ensures the enemies will not leave the screen by going too far to the left
			{
				CurrentPosition.x = -48;
			}

			if (CurrentPosition.x > 48 && CurrentPosition.y > -200) //Ensures the enemies will not leave the screen by going too far to the right
			{
				CurrentPosition.x = 48;
			}
		}
		XMFLOAT2 SpriteScale(1, 1);
		Transform2D SpriteTransform(CurrentPosition, 0.0f, SpriteScale);
		SetTransform(SpriteTransform);
	}

	void Enemy::Shoot(int bulletIndex, std::shared_ptr<EnemyBullet> bullet[4]) //Shoot method to create new missile and set initial position.
	{
		DirectX::XMFLOAT2 BasicTransform = CurrentPosition;
		DirectX::XMFLOAT2 SpriteScale(.4, .4);
		DX::Transform2D SpriteTransform(BasicTransform, 0.0f, SpriteScale);

		bullet[bulletIndex] = std::make_shared<EnemyBullet>();
		bullet[bulletIndex].get()->SetTransform(SpriteTransform);
		bullet[bulletIndex].get()->Position = CurrentPosition;
	}
};