#pragma once
#include "Enemy.h"
class Planets :
	public Models
{
public:
	Planets();
	~Planets();
	void PlanetMovements();
	void Draw(ID3D11DeviceContext* deviceContext, Matrix view, Matrix proj);
	void CreateDevice(ID3D11Device * device, ID3D11DeviceContext* deviceContext);

private:
	DirectX::SimpleMath::Matrix m_planetWorld[9];

	std::unique_ptr<DirectX::GeometricPrimitive> m_orbPlanet;
	std::unique_ptr<DirectX::GeometricPrimitive> m_star;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_starTex;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_planetTex;
};

