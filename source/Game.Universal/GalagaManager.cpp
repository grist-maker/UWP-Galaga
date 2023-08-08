#include "pch.h"
#include "GalagaManager.h"
#include "Utility.h"
#include "Camera.h"

using namespace std;
using namespace DirectX;
using namespace DX;

namespace GalagaPort
{
	GalagaManager::GalagaManager(const std::shared_ptr<DX::DeviceResources>& deviceResources, const std::shared_ptr<DX::Camera>& camera) :
		DrawableGameComponent(deviceResources, camera)
	{
		WaveController = std::make_shared<WaveSpawner>();
		WaveController->SetPatrol();

		CreateDeviceDependentResources();
		TitleScreenSprite = std::make_shared<DirectXGame::BasicSprite>();
		SpaceBackgroundSprite = std::make_shared<DirectXGame::BasicSprite>();
		SpaceshipSprite = std::make_shared<GalagaPort::Spaceship>();
	
		ScoreText = std::make_shared<GalagaPort::GalagaText>(deviceResources);
		FinalText = std::make_shared<GalagaPort::GalagaText>(deviceResources);

		XMFLOAT2 BasicTransform(0, 0);
		XMFLOAT2 TitleScale(50, 50);
		Transform2D FinalTransform(BasicTransform, 0.0f, TitleScale);
		TitleScreenSprite->SetTransform(FinalTransform);
		SpaceBackgroundSprite->SetTransform(FinalTransform);

		XMFLOAT2 LivesTransform(-54, -47);
		XMFLOAT2 LivesScale(1, 1);
		Transform2D LivesFinalTransform(LivesTransform, 0.0f, LivesScale);

		TextBatch = make_shared<SpriteBatch>(mDeviceResources->GetD3DDeviceContext());
		GalagaSpriteFont = make_shared<SpriteFont>(mDeviceResources->GetD3DDevice(), L"Content\\Fonts\\Arial_14_Regular.spritefont");

		for (int i = 0; i < 3; i++)
		{
			LivesTransform.x += 6;
			LivesFinalTransform.SetPosition(LivesTransform);
			Lives[i] = std::make_shared<GalagaPort::Spaceship>();
			Lives[i]->SetTransform(LivesFinalTransform);
		}
		GalagaAudioEngine = std::make_unique <AudioEngine>();

		StartingNoise = std::make_unique<SoundEffect>(GalagaAudioEngine.get(), L"Content//Audio//GalagaStartScreen.wav");

		RedDeath = std::make_unique<SoundEffect>(GalagaAudioEngine.get(), L"Content//Audio//RedEnemyDeath.wav");
		YellowDeath = std::make_unique<SoundEffect>(GalagaAudioEngine.get(), L"Content//Audio//YellowEnemyDeath.wav");
		GreenDeath = std::make_unique<SoundEffect>(GalagaAudioEngine.get(), L"Content//Audio//GreenEnemyDeath.wav");

		WinScreen = std::make_unique<SoundEffect>(GalagaAudioEngine.get(), L"Content//Audio//WinScreen.wav");
		LossScreen = std::make_unique<SoundEffect>(GalagaAudioEngine.get(), L"Content//Audio//LossScreen.wav");

		PlayerShot = std::make_unique<SoundEffect>(GalagaAudioEngine.get(), L"Content//Audio//PlayerShot.wav");
		PlayerDeath = std::make_unique<SoundEffect>(GalagaAudioEngine.get(), L"Content//Audio//PlayerDeath.wav");
	}

	void GalagaManager::ResetGame()
	{
		SpaceshipSprite = std::make_shared<GalagaPort::Spaceship>();
		WaveController->SetPatrol();
		WaveController->CurrentWave = 0;
		GameStartTime = 0;
		GameStart = false;
		PlayerDead = false;
		PlayerWin = false;
		LastPlayerHit = 0;
		LastEnemyShot = 0;
		Score = 0;
		PlayedStartSound = false;

		for (int i = 0; i < 2; i++)
		{
			PlayerMissiles[i] = nullptr;
		}

		for (int i = 0; i < 4; i++)
		{
			EnemyMissiles[i] = nullptr;
		}
	}

