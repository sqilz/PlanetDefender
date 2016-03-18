#include "pch.h"
#include "Shooting.h"


Shooting::Shooting()
{
	

}


Shooting::~Shooting()
{
	//m_projectile.reset();
	OutputDebugStringW(L"projectile Deleted \n");
}


void Shooting::Draw(Matrix world, Matrix view, Matrix proj)
{
	m_projectile->Draw(world, view, proj, Colors::Green);
}
void Shooting::CreateDevice(ID3D11DeviceContext* deviceContext)
{
	m_projectile = GeometricPrimitive::CreateCube(deviceContext, 0.5f);
}