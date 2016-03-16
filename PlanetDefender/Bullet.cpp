#include "pch.h"
#include "Bullet.h"


Bullet::Bullet()
{
}


Bullet::~Bullet()
{
	m_projectile.reset();
}
void Bullet::Shoot()
{
	
}
void Bullet::Render()
{ 
	
	///m_projectiled->Draw(m_bullets, m_views, m_projs, DirectX::Colors::Red);
	m_projectiled = DirectX::GeometricPrimitive::CreateCube(Game::m_d3dContext.Get(), 20.f);
}
