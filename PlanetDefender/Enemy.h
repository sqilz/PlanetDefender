//
// Enemy.h
//
// Creates a UFO if AlienShip[N] in Game.cpp Render() is null
//
#pragma once
#include "Models.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;
class Enemy : public Models
{
public:
	Enemy();
	~Enemy();
	 void Draw(ID3D11DeviceContext* deviceContext, Matrix world, Matrix view, Matrix proj);
	 bool ChangeColor(bool test);
	 void CreateDevice(ID3D11Device * device);

	 void SetWorldMatrix(Matrix world);
	 Matrix GetWorldMatrix();

	 void SetMatrixX(float x);
	 void SetMatrixZ(float z);
private:

	DirectX::SimpleMath::Matrix m_enemy;
	std::unique_ptr<DirectX::Model> alien;
	bool test;
	
};

