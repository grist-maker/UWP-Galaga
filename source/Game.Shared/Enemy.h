#pragma once
#include "BasicSprite.h"
#include "EnemyBullet.h"
#include "PlayerProjectile.h"

namespace GalagaPort
{
	class Enemy : public DirectXGame::BasicSprite
	{
	public:
		/// <summary>
		/// Constructor for the Enemy class, specifying enemy color, score, final position, and offset values.
		/// </summary>
		Enemy(std::string color = "Red", size_t pt = 100, DirectX::XMFLOAT2 stopPosition = {}, float offset = 0);
		/// <summary>
		/// Checks for collision between the enemy and a specific player projectile. Increments the score and explodes if hit.
		/// </summary>
		bool CheckForMissileHit(std::shared_ptr<GalagaPort::PlayerProjectile> missile, size_t& score);
		/// <summary>
		/// Points that are given to player when enemy is killed.
		/// </summary>
		size_t Points = 100;
		/// <summary>
		/// Whether or not enemy is still alive.
		/// </summary>
		bool IsAlive = true;
		/// <summary>
		/// The final position on the flight path.
		/// </summary>
		DirectX::XMFLOAT2 FinalPosition{ 0.0, 0.0};
		/// <summary>
		/// The current position that the enemy has on the path.
		/// </summary>
		DirectX::XMFLOAT2 CurrentPosition{0, -36};

		/// <summary>
		/// The enemy's color, used to dictate the sound they make on death.
		/// </summary>
		std::string Color;
		/// <summary>
		/// The speed at which the enemy is moving.
		/// </summary>
		float Speed = 0.02f;
		/// <summary>
		/// The place in the initial wave, how much it lags behind the first ship in the wave.
		/// </summary>
		float Place = 0;
		/// <summary>
		/// Whether or not the initial flight path onscreen is over.
		/// </summary>
		bool DonePath = false;
		/// <summary>
		/// Whether this enemy is currently exploding
		/// </summary>
		bool IsExploding = false;

		/// <summary>
		/// Whether or not it is idly moving left.
		/// </summary>
		bool MovingLeft = false;

		/// <summary>
		/// Shoots a projectile, adding a new EnemyBullet instance and returning it.
		/// </summary>
		/// <returns>The newly created projectile.</returns>
		void Shoot(int bulletIndex, std::shared_ptr<EnemyBullet> bullet[4]);
		/// <summary>
		/// Idle movement at top after finishing flight path.
		/// </summary>
		void IdleMove(bool& movingLeft);
		/// <summary>
		/// Defines wave movement for the enemy, mimicking a sine wave with defined variables
		/// </summary>
		void FollowWave(float& yVar, float offset, float multiplier, float insideMultiplier, float xModifier);
		/// <summary>
		/// The time that the explosion occurred, if one is in progress.
		/// </summary>
		double TimeOfExplosion = 0; //The time that the explosion began for proper animation
	};
}