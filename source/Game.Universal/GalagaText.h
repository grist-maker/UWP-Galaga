#pragma once
#include "DrawableGameComponent.h"
#include <DirectXMath.h>

namespace GalagaPort
{
	class GalagaText final : public DX::DrawableGameComponent
	{
	public:
		GalagaText(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		GalagaText(const GalagaText&) = delete;
		GalagaText(GalagaText&&) = default;
		GalagaText& operator=(const GalagaText&) = delete;
		GalagaText& operator=(GalagaText&&) = default;
		~GalagaText() = default;

		DirectX::XMFLOAT2& TextPosition();
		void DrawScore(std::shared_ptr<DirectX::SpriteBatch> TextBatch, std::shared_ptr<DirectX::SpriteFont> GalagaSpriteFont, size_t Score);//std::shared_ptr<DirectX::SpriteBatch> TextBatch, std::shared_ptr<DirectX::SpriteFont> GalagaSpriteFont, size_t Score);
		void EndMessage(std::shared_ptr<DirectX::SpriteBatch> TextBatch, std::shared_ptr<DirectX::SpriteFont> GalagaSpriteFont, std::string& FinalMessage);
	private:
		DirectX::XMFLOAT2 mTextPosition{ 400, 20.0f };

		int mFrameCount{ 0 };
		int mFrameRate{ 0 };
		double mLastTotalSeconds;
	};
}