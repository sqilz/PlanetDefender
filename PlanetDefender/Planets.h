#pragma once
#include "Enemy.h"
class Planets :
	public Models
{
public:
	Planets();
	~Planets();

	void Draw(ID3D11DeviceContext* deviceContext, Matrix world, Matrix world2, Matrix view, Matrix proj);
	void CreateDevice(ID3D11Device * device, ID3D11DeviceContext* deviceContext);

private:
	std::unique_ptr<DirectX::GeometricPrimitive> m_orbPlanet;
	std::unique_ptr<DirectX::GeometricPrimitive> m_star;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_starTex;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_planetTex;
};

