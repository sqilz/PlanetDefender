#include "pch.h"
#include "Ship.h"


Ship::Ship()
{
}


Ship::~Ship()
{
	m_starship.reset();
}

void Ship::Draw(ID3D11DeviceContext* deviceContext, Matrix world, Matrix view, Matrix proj)
{
	m_starship->Draw(deviceContext, *m_states, world, view, proj);
}

void Ship::CreateDevice(ID3D11Device * device)
{
	m_states = std::make_unique<CommonStates>(device);
	m_fxFactory = std::make_unique<EffectFactory>(device);

	m_starship = Model::CreateFromCMO(device, L"droidfighter.cmo", *m_fxFactory);

}