#pragma once
#include "Models.h"
class Font :
	public Models
{
public:
	Font();
	~Font();
	void Draw(float a, float b);
	void CreateDevice(ID3D11Device * device, ID3D11DeviceContext * context);
	void CreateResources(float backBufferWidth, float backBufferHeight);
private:
	DirectX::SimpleMath::Vector2 m_FontPos;
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	std::unique_ptr<DirectX::SpriteFont> m_font;

	


};

