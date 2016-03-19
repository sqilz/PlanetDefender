#include "pch.h"
#include "Skybox.h"


Skybox::Skybox()
{
}


Skybox::~Skybox()
{
	m_inputLayout.Reset();
	m_cubeMap.reset();
	m_SkyBoxTexture.Reset();
	m_effect.reset();
}

void Skybox::Draw(Matrix world)
{
	m_effect->SetWorld(world);
	m_cubeMap->Draw(m_effect.get(), m_inputLayout.Get());
}
void Skybox::CreateDevice(ID3D11Device * device, ID3D11DeviceContext* deviceContext)
{
	// skybox light fix - when loading, default lights were applied to the texture making the texture really dark
	m_effect = std::make_unique<BasicEffect>(device);
	m_effect->SetTextureEnabled(true);
	m_effect->SetPerPixelLighting(true);
	m_effect->SetLightingEnabled(true);
	m_effect->SetLightEnabled(0, true);
	m_effect->SetLightDiffuseColor(0, Colors::Azure);
	m_effect->SetLightDirection(0, -Vector3::UnitZ);
	m_effect->SetFogEnabled(true);
	m_effect->SetFogStart(6);
	m_effect->SetFogEnd(1200);
	m_effect->SetFogColor(Colors::Black);

	m_cubeMap = GeometricPrimitive::CreateSphere(deviceContext, 300.f, 16, false, true);
	m_cubeMap->CreateInputLayout(m_effect.get(), m_inputLayout.ReleaseAndGetAddressOf());

	DX::ThrowIfFailed(CreateWICTextureFromFile(device, L"spaceTexture.jpg", nullptr, m_SkyBoxTexture.ReleaseAndGetAddressOf()));
	m_effect->SetTexture(m_SkyBoxTexture.Get());
}

void Skybox::CreateResources(Matrix view, Matrix proj)
{
	// sets the view and projection matrix for effects
	m_effect->SetView(view);
	m_effect->SetProjection(proj);
}