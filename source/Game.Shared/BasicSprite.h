#pragma once
#include "Transform2D.h"
#include "MatrixHelper.h"

namespace DirectXGame
{
	class BasicSprite
	{
	public:
		BasicSprite(std::string SpriteType = "Red", const DX::Transform2D& transform = { {0, 0} }, const DirectX::XMFLOAT4X4& textureTransform = DX::MatrixHelper::Identity);
		const DX::Transform2D& Transform() const;
		void SetTransform(const DX::Transform2D& transform);

		const DirectX::XMFLOAT4X4& TextureTransform() const;
		void SetTextureTransform(const DirectX::XMFLOAT4X4& transform);

	private:
		DirectX::XMFLOAT4X4 mTextureTransform;
		DX::Transform2D mTransform;
		std::uint32_t mSpriteIndex;
		std::string Color;
	};
}