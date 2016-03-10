//
// Game.h
//

#pragma once

#include "StepTimer.h"
#include "AnimatedTexture.h"
#include "ScrollingBackground.h"
// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
public:

    Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();
    void Render();

    // Rendering helpers
    void Clear();
    void Present();

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

private:

    void Update(DX::StepTimer const& timer);

    void CreateDevice();
    void CreateResources();

    void OnDeviceLost();

    // Device resources.
    HWND                                            m_window;
    int                                             m_outputWidth;
    int                                             m_outputHeight;

    D3D_FEATURE_LEVEL                               m_featureLevel;
    Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice1;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext1;

    Microsoft::WRL::ComPtr<IDXGISwapChain>          m_swapChain;
    Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain1;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;


    // Rendering loop timer.
    DX::StepTimer                                   m_timer;
	
	//pointer to keyboard interface
	std::unique_ptr<DirectX::Keyboard> m_keyboard;

	//world and world2 responsible for local coordinates of objects
	
	DirectX::SimpleMath::Matrix m_planetWorld;
	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_world3;
	DirectX::SimpleMath::Matrix m_plan2;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	//font
	DirectX::SimpleMath::Vector2 m_FontPos;
	std::unique_ptr<DirectX::SpriteFont> m_font;
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

	// Geometry stuff
	std::unique_ptr<DirectX::CommonStates> m_states;
	
	std::unique_ptr<DirectX::GeometricPrimitive> m_shape;
	std::unique_ptr<DirectX::GeometricPrimitive> m_cubeMap;
	std::unique_ptr<DirectX::GeometricPrimitive> m_planet;
	std::unique_ptr<DirectX::Model> m_boat;

	std::unique_ptr<DirectX::IEffectFactory> m_fxFactory;
	std::unique_ptr<DirectX::EnvironmentMapEffect> m_effect;

	float a,b;

	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture2;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_cMapTexture;


};