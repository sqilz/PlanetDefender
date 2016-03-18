#pragma once
#include "Models.h"
class Shooting :
	public Models
{
public:
	Shooting();
	~Shooting();
	void Draw(Matrix world, Matrix view, Matrix proj);
	void CreateDevice(ID3D11DeviceContext* deviceContext);
private:
	std::unique_ptr<DirectX::GeometricPrimitive> m_projectile;
	Matrix m_world;
	
};

