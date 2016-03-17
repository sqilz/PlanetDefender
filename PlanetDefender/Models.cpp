#include "pch.h"
#include "Models.h"


Models::Models()
{
}


Models::~Models()
{
	m_states.reset(); 
	OutputDebugStringW(L"states removed\n");
	m_fxFactory.reset();
	OutputDebugStringW(L"factory removed\n");
}

void Models::Draw(ID3D11DeviceContext* deviceContext, Matrix world, Matrix view, Matrix proj)
{
}

void Models::CreateDevice(ID3D11Device * device)
{	
}