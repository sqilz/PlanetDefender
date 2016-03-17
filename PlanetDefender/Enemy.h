//
// Enemy.h
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
	 void CreateDevice(ID3D11Device * device);
private:

	std::unique_ptr<DirectX::Model> alien[20];
};