	void GalagaManager::MoveSpaceship(float amount)
	{
		SpaceshipSprite->MoveSpaceship(amount);
	}

	void GalagaManager::PlayerShoot()
	{
		SpaceshipSprite->PlayerShoot(PlayerMissiles, PlayerShot);
	}

	void GalagaManager::ReleaseDeviceDependentResources()
	{
		mVertexShader = nullptr;
		mPixelShader = nullptr;
		mInputLayout = nullptr;
		mVertexBuffer = nullptr;
		mIndexBuffer = nullptr;
		mVSCBufferPerObject = nullptr;
		mTextureSampler = nullptr;

		redAlienSprites[0] = nullptr;
		redAlienSprites[1] = nullptr;

		yellowAlienSprites[0] = nullptr;
		yellowAlienSprites[1] = nullptr;

		greenAlienSprites[0] = nullptr;
		greenAlienSprites[1] = nullptr;

		TitleScreenSprite = nullptr;
		SpaceshipSprite = nullptr;
		SpaceBackgroundSprite = nullptr;
		ScoreText = nullptr;
		FinalText = nullptr;
	}

	void GalagaManager::Update(const StepTimer& timer)
	{
		if (timer.GetTotalSeconds() > LastUpdateTime + SpriteUpdateDelay)
		{
			LastUpdateTime = timer.GetTotalSeconds();
			enemyState = static_cast<size_t>((enemyState + 1) % 2);
		}
	}

	void GalagaManager::CheckForEnemyCollisions(double currentTime)
	{
		WaveController->CheckForCollision(currentTime, PlayerMissiles[0], Score, RedDeath, YellowDeath, GreenDeath);
		WaveController->CheckForCollision(currentTime, PlayerMissiles[1], Score, RedDeath, YellowDeath, GreenDeath);
	}

	void GalagaManager::CheckForPlayerCollisions(const StepTimer& timer)
	{
		SpaceshipSprite->CheckForCollision(EnemyMissiles, 0, PlayerHurtCooldown, LastPlayerHit, timer.GetTotalSeconds(), PlayerDeath);
		SpaceshipSprite->CheckForCollision(EnemyMissiles, 1, PlayerHurtCooldown, LastPlayerHit, timer.GetTotalSeconds(), PlayerDeath);
		SpaceshipSprite->CheckForCollision(EnemyMissiles, 2, PlayerHurtCooldown, LastPlayerHit, timer.GetTotalSeconds(), PlayerDeath);
		SpaceshipSprite->CheckForCollision(EnemyMissiles, 3, PlayerHurtCooldown, LastPlayerHit, timer.GetTotalSeconds(), PlayerDeath);
	}

