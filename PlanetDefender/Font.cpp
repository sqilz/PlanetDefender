#include "pch.h"
#include "Font.h"


Font::Font()
{
}

Font::~Font()
{
}

void Font::Draw(float a, float b)
{
	std::wstring output = std::wstring(L" X: ") + std::to_wstring(a) + std::wstring(L"\n Z: ") + std::to_wstring(b);
	m_spriteBatch->Begin();
	Vector2 origin = m_font->MeasureString(output.c_str()) / 2.f;
	m_font->DrawString(m_spriteBatch.get(), output.c_str(), m_FontPos, Colors::White, 0.f, origin);
	m_spriteBatch->End();
}
void Font::CreateDevice(ID3D11Device * device,ID3D11DeviceContext * context)
{
	m_states = std::make_unique<CommonStates>(device);
	m_fxFactory = std::make_unique<EffectFactory>(device);

	m_font = std::make_unique<SpriteFont>(device, L"c.spritefont");
	m_spriteBatch = std::make_unique<SpriteBatch>(context);

}
void Font::CreateResources(float backBufferWidth,float backBufferHeight)
{
	//font position
	m_FontPos.x = backBufferWidth / 5.f;
	m_FontPos.y = backBufferHeight / 6.f;
}
