#pragma once
#include "Models.h"

//TODO: Use EnvironmentMapEffect to create a cubemap instead of Geometric Primitive
class Skybox :
	public Models
{
public:
	Skybox();
	~Skybox();
	void Draw(Matrix world);
	void CreateDevice(ID3D11Device * device, ID3D11DeviceContext* deviceContext);
	void CreateResources(Matrix view,Matrix proj);
private:
	std::unique_ptr<DirectX::GeometricPrimitive> m_cubeMap;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_SkyBoxTexture;
	std::unique_ptr<DirectX::BasicEffect> m_effect;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
};