	void GalagaManager::Render(const StepTimer& timer)
	{
		ID3D11DeviceContext* direct3DDeviceContext = mDeviceResources->GetD3DDeviceContext();
		direct3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		direct3DDeviceContext->IASetInputLayout(mInputLayout.get());

		const uint32_t stride = VertexPositionTexture::VertexSize();
		const uint32_t offset = 0;
		const auto vertexBuffers = mVertexBuffer.get();
		direct3DDeviceContext->IASetVertexBuffers(0, 1, &vertexBuffers, &stride, &offset);
		direct3DDeviceContext->IASetIndexBuffer(mIndexBuffer.get(), DXGI_FORMAT_R16_UINT, 0);

		direct3DDeviceContext->VSSetShader(mVertexShader.get(), nullptr, 0);
		direct3DDeviceContext->PSSetShader(mPixelShader.get(), nullptr, 0);

		const auto vsConstantBuffers = mVSCBufferPerObject.get();
		direct3DDeviceContext->VSSetConstantBuffers(0, 1, &vsConstantBuffers);

		const auto textureSamplers = mTextureSampler.get();
		direct3DDeviceContext->PSSetSamplers(0, 1, &textureSamplers);
		direct3DDeviceContext->OMSetBlendState(mAlphaBlending.get(), 0, 0xFFFFFFFF);

		if (WaveController != nullptr)
		{
			if (GameStart && !PlayerWin && !PlayerDead)
			{
				TextBatch->Begin();
				DrawBackground(*SpaceBackgroundSprite, SpaceBackground, direct3DDeviceContext);
				GameStartTime += timer.GetElapsedSeconds();
				WaveController->UpdateWaves(GameStartTime);
				DrawAliens(direct3DDeviceContext, timer.GetTotalSeconds());
				EnemyShotCheck();
				CheckForEnemyCollisions(timer.GetTotalSeconds());
				CheckForPlayerCollisions(timer);

				if (LastPlayerHit == 0 || LastPlayerHit + PlayerHurtCooldown < timer.GetTotalSeconds())
				{
 					DrawSprite(*SpaceshipSprite, SpaceshipBase, direct3DDeviceContext);
				}
				else
				{
					DrawSprite(*SpaceshipSprite, HurtSpaceshipBase, direct3DDeviceContext);
				}

				DrawPlayerMissiles(direct3DDeviceContext);
				DrawEnemyMissiles(direct3DDeviceContext);
				DrawLives(direct3DDeviceContext);

				ScoreText->DrawScore(TextBatch, GalagaSpriteFont, Score);
				TextBatch->End();
			}
			if (PlayerWin || Score == 4000)
			{
				TextBatch->Begin();
				DrawBackground(*SpaceBackgroundSprite, SpaceBackground, direct3DDeviceContext);
				if (!PlayerWin)
				{
					WinScreen->Play();
					PlayerWin = true;
				}
				std::string Message = "You Win!";
				FinalText->EndMessage(TextBatch, GalagaSpriteFont, Message);
				TextBatch->End();
			}
			else if (SpaceshipSprite->life < 0 || PlayerDead)
			{
				TextBatch->Begin();
				DrawBackground(*SpaceBackgroundSprite, SpaceBackground, direct3DDeviceContext);
				if (!PlayerDead)
				{
					LossScreen->Play();
					PlayerDead = true;
				}
				std::string Message = "You Lose!";
				FinalText->EndMessage(TextBatch, GalagaSpriteFont, Message);
				TextBatch->End();
			}
			else if(!PlayerWin && !PlayerDead)
			{
				if (!PlayedStartSound)
				{
					GalagaAudioEngine->Reset();
					StartingNoise->Play();
					PlayedStartSound = true;
				}

				TextBatch->Begin();
				DrawBackground(*TitleScreenSprite, TitleScreen, direct3DDeviceContext);
				TextBatch->End();
			}
		}
	}
	
	void GalagaManager::EnemyShotCheck()
	{
		if (EnemyShotCooldown <= (GameStartTime - LastEnemyShot) || LastEnemyShot == 0) //Checks if there are currently less than 4 missiles onscreen, allowing instantiation of a new one if so. Only allowed if enemyshotcooldown has been surpassed or met
		{
			int index = 4;
			if (EnemyMissiles[0] == nullptr)
			{
				index = 0;
			}
			else if (EnemyMissiles[1] == nullptr)
			{
				index = 1;
			}
			else if (EnemyMissiles[2] == nullptr)
			{
				index = 2;
			}
			else if (EnemyMissiles[3] == nullptr)
			{
				index = 3;
			}

			if (index < 4)
			{
				WaveController->ShootNextBullet(index, GameStartTime, EnemyMissiles, LastEnemyShot);
			}
		}
	}

