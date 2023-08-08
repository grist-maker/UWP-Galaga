#include "pch.h"
#include "BasicSprite.h"

using namespace DX;
using namespace DirectX;

namespace DirectXGame
{
	BasicSprite::BasicSprite(std::string SpriteType, const Transform2D& transform,  const XMFLOAT4X4& textureTransform) :
		mTransform(transform), mTextureTransform(textureTransform), Color(SpriteType)
	{
	}

	const Transform2D& BasicSprite::Transform() const
	{
		return mTransform;
	}

	void BasicSprite::SetTransform(const Transform2D& transform)
	{
		mTransform = transform;
	}

	const XMFLOAT4X4& BasicSprite::TextureTransform() const
	{
		return mTextureTransform;
	}

	void BasicSprite::SetTextureTransform(const XMFLOAT4X4& transform)
	{
		mTextureTransform = transform;
	}
}