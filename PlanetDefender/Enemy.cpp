//
// Enemy.cpp
//

#include "pch.h"
#include "Enemy.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
Enemy::Enemy()
{
}


Enemy::~Enemy()
{	
	
}

void Enemy::Draw(ID3D11DeviceContext* deviceContext,Matrix world, Matrix view, Matrix proj)
{
	alien[0]->Draw(deviceContext, *m_states, world, view, proj);
}

void Enemy::CreateDevice(ID3D11Device * device)
{
	m_states = std::make_unique<CommonStates>(device);
	m_fxFactory = std::make_unique<EffectFactory>(device);

	alien[0] = Model::CreateFromCMO(device, L"ufo.cmo", *m_fxFactory);
	
}