	void GalagaManager::CreateDeviceDependentResources()
	{
		auto compiledVertexShader = Utility::LoadBinaryFile(L"Content\\Shaders\\SpriteRendererVS.cso");
		mVertexShader = nullptr;
		ThrowIfFailed(mDeviceResources->GetD3DDevice()->CreateVertexShader(compiledVertexShader.data(), compiledVertexShader.size(), nullptr, mVertexShader.put()), "ID3D11Device::CreatedVertexShader() failed.");
		mInputLayout = nullptr;
		ThrowIfFailed(mDeviceResources->GetD3DDevice()->CreateInputLayout(VertexPositionTexture::InputElements.data(), gsl::narrow_cast<uint32_t>(VertexPositionTexture::InputElements.size()), compiledVertexShader.data(), compiledVertexShader.size(), mInputLayout.put()), "ID3D11Device::CreateInputLayout() failed.");

		const CD3D11_BUFFER_DESC constantBufferDesc(sizeof(VSCBufferPerObject), D3D11_BIND_CONSTANT_BUFFER);
		ThrowIfFailed(mDeviceResources->GetD3DDevice()->CreateBuffer(&constantBufferDesc, nullptr, mVSCBufferPerObject.put()), "ID3D11Device::CreateBuffer() failed.");

		auto compiledPixelShader = Utility::LoadBinaryFile(L"Content\\Shaders\\SpriteRendererPS.cso");
		mPixelShader = nullptr;
		ThrowIfFailed(mDeviceResources->GetD3DDevice()->CreatePixelShader(compiledPixelShader.data(), compiledPixelShader.size(), nullptr, mPixelShader.put()), "ID3D11Device::CreatedPixelShader() failed.");

		const CD3D11_DEFAULT defaultDesc;
		const CD3D11_SAMPLER_DESC samplerStateDesc(defaultDesc);
		mTextureSampler = nullptr;
		ThrowIfFailed(mDeviceResources->GetD3DDevice()->CreateSamplerState(&samplerStateDesc, mTextureSampler.put()));

		CD3D11_BLEND_DESC blendStateDesc(defaultDesc);
		blendStateDesc.RenderTarget[0].BlendEnable = true;
		blendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		mAlphaBlending = nullptr;
		ThrowIfFailed(mDeviceResources->GetD3DDevice()->CreateBlendState(&blendStateDesc, mAlphaBlending.put()));

		ThrowIfFailed(DirectX::CreateWICTextureFromFile(mDeviceResources->GetD3DDevice(), L"Content\\Textures\\GalagaEnemyRed1.png", nullptr, redAlienSprites[0].put()));
		ThrowIfFailed(DirectX::CreateWICTextureFromFile(mDeviceResources->GetD3DDevice(), L"Content\\Textures\\GalagaEnemyRed2.png", nullptr, redAlienSprites[1].put()));

		ThrowIfFailed(DirectX::CreateWICTextureFromFile(mDeviceResources->GetD3DDevice(), L"Content\\Textures\\GalagaEnemyYellow1.png", nullptr, yellowAlienSprites[0].put()));
		ThrowIfFailed(DirectX::CreateWICTextureFromFile(mDeviceResources->GetD3DDevice(), L"Content\\Textures\\GalagaEnemyYellow2.png", nullptr, yellowAlienSprites[1].put()));

		ThrowIfFailed(DirectX::CreateWICTextureFromFile(mDeviceResources->GetD3DDevice(), L"Content\\Textures\\GalagaEnemyGreen1.png", nullptr, greenAlienSprites[0].put()));
		ThrowIfFailed(DirectX::CreateWICTextureFromFile(mDeviceResources->GetD3DDevice(), L"Content\\Textures\\GalagaEnemyGreen2.png", nullptr, greenAlienSprites[1].put()));

		ThrowIfFailed(DirectX::CreateWICTextureFromFile(mDeviceResources->GetD3DDevice(), L"Content\\Textures\\StartScreen.png", nullptr, TitleScreen.put()));
		ThrowIfFailed(DirectX::CreateWICTextureFromFile(mDeviceResources->GetD3DDevice(), L"Content\\Textures\\SpaceBackgroundLoopable.png", nullptr, SpaceBackground.put()));

		ThrowIfFailed(DirectX::CreateWICTextureFromFile(mDeviceResources->GetD3DDevice(), L"Content\\Textures\\GalagaShip.png", nullptr, SpaceshipBase.put()));
		ThrowIfFailed(DirectX::CreateWICTextureFromFile(mDeviceResources->GetD3DDevice(), L"Content\\Textures\\GalagaShipHurt.png", nullptr, HurtSpaceshipBase.put()));
		ThrowIfFailed(DirectX::CreateWICTextureFromFile(mDeviceResources->GetD3DDevice(), L"Content\\Textures\\PlayerProjectile.png", nullptr, PlayerMissileSprite.put()));

		ThrowIfFailed(DirectX::CreateWICTextureFromFile(mDeviceResources->GetD3DDevice(), L"Content\\Textures\\Explosion1.png", nullptr, ExplosionSprites[0].put()));
		ThrowIfFailed(DirectX::CreateWICTextureFromFile(mDeviceResources->GetD3DDevice(), L"Content\\Textures\\Explosion2.png", nullptr, ExplosionSprites[1].put()));
		ThrowIfFailed(DirectX::CreateWICTextureFromFile(mDeviceResources->GetD3DDevice(), L"Content\\Textures\\Explosion3.png", nullptr, ExplosionSprites[2].put()));
		ThrowIfFailed(DirectX::CreateWICTextureFromFile(mDeviceResources->GetD3DDevice(), L"Content\\Textures\\Explosion4.png", nullptr, ExplosionSprites[3].put()));
		ThrowIfFailed(DirectX::CreateWICTextureFromFile(mDeviceResources->GetD3DDevice(), L"Content\\Textures\\Explosion5.png", nullptr, ExplosionSprites[4].put()));
		ThrowIfFailed(DirectX::CreateWICTextureFromFile(mDeviceResources->GetD3DDevice(), L"Content\\Textures\\Explosion6.png", nullptr, ExplosionSprites[5].put()));

		InitializeVertices();
	}

