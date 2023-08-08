#pragma once
#include "WaveSpawner.h"
#include "StepTimer.h"
#include "GalagaText.h"
#include "directxtk/Audio.h"

namespace GalagaPort
{
	class GalagaManager : public DX::DrawableGameComponent
	{
	public:
		/// <summary>
		/// Whether or not the player is dead, indicating a loss of the game
		/// </summary>
		bool PlayerDead = false;
		/// <summary>
		/// Whether or not the player has won the game, indicating the game is over
		/// </summary>
		bool PlayerWin = false;

		/// <summary>
		/// The player's score, with them getting 100 points for each enemy shot.
		/// </summary>
		size_t Score = 0;
		/// <summary>
		/// Whether or not the game is started, that is, out of the title screen.
		/// </summary>
		bool GameStart = false;
		/// <summary>
		/// This integer indicates the state of the enemy. They have an idle animation consisting of two sprites, which this variable coordinates throughout the wave.
		/// </summary>
		int enemyState = 0;
		/// <summary>
		/// The time that the game was actually started, that is, the time that the player left the title screen.
		/// </summary>
		double GameStartTime = 0;

		/// <summary>
		/// The period of time enemies wait between spawning a new bullet to shoot the player.
		/// </summary>
		size_t EnemyShotCooldown = 1;
		/// <summary>
		/// The seconds within the game when the enemy last shot a bullet.
		/// </summary>
		double LastEnemyShot = 0;

		/// <summary>
		/// The seconds that a player is invulnerable after getting shot.
		/// </summary>
		double PlayerHurtCooldown = 2;
		/// <summary>
		/// The game time in seconds that the player was last shot at.
		/// </summary>
		double LastPlayerHit = 0;

		/// <summary>
		/// The text object to display the score onscreen.
		/// </summary>
		std::shared_ptr<GalagaText> ScoreText;
		/// <summary>
		/// The text object to display the final (win or loss) message onscreen.
		/// </summary>
		std::shared_ptr<GalagaText> FinalText;

		/// <summary>
		/// The sound that plays when the game enters the title screen.
		/// </summary>
		std::unique_ptr<DirectX::SoundEffect> StartingNoise{ nullptr };

		/// <summary>
		/// The sound that plays when a red alien is shot.
		/// </summary>
		std::shared_ptr<DirectX::SoundEffect>  RedDeath{ nullptr };
		/// <summary>
		/// The sound that plays when a green alien is shot.
		/// </summary>
		std::shared_ptr<DirectX::SoundEffect>  GreenDeath{ nullptr };
		/// <summary>
		/// The sound that plays when a yellow alien is shot.
		/// </summary>
		std::shared_ptr<DirectX::SoundEffect>  YellowDeath{ nullptr };

		/// <summary>
		/// The sound that plays when the player enters the win screen following the game.
		/// </summary>
		std::unique_ptr<DirectX::SoundEffect>  WinScreen{ nullptr };
		/// <summary>
		/// The sound that plays when the player enters the loss screen following the game.
		/// </summary>
		std::unique_ptr<DirectX::SoundEffect>  LossScreen{ nullptr };

		/// <summary>
		/// The sound that plays when the player shoots a missile.
		/// </summary>
		std::shared_ptr<DirectX::SoundEffect>  PlayerShot{ nullptr };
		/// <summary>
		/// The sound that plays when the player is shot by an enemy.
		/// </summary>
		std::shared_ptr<DirectX::SoundEffect>  PlayerDeath{ nullptr };

		/// <summary>
		/// The audio engine used to play sound effects in the game.
		/// </summary>
		std::unique_ptr<DirectX::AudioEngine> GalagaAudioEngine{nullptr};

		/// <summary>
		/// Whether or not the start sound has already been played
		/// </summary>
		bool PlayedStartSound = false;

		/// <summary>
		/// GalagaManager constructor that sets up the manager for the game, with the proper device resources and camera reference.
		/// </summary>
		/// <param name="deviceResources">The device resources used in rendering objects in the game.</param>
		/// <param name="camera">The camera used to let the user observe components in the game.</param>
		GalagaManager(const std::shared_ptr<DX::DeviceResources>& deviceResources, const std::shared_ptr<DX::Camera>& camera);
		
