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
	void OnNewAudioDevice() { m_retryAudio = true; }
    // Properties
    void GetDefaultSize( int& width, int& height ) const;

	//Main Menu
	bool Menu(bool pause, bool buttonTextureChanger, bool newbtnhover, bool exitbtnhover);
	bool Shoot(bool shoot,bool shoot2);
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
	
	//pointer to keyboard/mouse interface
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::Mouse> m_mouse;

	DirectX::SimpleMath::Matrix m_planetWorld[2];
	DirectX::SimpleMath::Matrix m_ship;
	DirectX::SimpleMath::Matrix m_bullet;
	DirectX::SimpleMath::Matrix m_skybox;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;
	DirectX::SimpleMath::Matrix m_enemy[200];

	DirectX::SimpleMath::Vector3 m_planetPos[9];

	//font
	DirectX::SimpleMath::Vector2 m_FontPos;
	std::unique_ptr<DirectX::SpriteFont> m_font;
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	
	bool shoot1,shoot2;
	bool draw;
	DirectX::SimpleMath::Vector3 m_shipPos, m_bulletPos;
	
	
	int score;
	char HighScore[2];
	float speed, acceleration;
	// Menu
	RECT m_menuBackground, m_newGame, m_exit;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_background;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_btnNewGame;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_btnExit;
	// Pausing game 
	bool isPaused,menu;
	bool menuOn;
	bool continuebtn;
	bool newgamebtnHover, exitbtnHover;
	
	std::unique_ptr<DirectX::AudioEngine> m_audio;
	bool m_retryAudio;
	float explodeDelay;
	std::unique_ptr<DirectX::SoundEffect> m_bgAudio;
	std::unique_ptr<DirectX::SoundEffectInstance> m_bgAudioLoop;

	std::unique_ptr<std::mt19937> m_random;
	float enemyPosX,enemyPosZ;
	std::vector<float> positionRand = std::vector<float>(100);
};