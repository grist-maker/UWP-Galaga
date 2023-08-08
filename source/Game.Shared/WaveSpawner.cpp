#include "pch.h"
#include "WaveSpawner.h"
#include "VertexDeclarations.h"

using namespace std;
using namespace DirectX;
using namespace DX;

namespace GalagaPort
{	
	void WaveSpawner::SetPatrol() //Sets all enemy waves with necessary starting variables. This controls 5 waves, each with 8 enemies.
	{
		mSprites.clear();
		//Initializes movingleft variable
		movingLeft = true;

		//Initializes the first wave
		mSprites.push_back(std::make_shared<Enemy>("Red", 100, DirectX::XMFLOAT2(-15, 20), firstPlace));
		mSprites.push_back(std::make_shared<Enemy>("Yellow", 100, DirectX::XMFLOAT2(-10, 20), secondPlace));
		mSprites.push_back(std::make_shared<Enemy>("Red", 100, DirectX::XMFLOAT2(-5, 20), thirdPlace));
		mSprites.push_back(std::make_shared<Enemy>("Yellow", 100, DirectX::XMFLOAT2(0, 20), fourthPlace));
		mSprites.push_back(std::make_shared<Enemy>("Red", 100, DirectX::XMFLOAT2(5, 20), fifthPlace));
		mSprites.push_back(std::make_shared<Enemy>("Yellow", 100, DirectX::XMFLOAT2(10, 20), sixthPlace));
		mSprites.push_back(std::make_shared<Enemy>("Red", 100, DirectX::XMFLOAT2(15, 20), seventhPlace));
		mSprites.push_back(std::make_shared<Enemy>("Yellow", 100, DirectX::XMFLOAT2(20, 20), eigthPlace));

		//Initializes the second wave
		mSprites.push_back(std::make_shared<Enemy>("Green", 100, DirectX::XMFLOAT2(-15, 25), firstPlace));
		mSprites.push_back(std::make_shared<Enemy>("Red", 100, DirectX::XMFLOAT2(-10, 25), secondPlace));
		mSprites.push_back(std::make_shared<Enemy>("Green", 100, DirectX::XMFLOAT2(-5, 25), thirdPlace));
		mSprites.push_back(std::make_shared<Enemy>("Red", 100, DirectX::XMFLOAT2(0, 25), fourthPlace));
		mSprites.push_back(std::make_shared<Enemy>("Green", 100, DirectX::XMFLOAT2(5, 25), fifthPlace));
		mSprites.push_back(std::make_shared<Enemy>("Red", 100, DirectX::XMFLOAT2(10, 25), sixthPlace));
		mSprites.push_back(std::make_shared<Enemy>("Green", 100, DirectX::XMFLOAT2(15, 25), seventhPlace));
		mSprites.push_back(std::make_shared<Enemy>("Red", 100, DirectX::XMFLOAT2(20, 25), eigthPlace));

		//Initializes the third wave
		mSprites.push_back(std::make_shared<Enemy>("Red", 100, DirectX::XMFLOAT2(-15, 30), firstPlace));
		mSprites.push_back(std::make_shared<Enemy>("Red", 100, DirectX::XMFLOAT2(-10, 30), secondPlace));
		mSprites.push_back(std::make_shared<Enemy>("Red", 100, DirectX::XMFLOAT2(-5, 30), thirdPlace));
		mSprites.push_back(std::make_shared<Enemy>("Red", 100, DirectX::XMFLOAT2(0, 30), fourthPlace));
		mSprites.push_back(std::make_shared<Enemy>("Red", 100, DirectX::XMFLOAT2(5, 30), fifthPlace));
		mSprites.push_back(std::make_shared<Enemy>("Red", 100, DirectX::XMFLOAT2(10, 30), sixthPlace));
		mSprites.push_back(std::make_shared<Enemy>("Red", 100, DirectX::XMFLOAT2(15, 30), seventhPlace));
		mSprites.push_back(std::make_shared<Enemy>("Red", 100, DirectX::XMFLOAT2(20, 30), eigthPlace));

		//Initializes the fourth wave
		mSprites.push_back(std::make_shared<Enemy>("Yellow", 100, DirectX::XMFLOAT2(-15, 35), firstPlace));
		mSprites.push_back(std::make_shared<Enemy>("Yellow", 100, DirectX::XMFLOAT2(-10, 35), secondPlace));
		mSprites.push_back(std::make_shared<Enemy>("Yellow", 100, DirectX::XMFLOAT2(-5, 35), thirdPlace));
		mSprites.push_back(std::make_shared<Enemy>("Yellow", 100, DirectX::XMFLOAT2(0, 35), fourthPlace));
		mSprites.push_back(std::make_shared<Enemy>("Yellow", 100, DirectX::XMFLOAT2(5, 35), fifthPlace));
		mSprites.push_back(std::make_shared<Enemy>("Yellow", 100, DirectX::XMFLOAT2(10, 35), sixthPlace));
		mSprites.push_back(std::make_shared<Enemy>("Yellow", 100, DirectX::XMFLOAT2(15, 35), seventhPlace));
		mSprites.push_back(std::make_shared<Enemy>("Yellow", 100, DirectX::XMFLOAT2(20, 35), eigthPlace));

		//Initializes the fifth wave
		mSprites.push_back(std::make_shared<Enemy>("Yellow", 100, DirectX::XMFLOAT2(-15, 40), firstPlace));
		mSprites.push_back(std::make_shared<Enemy>("Yellow", 100, DirectX::XMFLOAT2(-10, 40), secondPlace));
		mSprites.push_back(std::make_shared<Enemy>("Yellow", 100, DirectX::XMFLOAT2(-5, 40), thirdPlace));
		mSprites.push_back(std::make_shared<Enemy>("Yellow", 100, DirectX::XMFLOAT2(0, 40), fourthPlace));
		mSprites.push_back(std::make_shared<Enemy>("Yellow", 100, DirectX::XMFLOAT2(5, 40), fifthPlace));
		mSprites.push_back(std::make_shared<Enemy>("Yellow", 100, DirectX::XMFLOAT2(10, 40), sixthPlace));
		mSprites.push_back(std::make_shared<Enemy>("Yellow", 100, DirectX::XMFLOAT2(15, 40), seventhPlace));
		mSprites.push_back(std::make_shared<Enemy>("Yellow", 100, DirectX::XMFLOAT2(20, 40), eigthPlace));
	}
	