		/// <summary>
		/// Checks if an enemy is able to shoot, shooting if so.
		/// </summary>
		void EnemyShotCheck();
		/// <summary>
		/// Checks if any enemys have been hit by an active player projectile.
		/// </summary>
		void CheckForEnemyCollisions(double currentTime);
		/// <summary>
		/// Checks if the player has been hit by any active enemy projectiles.
		/// </summary>
		void CheckForPlayerCollisions(const DX::StepTimer& timer);
		/// <summary>
		/// Used to let the player shoot, if they are currently able to based on the number of already active missiles.
		/// </summary>
		void PlayerShoot();

		/// <summary>
		/// Moves the player spaceship by a provided value.
		/// </summary>
		void MoveSpaceship(float amount);

		/// <summary>
		/// Draws a background onto the screen with correct size and specification, given a reference to the sprite being drawn, the sprite's image, and the device context associated to draw it.
		/// </summary>
		void DrawBackground(DirectXGame::BasicSprite& sprite, winrt::com_ptr<ID3D11ShaderResourceView> spriteData, ID3D11DeviceContext* direct3DDeviceContext);
		/// <summary>
		/// Draws any sprite onto the screen, given a reference to the sprite being drawn, the sprite's image, and the device context associated to draw it.
		/// </summary>
		void DrawSprite(DirectXGame::BasicSprite& sprite, winrt::com_ptr<ID3D11ShaderResourceView> spriteData, ID3D11DeviceContext* direct3DDeviceContext);
		/// <summary>
		/// Draws all active aliens onto the screen, provided the correct time value and device context.
		/// </summary>
		void DrawAliens(ID3D11DeviceContext* direct3DDeviceContext, double CurrentTime);
		/// <summary>
		/// Draws the player's lives on the screen, pvoided the correct device context, based on the number of times they've been shot.
		/// </summary>
		void DrawLives(ID3D11DeviceContext* direct3DDeviceContext);
		/// <summary>
		/// Draws all the player's missiles on the screen.
		/// </summary>
		void DrawPlayerMissiles(ID3D11DeviceContext* direct3DDeviceContext);
		/// <summary>
		/// Draws all of the enemy missiles on the screen.
		/// </summary>
		void DrawEnemyMissiles(ID3D11DeviceContext* direct3DDeviceContext);

		/// <summary>
		/// Resets the game state to reset the game and allow the user to play again without closing and reopening the application.
		/// </summary>
		void ResetGame();

		/// <summary>
		/// Initializes vertices for endering to the screen.
		/// </summary>
		void InitializeVertices();
		
		/// /// <summary>
		/// Creates all necessary resources for the game.
		/// </summary>
		void CreateDeviceDependentResources();
		/// <summary>
		/// Releases all necessary resources for the game.
		/// </summary>
		virtual void ReleaseDeviceDependentResources() override;

		/// <summary>
		/// Updates elements of the Galaga scene as needed to indicate game state to the player.
		/// </summary>
		virtual void Update(const DX::StepTimer& timer) override;
		/// <summary>
		/// Renders the Galaga Scene as it updates by drawing key elements in the appropriate order.
		/// </summary>
		virtual void Render(const DX::StepTimer& timer) override;

		/// <summary>
		/// The wave controller, which supervises and controls logic of the waves of enemies in the game.
		/// </summary>
		std::shared_ptr<WaveSpawner> WaveController;

	private:
		struct VSCBufferPerObject
		{
			DirectX::XMFLOAT4X4 WorldViewProjection;
			DirectX::XMFLOAT4X4 TextureTransform;

			VSCBufferPerObject() :
				WorldViewProjection(DX::MatrixHelper::Identity), TextureTransform(DX::MatrixHelper::Identity)
			{ };

