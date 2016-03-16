#pragma once
#include "Game.h"
class Bullet :
	public Game
{
public:
	Bullet();
	~Bullet();
	void Shoot();
	void Render();
private:
	
	std::unique_ptr<DirectX::GeometricPrimitive> m_projectiled;
	DirectX::SimpleMath::Matrix m_bullets;
	DirectX::SimpleMath::Matrix m_projs;
	DirectX::SimpleMath::Matrix m_views;
	
};