	void WaveSpawner::MoveWave(int waveNumber) //Draws a given wave of enemies
	{
		for (int i = 0; i < 8; i++)
		{
			if(mSprites[waveNumber*8 + i]->IsAlive) //Only draws enemy if they are alive
			{
				if (mSprites[waveNumber*8 + i]->DonePath) //If path is done, move them idly from side to side
				{
					mSprites[waveNumber * 8 + i]->IdleMove(movingLeft);
				}
				else //Otherwise, we need to continue their initial path movement based on their wave's path and their place
				{
					if (waveNumber == 0)
					{
						mSprites[waveNumber * 8 + i]->FollowWave(wave1Y, wave1Offset, wave1Multiplier, wave1InsideMultiplier, wave1XMultiplier);
					}
					else if (waveNumber == 1)
					{
						mSprites[waveNumber * 8 + i]->FollowWave(wave2Y, wave2Offset, wave2Multiplier, wave2InsideMultiplier, wave2XMultiplier);
					}
					else if (waveNumber == 2)
					{
						mSprites[waveNumber * 8 + i]->FollowWave(wave3Y, wave3Offset, wave3Multiplier, wave3InsideMultiplier, wave3XMultiplier);
					}
					else if (waveNumber == 3)
					{
						mSprites[waveNumber * 8 + i]->FollowWave(wave4Y, wave4Offset, wave4Multiplier, wave4InsideMultiplier, wave4XMultiplier);
					}
					else if (waveNumber == 4)
					{
						mSprites[waveNumber * 8 + i]->FollowWave(wave5Y, wave5Offset, wave5Multiplier, wave5InsideMultiplier, wave5XMultiplier);
					}
				}
				mSprites[waveNumber * 8 + i]->SetTransform(mSprites[waveNumber * 8 + i]->CurrentPosition);
			}
		}
	}

