#pragma once
#include "PlayerProjectile.h"
#include "EnemyBullet.h"
#include "BasicSprite.h"
#include "directxtk/Audio.h"

namespace GalagaPort
{
	class Spaceship : public DirectXGame::BasicSprite
	{
	public:
		/// <summary>
		/// Position of the spaceship on the screen.
		/// </summary>
		DirectX::XMFLOAT2 Position{ 0, -45 };
		/// <summary>
		/// Ship movement speed left and right.
		/// </summary>
		float changeAmt = 9;
		/// <summary>
		/// Array for potential onscreen missiles at a time.
		/// </summary>
		bool missileActive[2] = { false, false };
		/// <summary>
		/// How many lives the player currently has.
		/// </summary>
		int life = 3;

		/// <summary>
		/// Whether or not the player is hurt (or able to be hurt again)
		/// </summary>
		bool isHurt = false;

		/// <summary>
		/// Checks to see if a collision has occured between the spaceship and an enemy bullet.
		/// </summary>
		/// <param name="CurrentBullet">The array of enemy bullets being checked.</param>
		/// <param name="BulletIndex">The index in the array for the exact bullet being referenced.</param>
		/// <param name="PlayerHurtCooldown">The time that the player is invulnerable to recover after being hit.</param>
		/// <param name="LastPlayerHit">The time that the player was last hit.</param>
		/// <param name="currentTime">The current time within the game.</param>
		/// <param name="PlayerHit">The sound effect played if the player is hit.</param>
		void CheckForCollision(std::shared_ptr<EnemyBullet> CurrentBullet[4], int BulletIndex, double PlayerHurtCooldown, double& LastPlayerHit, double currentTime, std::shared_ptr<DirectX::SoundEffect> PlayerHit);
		/// <summary>
		/// Moves the spaceship by a certain amount across the screen.
		/// </summary>
		/// <param name="Amount">The amount that the spaceship should be moved by.</param>
		void MoveSpaceship(float Amount);
		/// <summary>
		/// Checks if the player can shoot a new missile from their ship to hit enemies.
		/// </summary>
		/// <param name="PlayerMissiles">The array of potential player missiles.</param>
		/// <param name="PlayerShotSound">The sound that plays after the player shoots.</param>
		void PlayerShoot(std::shared_ptr<PlayerProjectile> PlayerMissiles[2], std::shared_ptr<DirectX::SoundEffect> PlayerShotSound);
		/// <summary>
		/// Actually shoots a missile from the player ship.
		/// </summary>
		/// <returns>A shared pointer to the new player projectile.</returns>
		std::shared_ptr<PlayerProjectile> Shoot();
		/// <summary>
		/// The default constructor for the Spaceship class.
		/// </summary>
		Spaceship();
	};
}