			VSCBufferPerObject(const DirectX::XMFLOAT4X4& wvp, const DirectX::XMFLOAT4X4& textureTransform) :
				WorldViewProjection(wvp), TextureTransform(textureTransform)
			{ }
		};
		winrt::com_ptr<ID3D11VertexShader> mVertexShader;
		winrt::com_ptr<ID3D11PixelShader> mPixelShader;
		winrt::com_ptr<ID3D11InputLayout> mInputLayout;
		winrt::com_ptr<ID3D11Buffer> mVertexBuffer;
		winrt::com_ptr<ID3D11Buffer> mIndexBuffer;
		winrt::com_ptr<ID3D11Buffer> mVSCBufferPerObject;
		winrt::com_ptr<ID3D11SamplerState> mTextureSampler;
		winrt::com_ptr<ID3D11BlendState> mAlphaBlending;
		VSCBufferPerObject mVSCBufferPerObjectData;
		std::uint32_t mIndexCount{ 0 };

		/// <summary>
		/// Sprite batch that's used to render text in the game.
		/// </summary>
		std::shared_ptr<DirectX::SpriteBatch> TextBatch;
		/// <summary>
		/// SpriteFont defining the specific font used on all text in the game.
		/// </summary>
		std::shared_ptr<DirectX::SpriteFont> GalagaSpriteFont;

		/// <summary>
		/// The delay between updating enemy sprites within the scene, in seconds.
		/// </summary>
		inline static const double SpriteUpdateDelay{ 1.0 };
		/// <summary>
		/// The last time (in seconds) that the enemy sprites were updated.
		/// </summary>
		inline static double LastUpdateTime{ 0 };

		/// <summary>
		/// The two red alien sprites that are used for their basic animation.
		/// </summary>
		winrt::com_ptr<ID3D11ShaderResourceView> redAlienSprites[2];
		/// <summary>
		/// The two yellow alien sprites that are used for their basic animation.
		/// </summary>
		winrt::com_ptr<ID3D11ShaderResourceView> yellowAlienSprites[2];
		/// <summary>
		/// The two green alien sprites that are used for their basic animation.
		/// </summary>
		winrt::com_ptr<ID3D11ShaderResourceView> greenAlienSprites[2];
		/// <summary>
		/// The six alien sprites that are used for their basic animation.
		/// </summary>
		winrt::com_ptr<ID3D11ShaderResourceView> ExplosionSprites[6];
		/// <summary>
		/// The sprite for player missiles, displayed when they shoot.
		/// </summary>
		winrt::com_ptr<ID3D11ShaderResourceView> PlayerMissileSprite;
		
		/// <summary>
		/// The sprite for the title screen of the game, displayed on game startup and after game win or loss screen.
		/// </summary>
		winrt::com_ptr<ID3D11ShaderResourceView> TitleScreen;
		/// <summary>
		/// The sprite for the space background, shown ingame.
		/// </summary>
		winrt::com_ptr<ID3D11ShaderResourceView> SpaceBackground;
		/// <summary>
		/// The sprite for the spaceship, which the user controls ingame.
		/// </summary>
		winrt::com_ptr<ID3D11ShaderResourceView> SpaceshipBase;
		/// <summary>
		/// The sprite for the spaceship while recovering from being hurt.
		/// </summary>
		winrt::com_ptr<ID3D11ShaderResourceView> HurtSpaceshipBase;

		/// <summary>
		/// The BasicSprite for the title screen of the game.
		/// </summary>
		std::shared_ptr<DirectXGame::BasicSprite> TitleScreenSprite;
		/// <summary>
		/// The BasicSprite for the space background shown ingame.
		/// </summary>
		std::shared_ptr<DirectXGame::BasicSprite> SpaceBackgroundSprite;
		/// <summary>
		/// The spaceship object that the user controls.
		/// </summary>
		std::shared_ptr<GalagaPort::Spaceship> SpaceshipSprite;
		/// <summary>
		/// The player missiles that the player can shoot ingame.
		/// </summary>
		std::shared_ptr<GalagaPort::PlayerProjectile> PlayerMissiles[2] = { nullptr, nullptr };
		/// <summary>
		/// The enemy missiles that can be shot ingame.
		/// </summary>
		std::shared_ptr<GalagaPort::EnemyBullet> EnemyMissiles[4] = { nullptr, nullptr, nullptr, nullptr };
		/// <summary>
		/// The lives that the player has, to be displayed onscreen.
		/// </summary>
		std::shared_ptr<GalagaPort::Spaceship> Lives[3];
	};
}