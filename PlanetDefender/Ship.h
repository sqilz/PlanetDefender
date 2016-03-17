#pragma once
#include "Enemy.h"
class Ship :
	public Models
{
public:
	Ship();
	~Ship();
	void Draw(ID3D11DeviceContext* deviceContext, Matrix world, Matrix view, Matrix proj);
	void CreateDevice(ID3D11Device * device);
private:

	std::unique_ptr<DirectX::Model> m_starship;
	int health;
	//TODO: change size of models from insde a class
	Matrix test;
};

