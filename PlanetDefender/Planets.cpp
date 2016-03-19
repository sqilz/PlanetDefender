#include "pch.h"
#include "Planets.h"


Planets::Planets()
{
	m_planetWorld[0] = Matrix::Identity;
	m_planetWorld[1] = Matrix::Identity;
	m_planetWorld[1]._41 = -20.f;	// X Put this in initialize in Game.cpp
	m_planetWorld[1]._43 = -20.f;	// Y
	m_planetWorld[0] = Matrix::CreateScale(Vector3(15.f, 15.f, 15.f));
	m_planetWorld[1] = Matrix::CreateScale(Vector3(4.f, 4.f, 4.f));
}


Planets::~Planets()
{
	m_starTex.Reset();
	m_planetTex.Reset();
	m_star.reset();
	m_orbPlanet.reset();
	OutputDebugStringW(L"Destructor in Planets");
}
void Planets::PlanetMovements()
{
	// star rotation around Y axis
	m_planetWorld[0] *= Matrix::CreateRotationY(.001f);
	// planet orbiting
	m_planetWorld[1] *= Matrix::CreateRotationY(sinf(0.5f*XM_PI / 360.f)) * Matrix::CreateTranslation(Vector3(.1f, .0f, .1f));

}
void Planets::Draw(ID3D11DeviceContext* deviceContext, Matrix view, Matrix proj)
{
	m_star->Draw(m_planetWorld[0], view, proj, Colors::White, m_starTex.Get());
	m_orbPlanet->Draw(m_planetWorld[1], view, proj, Colors::White, m_planetTex.Get());
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