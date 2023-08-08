#include "pch.h"
#include "GalagaText.h"
#include "StepTimer.h"

using namespace std;
using namespace std::literals;
using namespace DirectX;
using namespace DX;

namespace GalagaPort
{
	GalagaText::GalagaText(const shared_ptr<DX::DeviceResources>& deviceResources) :
		DrawableGameComponent(deviceResources)
	{
	}

	XMFLOAT2& GalagaText::TextPosition()
	{
		return mTextPosition;
	}
	void GalagaText::DrawScore(std::shared_ptr<SpriteBatch> TextBatch, std::shared_ptr<SpriteFont> GalagaSpriteFont, size_t Score)
	{
		wostringstream fpsLabel;
		fpsLabel << setprecision(4) << L"SScore: " << Score;
		DirectX::XMFLOAT2 Position{0.0f, 0.0f};
		GalagaSpriteFont->DrawString(TextBatch.get(), fpsLabel.str().c_str(), mTextPosition, Colors::White, 0.0F, Position, 1);
	}

	void GalagaText::EndMessage(std::shared_ptr<SpriteBatch> TextBatch, std::shared_ptr<SpriteFont> GalagaSpriteFont, std::string& FinalMessage)
	{
		wostringstream fpsLabel;
		fpsLabel << setprecision(4) << FinalMessage.c_str();
		mTextPosition = { 0, 0 };
		DirectX::FXMVECTOR Scale{0.1, 0.1, 0.1};
		DirectX::XMFLOAT2 Position{-10.0f, -10.0f};
		GalagaSpriteFont->DrawString(TextBatch.get(), fpsLabel.str().c_str(), mTextPosition, Colors::White, 0.0F, Position, 10);
	}
}