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
	alien.reset();
}

void Enemy::Draw(ID3D11DeviceContext* deviceContext,Matrix world, Matrix view, Matrix proj)
{
	alien->Draw(deviceContext, *m_states, world, view, proj);
}

void Enemy::CreateDevice(ID3D11Device * device)
{
	m_states = std::make_unique<CommonStates>(device);
	m_fxFactory = std::make_unique<EffectFactory>(device);

	alien = Model::CreateFromCMO(device, L"ufo.cmo", *m_fxFactory);
}

void Enemy::SetWorldMatrix(Matrix m)
{
	m_enemy = m;
}

Matrix Enemy::GetWorldMatrix()
{
	return m_enemy;
}
void Enemy::SetMatrixX(float x)
{
	m_enemy._41 = x;
}
void Enemy::SetMatrixZ(float z)
{
	m_enemy._43 = z;
}