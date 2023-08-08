#pragma once
#include "Enemy.h"
#include "DrawableGameComponent.h"
#include "Spaceship.h"

namespace GalagaPort
{
    class WaveSpawner
    {
    public:
        WaveSpawner() = default;
        //References to death sounds for each enemy type
        int CurrentWave = 0;

        //These are times each wave will spawn
        const float wave1Time = 1;
        const float wave2Time = 4;
        const float wave3Time = 8;
        const float wave4Time = 11;
        const float wave5Time = 14;
        //These are the y values that each wave spawns at.
        float wave1Y = -40;
        float wave2Y = -40;
        float wave3Y = -40;
        float wave4Y = -40;
        float wave5Y = -40;
        //This takes the place of the variable multiplier.
        const float wave1Multiplier = 380;
        const float wave2Multiplier = 390;
        const float wave3Multiplier = 375;
        const float wave4Multiplier = 370;
        const float wave5Multiplier = 375;
        //This takes the place of the variable xModifier
        const float wave1XMultiplier = 8;
        const float wave2XMultiplier = 8;
        const float wave3XMultiplier = 8;
        const float wave4XMultiplier = 8;
        const float wave5XMultiplier = 8;
        //This takes the place of the variable insideMultiplier
        const float wave1InsideMultiplier = 0.12f;
        const float wave2InsideMultiplier = 0.13f;
        const float wave3InsideMultiplier = 0.14f;
        const float wave4InsideMultiplier = 0.15f;
        const float wave5InsideMultiplier = 0.16f;
        //This takes the place of the variable offset
        const float wave1Offset = 37.5;
        const float wave2Offset = 32;
        const float wave3Offset = 23;
        const float wave4Offset = 15;
        const float wave5Offset = 06;
        //Place in the order of the wave. Each enemy has an offset based on if they are 2nd or 1st, etc. This offsets position relative to other wave members
        const float firstPlace = 0;
        const float secondPlace = 1;
        const float thirdPlace = 2;
        const float fourthPlace = 3;
        const float fifthPlace = 4;
        const float sixthPlace = 5;
        const float seventhPlace = 6;
        const float eigthPlace = 7;

        //Whether or not it is idly moving left after flight path completion.
        bool movingLeft;

        /// <summary>
        /// Defines patrol for enemies to get to final position.
        /// </summary>
        void SetPatrol();
        /// <summary>
        /// Checks for collision between a specific player missile and any live enemies.
        /// </summary>
        /// <param name="time">The current time in the system.</param>
        /// <param name="missile">The missile being checked for collisions with live enemies.</param>
        /// <param name="score">The score that is displayed on the screen, adjusted if an enemy is hit.</param>
        /// <param name="Red">The sound effect played if the enemy killed is red.</param>
        /// <param name="Yellow">The sound effect played if the enemy killed is yellow.</param>
        /// <param name="Green">The sound effect played if the enemy killed is green.</param>
        void CheckForCollision(double time, std::shared_ptr<PlayerProjectile> missile, size_t& score, std::shared_ptr<DirectX::SoundEffect> Red, std::shared_ptr<DirectX::SoundEffect> Yellow, std::shared_ptr<DirectX::SoundEffect> Green);

        /// <summary>
        /// Creates a new enemy projectile, in the indicated index, from the indicated enemy.
        /// </summary>
        /// <param name="bulletIndex">The index for the new bullet being created.</param>
        /// <param name="WaveIndex">The index for the wave that shot it.</param>
        /// <param name="EnemyIndex">The inner index for the enemy within the wave that shot the bullet.</param>
        /// <param name="bullet">The array of enemey bullets that are active.</param>
        void NewProjectile(int bulletIndex, int WaveIndex, int EnemyIndex, std::shared_ptr<EnemyBullet> bullet[4]);
        /// <summary>
        /// Checks if the wave indicated by the index is capable of shooting at the player.
        /// </summary>
        /// <param name="currentWave">The wave index that's being checked for validity.</param>
        bool CheckIfValid(int currentWave);
        /// <summary>
        /// Shoots the next enemy bullet, then updating the time that the last enemy shot occurred.
        /// </summary>
        /// <param name="bulletIndex">The index in the array of the specific place where the new bullet will be stored.</param>
        /// <param name="timePassed">The current time within the system.</param>
        /// <param name="newBullet">The full array of enemy bullets.</param>
        /// <param name="EnemyLastShot">The time that the last enemy shot.</param>
        void ShootNextBullet(int bulletIndex, double timePassed, std::shared_ptr<EnemyBullet> newBullet[4], double& enemyLastShot); //Randomly generates next enemy to shoot

        /// <summary>
        /// Moves enemies that are going towards the top of the screen along their entry wave.
        /// </summary>
        void MoveWave(int waveNumber);
        /// <summary>
        /// The function to update all enemies within the system positionally, whether moving idly or following the initial entry eave.
        /// </summary>
        void UpdateWaves(const double timer);
        /// <summary>
        /// The vector of all enemies within the game.
        /// </summary>
        std::vector<std::shared_ptr<GalagaPort::Enemy>> mSprites;
    };
}