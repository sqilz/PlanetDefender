#include "pch.h"
#include "Planets.h"


Planets::Planets()
{
}


Planets::~Planets()
{
	m_starTex.Reset();
	m_planetTex.Reset();
	m_star.reset();
	m_orbPlanet.reset();
	OutputDebugStringW(L"Destructor in Planets");
}
void Planets::Draw(ID3D11DeviceContext* deviceContext, Matrix world, Matrix world2, Matrix view, Matrix proj)
{
	m_star->Draw(world, view, proj, Colors::White, m_starTex.Get());
	m_orbPlanet->Draw(world2, view, proj, Colors::White, m_planetTex.Get());
}
void Planets::CreateDevice(ID3D11Device * device, ID3D11DeviceContext* deviceContext)
{
	m_states = std::make_unique<CommonStates>(device);
	m_fxFactory = std::make_unique<EffectFactory>(device);

	//center planet
	DX::ThrowIfFailed(CreateWICTextureFromFile(device, L"SunTex.jpg", nullptr, m_starTex.ReleaseAndGetAddressOf()));
	m_star = GeometricPrimitive::CreateSphere(deviceContext);
	//orbiting planet
	DX::ThrowIfFailed(CreateWICTextureFromFile(device, L"earth.bmp", nullptr, m_planetTex.ReleaseAndGetAddressOf()));
	m_orbPlanet = GeometricPrimitive::CreateSphere(deviceContext);
}