#include "pch.h"
#include "Planets.h"


Planets::Planets()
{
	for (int i = 0; i <= 8; i++)
	{
		m_planetWorld[i] = Matrix::Identity;
		m_planetWorld[i] = Matrix::CreateScale(Vector3(4.f, 4.f, 4.f));
	}
	
	for (int p = 1; p <= 8; p++)
	{
		m_planetWorld[p]._41 = -30.f;
		m_planetWorld[p]._43 = -30.f;
	}
	m_planetWorld[0] = Matrix::CreateScale(Vector3(15.f, 15.f, 15.f));

}


Planets::~Planets()
{
	m_starTex.Reset();
	m_planetTex.Reset();
	m_star.reset();
	//m_orbPlanet.reset();
	OutputDebugStringW(L"Destructor in Planets");
}
void Planets::PlanetMovements()
{
	// star rotation around Y axis
	m_planetWorld[0] *= Matrix::CreateRotationY(.001f);
	// planet orbiting and moving around their Y axis
	for (int or = 1; or <= 8; or++)
	{
		m_planetWorld[or] *= Matrix::CreateRotationY(.005f);
		m_planetWorld[or] *= Matrix::CreateRotationY(sinf(0.5f*XM_PI / 360.f * (or * 1.001f))) * Matrix::CreateTranslation(Vector3(.001f, .0f, .001f));
	}
	

}
void Planets::Draw(ID3D11DeviceContext* deviceContext, Matrix view, Matrix proj)
{
	m_star->Draw(m_planetWorld[0], view, proj, Colors::White, m_starTex.Get());

	m_orbPlanet[0]->Draw(m_planetWorld[1], view, proj, Colors::White, m_planetTex.Get());
	m_orbPlanet[1]->Draw(m_planetWorld[2], view, proj, Colors::Red, m_planetTex.Get());
	m_orbPlanet[2]->Draw(m_planetWorld[3], view, proj, Colors::Magenta, m_planetTex.Get());
	m_orbPlanet[3]->Draw(m_planetWorld[4], view, proj, Colors::Lavender, m_planetTex.Get());
	m_orbPlanet[4]->Draw(m_planetWorld[5], view, proj, Colors::Khaki, m_planetTex.Get());
	m_orbPlanet[5]->Draw(m_planetWorld[6], view, proj, Colors::Green, m_planetTex.Get());
	m_orbPlanet[6]->Draw(m_planetWorld[7], view, proj, Colors::Green, m_planetTex.Get());
	m_orbPlanet[7]->Draw(m_planetWorld[8], view, proj, Colors::Green, m_planetTex.Get());
	m_orbPlanet[8]->Draw(m_planetWorld[9], view, proj, Colors::Green, m_planetTex.Get());
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
	m_orbPlanet[0] = GeometricPrimitive::CreateSphere(deviceContext);
	m_orbPlanet[1] = GeometricPrimitive::CreateSphere(deviceContext);
	m_orbPlanet[2] = GeometricPrimitive::CreateSphere(deviceContext);
	m_orbPlanet[3] = GeometricPrimitive::CreateSphere(deviceContext);
	m_orbPlanet[4] = GeometricPrimitive::CreateSphere(deviceContext);
	m_orbPlanet[5] = GeometricPrimitive::CreateSphere(deviceContext);
	m_orbPlanet[6] = GeometricPrimitive::CreateSphere(deviceContext);
	m_orbPlanet[7] = GeometricPrimitive::CreateSphere(deviceContext);
	m_orbPlanet[8] = GeometricPrimitive::CreateSphere(deviceContext);

}
Matrix Planets::GetPlanetsMatrix(int i)
{
	return m_planetWorld[i];
}