	void GalagaManager::InitializeVertices()
	{
		const VertexPositionTexture vertices[] =
		{
			VertexPositionTexture(XMFLOAT4(-1.0f, -1.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f)),
			VertexPositionTexture(XMFLOAT4(-1.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 0.0f)),
			VertexPositionTexture(XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 0.0f)),
			VertexPositionTexture(XMFLOAT4(1.0f, -1.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 1.0f)),
		};
		mVertexBuffer = nullptr;
		VertexPositionTexture::CreateVertexBuffer(gsl::not_null<ID3D11Device*>(mDeviceResources->GetD3DDevice()), vertices, gsl::not_null<ID3D11Buffer**>(mVertexBuffer.put()));

		// Create and index buffer
		const uint16_t indices[] =
		{
			0, 1, 2,
			0, 2, 3
		};
		mIndexCount = gsl::narrow<uint32_t>(std::size(indices));
		D3D11_BUFFER_DESC indexBufferDesc{ 0 };
		indexBufferDesc.ByteWidth = sizeof(uint16_t) * mIndexCount;
		indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA indexSubResourceData{ 0 };
		indexSubResourceData.pSysMem = indices;
		mIndexBuffer = nullptr;
		ThrowIfFailed(mDeviceResources->GetD3DDevice()->CreateBuffer(&indexBufferDesc, &indexSubResourceData, mIndexBuffer.put()));
	}
	void GalagaManager::DrawBackground(DirectXGame::BasicSprite& sprite, winrt::com_ptr<ID3D11ShaderResourceView> spriteData, ID3D11DeviceContext* direct3DDeviceContext)
	{
		const auto psShaderResources = spriteData.get();
		direct3DDeviceContext->PSSetShaderResources(0, 1, &psShaderResources);
		direct3DDeviceContext = mDeviceResources->GetD3DDeviceContext();

		const XMMATRIX wvp = XMMatrixTranspose(sprite.Transform().WorldMatrix() * mCamera->ViewProjectionMatrix());
		XMStoreFloat4x4(&mVSCBufferPerObjectData.WorldViewProjection, wvp);
		XMMATRIX textureTransform = XMLoadFloat4x4(&sprite.TextureTransform());
		XMStoreFloat4x4(&mVSCBufferPerObjectData.TextureTransform, XMMatrixTranspose(textureTransform));
		direct3DDeviceContext->UpdateSubresource(mVSCBufferPerObject.get(), 0, nullptr, &mVSCBufferPerObjectData, 0, 0);
		direct3DDeviceContext->DrawIndexed(mIndexCount, 0, 0);
	}

	void GalagaManager::DrawSprite(DirectXGame::BasicSprite& sprite, winrt::com_ptr<ID3D11ShaderResourceView> spriteData, ID3D11DeviceContext* direct3DDeviceContext)
	{
		const auto psShaderResources = spriteData.get();
		direct3DDeviceContext->PSSetShaderResources(0, 1, &psShaderResources);
		direct3DDeviceContext = mDeviceResources->GetD3DDeviceContext();

		const XMMATRIX wvp = XMMatrixTranspose(sprite.Transform().WorldMatrix() * mCamera->ViewProjectionMatrix()) * XMMatrixScaling(2, 2, 2);
		XMStoreFloat4x4(&mVSCBufferPerObjectData.WorldViewProjection, wvp);
		XMMATRIX textureTransform = XMLoadFloat4x4(&sprite.TextureTransform());
		XMStoreFloat4x4(&mVSCBufferPerObjectData.TextureTransform, XMMatrixTranspose(textureTransform));
		direct3DDeviceContext->UpdateSubresource(mVSCBufferPerObject.get(), 0, nullptr, &mVSCBufferPerObjectData, 0, 0);
		direct3DDeviceContext->DrawIndexed(mIndexCount, 0, 0);
	}

	void GalagaManager::DrawLives(ID3D11DeviceContext* direct3DDeviceContext)
	{
		if (SpaceshipSprite->life > 0)
		{
			if (SpaceshipSprite->life > 1)
			{
				if (SpaceshipSprite->life > 2)
				{
					DrawSprite(*Lives[2], SpaceshipBase, direct3DDeviceContext);
				}
				DrawSprite(*Lives[1], SpaceshipBase, direct3DDeviceContext);
			}
			DrawSprite(*Lives[0], SpaceshipBase, direct3DDeviceContext);
		}
	}

	void GalagaManager::DrawAliens(ID3D11DeviceContext* direct3DDeviceContext, double CurrentTime)
	{
		auto& Sprites = WaveController->mSprites;
		for (int i = 0; i < WaveController->mSprites.size(); i++)
		{
			if (Sprites[i] != nullptr)
			{
				if (Sprites[i]->IsAlive)
				{
					if (Sprites[i]->Color == "Red")
					{
						DrawSprite(*Sprites[i], redAlienSprites[enemyState], direct3DDeviceContext);
					}
					else if (Sprites[i]->Color == "Yellow")
					{
						DrawSprite(*Sprites[i], yellowAlienSprites[enemyState], direct3DDeviceContext);
					}
					else if (Sprites[i]->Color == "Green")
					{
						DrawSprite(*Sprites[i], greenAlienSprites[enemyState], direct3DDeviceContext);
					}
				}
				else if (Sprites[i]->IsExploding)
				{
					if (CurrentTime > Sprites[i]->TimeOfExplosion + 2.5)
					{
						Sprites[i]->IsExploding = false;
					}
					DrawSprite(*Sprites[i], ExplosionSprites[static_cast<size_t>((CurrentTime - Sprites[i]->TimeOfExplosion)*2)], direct3DDeviceContext);
				}
			}
		}
	}

	void GalagaManager::DrawEnemyMissiles(ID3D11DeviceContext* direct3DDeviceContext)
	{
		for (int i = 0; i < 4; i++)
		{
			if (EnemyMissiles[i] != nullptr)
			{
				EnemyMissiles[i]->Fly();
				if (EnemyMissiles[i]->Position.y < -48)
				{
					EnemyMissiles[i] = nullptr;
				}
				else
				{
					DrawSprite(*EnemyMissiles[i], PlayerMissileSprite, direct3DDeviceContext);
				}
			}
		}
	}

	void GalagaManager::DrawPlayerMissiles(ID3D11DeviceContext* direct3DDeviceContext)
	{
		for (int i = 0; i < 2; i++)
		{
			if (PlayerMissiles[i] != nullptr && PlayerMissiles[i]->IsActive)
			{
				PlayerMissiles[i]->Fly();
				if (PlayerMissiles[i]->Position.y > 50)
				{
					PlayerMissiles[i]->IsActive = false;
					PlayerMissiles[i] = nullptr;
				}
				else
				{
					DrawSprite(*PlayerMissiles[i], PlayerMissileSprite, direct3DDeviceContext);
				}
			}
		}
	}
}