//
// Models.h
//
// Class Created for other classes that use models or geometry to inherit from
//
#pragma once
using namespace DirectX;
using namespace DirectX::SimpleMath;
class Models
{
public:
	Models();
	~Models();
	virtual void Draw(ID3D11DeviceContext* deviceContext, Matrix world, Matrix view, Matrix proj);
	virtual void CreateDevice(ID3D11Device * device);

protected:

	std::unique_ptr<DirectX::CommonStates> m_states;
	std::unique_ptr<DirectX::IEffectFactory> m_fxFactory;
};

