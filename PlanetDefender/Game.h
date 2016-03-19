//
// Game.h
//

#pragma once

#include "StepTimer.h"


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
public:

    Game();
	~Game();
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

protected:

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
	
	// pointer to keyboard/mouse interface
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::Mouse> m_mouse;

	DirectX::SimpleMath::Matrix m_view; // view matrix
	DirectX::SimpleMath::Matrix m_proj; // projection matrix
	DirectX::SimpleMath::Matrix m_planetWorld[9];
	DirectX::SimpleMath::Matrix m_ship;
	DirectX::SimpleMath::Matrix m_bullet;
	DirectX::SimpleMath::Matrix m_skybox;
	DirectX::SimpleMath::Matrix m_enemy[200];

	DirectX::SimpleMath::Vector3 m_planetPos[9];

	// font
	DirectX::SimpleMath::Vector2 m_FontPos;
	std::unique_ptr<DirectX::SpriteFont> m_font;
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	
	DirectX::SimpleMath::Vector3 m_shipPos, m_bulletPos;
		
	int score;
	float speed, acceleration;
	
	// for random UFO positioning
	std::unique_ptr<std::mt19937> m_random;
	float enemyPosX,enemyPosZ;
	std::vector<float> positionRand = std::vector<float>(100);
};