	void WaveSpawner::CheckForCollision(double time, std::shared_ptr<PlayerProjectile> missile, size_t& score, std::shared_ptr<DirectX::SoundEffect> Red, std::shared_ptr<DirectX::SoundEffect> Yellow, std::shared_ptr<DirectX::SoundEffect> Green)
	{
		for (int i = 0; i < 40; i++) //Goes through enemies to see if  any have collided with a missile
		{
			if(mSprites[i] != nullptr && mSprites[i]->IsAlive && missile != nullptr && missile->IsActive && mSprites[i]->CheckForMissileHit(missile, score))
			{
				mSprites[i]->TimeOfExplosion = time;
				mSprites[i]->IsExploding = true;
				if (mSprites[i]->Color == "Red")
				{
					Red->Play();
				}
				else if (mSprites[i]->Color == "Yellow")
				{
					Yellow->Play();
				}
				else if (mSprites[i]->Color == "Green")
				{
					Green->Play();
				}
			}
		}
	}

	void WaveSpawner::NewProjectile(int bulletIndex, int WaveIndex, int EnemyIndex, std::shared_ptr<EnemyBullet> bullet[4])
	{
		mSprites[EnemyIndex + WaveIndex * 8]->Shoot(bulletIndex, bullet);
	}

	bool WaveSpawner::CheckIfValid(int currentWave) //Checks to see if the enemy generated to shoot the next projectile is valid
	{
		bool k = false;
		for (int l = 0; l < 8; l++)
		{
			if (mSprites[currentWave*8 + l]->IsAlive && mSprites[currentWave * 8 + l]->DonePath) //Makes sure that the enemy is both alive and done its initial path movement
			{
				k = true;
			}
		}
		return k;
	}
	
	void WaveSpawner::ShootNextBullet(int bulletIndex, double timePassed, std::shared_ptr<EnemyBullet> newBullet[4], double& enemyLastShot) //Randomly selects an enemy and has them shoot if possible
	{
		int i = 0;
		int j = 0;

		i = rand() % 8;

		if (timePassed <= wave2Time) //Checks to ensure wave is spawned
		{
			j = 0;
		}
		else if (timePassed <= wave3Time)
		{
			j = rand() % 2;
		}
		else if (timePassed <= wave4Time)
		{
			j = rand() % 3;
		}
		else if (timePassed <= wave5Time)
		{
			j = rand() % 4;
		}
		else
		{
			j = rand() % 5;
		}

		if (CheckIfValid(j))
		{
			int m = 0; //Gets random enemy that is alive to shoot

			while (m < 5)
			{
				if (mSprites[i + j*8]->IsAlive)
				{
					NewProjectile(bulletIndex, j, i, newBullet);
					enemyLastShot = timePassed;
					m = 5;
				}
				else
				{
					m++;
					i = rand() % 8;
				}
			}
		}
	}

	void WaveSpawner::UpdateWaves(const double timer)
	{
		if (CurrentWave >= 1 || timer > wave1Time)
		{
			MoveWave(0);
			if (CurrentWave == 0)
			{
				CurrentWave++;
			}
		}
		if (CurrentWave >= 2 || timer > wave2Time)
		{
			MoveWave(1);
			if (CurrentWave == 0)
			{
				CurrentWave++;
			}
		}
		if (CurrentWave >= 3 || timer > wave3Time)
		{
			MoveWave(2);
			if (CurrentWave == 1)
			{
				CurrentWave++;
			}
		}
		if (CurrentWave >= 4 || timer > wave4Time)
		{
			MoveWave(3);
			if (CurrentWave == 2)
			{
				CurrentWave++;
			}
		}
		if (CurrentWave >= 5 || timer > wave5Time)
		{
			MoveWave(4);
			if (CurrentWave == 3)
			{
				CurrentWave++;
			}
		}
	}
}