//
// Game.cpp
//
#include "pch.h"
#include "Game.h"
#include "Enemy.h"
#include "Ship.h"
#include "Planets.h"
#include "Skybox.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

std::unique_ptr<Enemy> AlienShip(new Enemy);
std::unique_ptr<Ship> Starship(new Ship);
std::unique_ptr<Planets> Planet(new Planets);
std::unique_ptr<Skybox> skybox(new Skybox);

Game::Game() :
    m_window(0),
	m_outputWidth(1270),
    m_outputHeight(860),
    m_featureLevel(D3D_FEATURE_LEVEL_11_1)
{
}
Game::~Game()
{
	if (m_audio)
	{
		m_audio->Suspend();
	}
	m_bgAudioLoop.reset();
	
		
}
// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
	m_window = window;
	m_outputWidth = std::max(width, 1);
	m_outputHeight = std::max(height, 1);

	CreateDevice();
	
	CreateResources();

	// TODO: Change the timer settings if you want something other than the default variable timestep mode.
	// e.g. for 60 FPS fixed timestep update logic , call:

	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60);

	AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG
	eflags = eflags | AudioEngine_Debug;
#endif
	m_audio = std::make_unique<AudioEngine>(eflags);
	m_retryAudio = false;

	m_bgAudio = std::make_unique<SoundEffect>(m_audio.get(), L"sandstorm.wav");
	m_bgAudioLoop = m_bgAudio->CreateInstance();
	m_bgAudioLoop->Play(true);
	explodeDelay = 2.f;

	m_keyboard = std::make_unique<Keyboard>();
	m_mouse = std::make_unique<Mouse>();
	m_mouse->SetWindow(window);
	m_planetWorld[1]._41 = -20.f;
	m_planetWorld[1]._43 = -20.f;

	menuOn = true;
	newgamebtnHover = true;
	exitbtnHover = true;
	speed = 0.6f;
	//m_bullet = Matrix::CreateRotationY(m_ship._42) * m_ship;

	m_ship._43 = 30.f; // spawn position on Z changed so ship doesnt spawn inside a planet
	m_bullet._41 = m_ship._41;
	m_bullet._42 = m_ship._42;
	m_bullet._43 = m_ship._43;
	
	std::random_device rd;
	m_random = std::make_unique<std::mt19937>(rd());
	
	for (int i = 0; i < 100; i++){

		std::uniform_real_distribution<float> dist(-30.f, 30.f);
		enemyPosX = dist(*m_random);
		enemyPosZ= dist(*m_random);

		m_enemy[i]._41 = enemyPosX;
		m_enemy[i]._43 = enemyPosZ;
		//m_enemy[i] = Matrix::CreateTranslation(Vector3(explodeDelay*i,0.f,explodeDelay*i));
	}
	
	m_planetPos[0] = Vector3(m_planetWorld[1]._41, 0.f, m_planetWorld[1]._43);
	
}

// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
       Update(m_timer);
    });
   Render();	
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
	elapsedTime;
	float time = float(timer.GetTotalSeconds());
	
	float newTime = time - elapsedTime;
	// KEYBOARD AND MOUSE INITIALISATION 
	auto kb = m_keyboard->GetState();
	auto mouse = m_mouse->GetState();
	
	m_shipPos = Vector3(m_ship._41, m_ship._42, m_ship._43);
	m_bulletPos = Vector3(m_bullet._41 + float(1), m_bullet._42, m_bullet._43);

	if (kb.F1)
		PostQuitMessage(0);

	// showing/hiding menu
	if (kb.Escape)
		menuOn = true;

	// New game/ continue button color change on hover
	if (mouse.x > m_newGame.left && mouse.x < m_newGame.right && mouse.y > m_newGame.top && mouse.y < m_newGame.bottom)
		newgamebtnHover = false;
	else
		newgamebtnHover = true;
	/***********************/

	// Exit button color change on hover
	if (mouse.x > m_exit.left && mouse.x < m_exit.right && mouse.y > m_exit.top && mouse.y < m_exit.bottom && menuOn == true)
		exitbtnHover = false;
	else
		exitbtnHover = true;
	/***********************/

	// specifying the clickable area where buttons are
	if (mouse.leftButton)
	{	
		// When new game/continue button is clicked start game
		if (mouse.x > m_newGame.left && mouse.x < m_newGame.right && mouse.y > m_newGame.top && mouse.y < m_newGame.bottom)
		{
			menuOn = false;
			continuebtn = true;	
		}

		// when exit button is clicked - exit
		if (mouse.x > m_exit.left && mouse.x < m_exit.right && mouse.y > m_exit.top && mouse.y < m_exit.bottom && menuOn == true)			
			PostQuitMessage(0);
	}
	/***********************/

	Menu(menuOn, continuebtn, newgamebtnHover, exitbtnHover);

	// Pausing game if menu is not hidden
	if (!isPaused)
	{
		if (kb.A)
			m_ship = Matrix::CreateTranslation(-Vector3::Forward * speed) * Matrix::CreateRotationY(.1f) * m_ship;
				
		if (kb.D)
			m_ship = Matrix::CreateTranslation(-Vector3::Forward * speed) * Matrix::CreateRotationY(-.1f) * m_ship;

		if (kb.W)
			m_ship = Matrix::CreateTranslation(-Vector3::Forward * speed) * Matrix::CreateRotationY(0.f) * m_ship;;
			
		if (kb.S)
			m_ship *= Matrix::CreateTranslation(Vector3(0.0f, .0f, 0.2f));
		
		// shooting
		if (kb.Space)
		{
			if (6 - timer.GetElapsedSeconds())
			{
				
				Shoot(true, false);
			}
			Shoot(false, true);
					
		}
		m_bullet = Matrix::CreateTranslation(-Vector3::Forward * 2) *Matrix::CreateRotationY(m_ship._42)  *m_bullet;
		m_bullet2 = Matrix::CreateTranslation(-Vector3::Forward ) *Matrix::CreateRotationY(m_ship._42)  *m_bullet2;
		
		
		// star rotation around Y axis
		m_planetWorld[0] *= Matrix::CreateRotationY(.001f);
	
		// planet orbiting
		m_planetWorld[1] *= Matrix::CreateRotationY(sinf(2.f*XM_PI / 360.f)) * Matrix::CreateTranslation(Vector3(.1f, .0f, .1f));
		
		// makes the background "space" texture rotate slowly
		m_skybox *= Matrix::CreateRotationY(.001f);
		m_skybox *= Matrix::CreateRotationX(.001f);
		m_skybox *= Matrix::CreateRotationZ(.001f);
		
		a = m_planetWorld[1]._41;
		b = m_planetWorld[1]._43;

		
	}
	// makes the camera look at the spaceship
	m_view = Matrix::CreateLookAt(Vector3(m_shipPos.x + 0.f, m_shipPos.y + 50.f, m_shipPos.z + 50.f), Vector3(m_ship._41, m_ship._42, m_ship._43), Vector3::Up);

	if (m_retryAudio)
	{
		m_retryAudio = false;
		if (m_audio->Reset())
		{
			// TODO: restart any looped sounds here
			if (m_bgAudioLoop)
				m_bgAudioLoop->Play(true);
		}
	}
	else if (!m_audio->Update())
	{
		if (m_audio->IsCriticalError())
		{
			m_retryAudio = true;
		}
	}
	for (int i = 0; i < 100; i++){
	//	m_enemy[i] = Matrix::CreateTranslation(m_planetPos[0]);
	}
}
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }
	Clear(); 

    // TODO: Add your rendering code here.
	skybox->Draw(m_skybox);
	
	Planet->Draw(m_d3dContext.Get(), m_planetWorld[0], m_planetWorld[1], m_view, m_proj);
	AlienShip->Draw(m_d3dContext.Get(), m_enemy[0], m_view, m_proj);
	Starship->Draw(m_d3dContext.Get(), m_ship, m_view, m_proj);

	
	m_projectile->Draw(m_bullet, m_view, m_proj, Colors::Red);
	m_projectile2->Draw(m_bullet2 , m_view, m_proj, Colors::Green);
	
	// Draws text
	std::wstring output = std::wstring(L" X: ")+ std::to_wstring(a) +std::wstring(L"\n Z: ") + std::to_wstring(b);
	m_spriteBatch->Begin();
	Vector2 origin = m_font->MeasureString(output.c_str()) / 2.f;
	m_font->DrawString(m_spriteBatch.get(), output.c_str(),	m_FontPos, Colors::White, 0.f, origin);
	m_spriteBatch->End();
	
	//for drawing menu
	if (menu)
	{
		m_spriteBatch->Begin();

		// background texture drawing
		m_spriteBatch->Draw(m_background.Get(), m_menuBackground);

		// new game/continue + color change
		if (newgamebtnHover)
		m_spriteBatch->Draw(m_btnNewGame.Get(), m_newGame);
		else
		m_spriteBatch->Draw(m_btnNewGame.Get(), m_newGame, Colors::Chartreuse);

		// exit button + color change
		if (exitbtnHover)
		m_spriteBatch->Draw(m_btnExit.Get(), m_exit);
		else
		m_spriteBatch->Draw(m_btnExit.Get(), m_exit, Colors::Chartreuse);

		m_spriteBatch->End();
	}
	Present();
}

bool Game::Menu(bool menuAndPause, bool contbtn, bool newgamebtn, bool exitbtn)
{
	// for pausing udpate / showing menu
	menu = menuAndPause;
	isPaused = menuAndPause;
	newgamebtnHover = newgamebtn;
	exitbtnHover = exitbtn;

	// main menu textures for bg and buttons
	continuebtn = contbtn;
	if (continuebtn == true)
		DX::ThrowIfFailed(CreateWICTextureFromFile(m_d3dDevice.Get(), L"continue.jpg", nullptr, m_btnNewGame.ReleaseAndGetAddressOf()));
	if (m_background.Get() == nullptr)
	DX::ThrowIfFailed(CreateWICTextureFromFile(m_d3dDevice.Get(), L"menubackground.jpg", nullptr, m_background.ReleaseAndGetAddressOf()));
	if (m_btnNewGame == nullptr)
	DX::ThrowIfFailed(CreateWICTextureFromFile(m_d3dDevice.Get(), L"newGame.jpg", nullptr, m_btnNewGame.ReleaseAndGetAddressOf()));
	if (m_btnExit == nullptr)
	DX::ThrowIfFailed(CreateWICTextureFromFile(m_d3dDevice.Get(), L"exit.jpg", nullptr, m_btnExit.ReleaseAndGetAddressOf()));
	
	return menu;
}
bool Game::Shoot(bool test,bool test2)
{
	shoot1 = test;
	shoot2 = test2;
	if (shoot1)
		m_bullet = Matrix::CreateRotationY(m_ship._42)* m_ship;
	if (shoot2)
		m_bullet2 = Matrix::CreateRotationY(m_ship._42)* m_ship;
		
		return draw;
}
// Helper method to clear the back buffers.
void Game::Clear()
{
    // Clear the views
    m_d3dContext->ClearRenderTargetView(m_renderTargetView.Get(), Colors::CornflowerBlue);
    m_d3dContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    m_d3dContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());

    // Set the viewport.
    CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(m_outputWidth), static_cast<float>(m_outputHeight));
    m_d3dContext->RSSetViewports(1, &viewport);
}

// Presents the back buffer contents to the screen.
void Game::Present()
{
    // The first argument instructs DXGI to block until VSync, putting the application
    // to sleep until the next VSync. This ensures we don't waste any cycles rendering
    // frames that will never be displayed to the screen.
    HRESULT hr = m_swapChain->Present(1, 0);

    // If the device was reset we must completely reinitialize the renderer.
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
    {
        OnDeviceLost();
    }
    else
    {
        DX::ThrowIfFailed(hr);
    }
}

// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
	m_audio->Suspend();
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
	m_audio->Resume();
	explodeDelay = 2.f;
}

void Game::OnWindowSizeChanged(int width, int height)
{
    m_outputWidth = std::max(width, 1);
    m_outputHeight = std::max(height, 1);

    CreateResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 1270;
    height = 860;
}

// These are the resources that depend on the device.
void Game::CreateDevice()
{
    UINT creationFlags = 0;

#ifdef _DEBUG
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    static const D3D_FEATURE_LEVEL featureLevels [] =
    {
        // TODO: Modify for supported Direct3D feature levels (see code below related to 11.1 fallback handling).
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };

    // Create the DX11 API device object, and get a corresponding context.
    HRESULT hr = D3D11CreateDevice(
        nullptr,                                // specify nullptr to use the default adapter
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        creationFlags,
        featureLevels,
        _countof(featureLevels),
        D3D11_SDK_VERSION,
        m_d3dDevice.ReleaseAndGetAddressOf(),   // returns the Direct3D device created
        &m_featureLevel,                        // returns feature level of device created
        m_d3dContext.ReleaseAndGetAddressOf()   // returns the device immediate context
        );

    if (hr == E_INVALIDARG)
    {
        // DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
        hr = D3D11CreateDevice(nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            creationFlags,
            &featureLevels[1],
            _countof(featureLevels) - 1,
            D3D11_SDK_VERSION,
            m_d3dDevice.ReleaseAndGetAddressOf(),
            &m_featureLevel,
            m_d3dContext.ReleaseAndGetAddressOf()
            );
    }

    DX::ThrowIfFailed(hr);

#ifndef NDEBUG
    ComPtr<ID3D11Debug> d3dDebug;
    if (SUCCEEDED(m_d3dDevice.As(&d3dDebug)))
    {
        ComPtr<ID3D11InfoQueue> d3dInfoQueue;
        if (SUCCEEDED(d3dDebug.As(&d3dInfoQueue)))
        {
#ifdef _DEBUG
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
#endif
            D3D11_MESSAGE_ID hide [] =
            {
                D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
                // TODO: Add more message IDs here as needed.
            };
            D3D11_INFO_QUEUE_FILTER filter;
            memset(&filter, 0, sizeof(filter));
            filter.DenyList.NumIDs = _countof(hide);
            filter.DenyList.pIDList = hide;
            d3dInfoQueue->AddStorageFilterEntries(&filter);
        }
    }
#endif

    // DirectX 11.1 if present
    if (SUCCEEDED(m_d3dDevice.As(&m_d3dDevice1)))
        (void)m_d3dContext.As(&m_d3dContext1);

    // TODO: Initialize device dependent objects here (independent of window 
	m_states = std::make_unique<CommonStates>(m_d3dDevice.Get());
	m_fxFactory = std::make_unique<EffectFactory>(m_d3dDevice.Get());
		
	m_projectile = GeometricPrimitive::CreateCube(m_d3dContext.Get(), 2.f);
	m_projectile2 = GeometricPrimitive::CreateCube(m_d3dContext.Get(), 2.f);
	
	m_planetWorld[0] = Matrix::Identity;
	m_planetWorld[1] = Matrix::Identity;
	m_skybox = Matrix::Identity;
	m_ship = Matrix::Identity;
	m_bullet = Matrix::Identity;
	m_bullet2 = Matrix::Identity;

	m_ship = Matrix::CreateScale(Vector3(1.2f, 1.2f, 1.2f));
	m_planetWorld[0] = Matrix::CreateScale(Vector3(15.f, 15.f, 15.f));
	m_planetWorld[1] = Matrix::CreateScale(Vector3(4.f, 4.f, 4.f));
	m_skybox = Matrix::CreateScale(Vector3(5.f, 5.f, 5.f));
	
	m_font = std::make_unique<SpriteFont>(m_d3dDevice.Get(), L"c.spritefont");
	m_spriteBatch = std::make_unique<SpriteBatch>(m_d3dContext.Get());

	// Creating models/texturing
	AlienShip->CreateDevice(m_d3dDevice.Get());
	Starship->CreateDevice(m_d3dDevice.Get());
	Planet->CreateDevice(m_d3dDevice.Get(), m_d3dContext.Get());
	skybox->CreateDevice(m_d3dDevice.Get(), m_d3dContext.Get());
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateResources()
{
    // Clear the previous window size specific context.
    ID3D11RenderTargetView* nullViews [] = { nullptr };
    m_d3dContext->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);
    m_renderTargetView.Reset();
    m_depthStencilView.Reset();
    m_d3dContext->Flush();

    UINT backBufferWidth = static_cast<UINT>(m_outputWidth);
    UINT backBufferHeight = static_cast<UINT>(m_outputHeight);
    DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
    DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
    UINT backBufferCount = 2;

    // If the swap chain already exists, resize it, otherwise create one.
    if (m_swapChain)
    {
        HRESULT hr = m_swapChain->ResizeBuffers(backBufferCount, backBufferWidth, backBufferHeight, backBufferFormat, 0);

        if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
        {
            // If the device was removed for any reason, a new device and swap chain will need to be created.
            OnDeviceLost();

            // Everything is set up now. Do not continue execution of this method. OnDeviceLost will reenter this method 
            // and correctly set up the new device.
            return;
        }
        else
        {
            DX::ThrowIfFailed(hr);
        }
    }
    else
    {
        // First, retrieve the underlying DXGI Device from the D3D Device
        ComPtr<IDXGIDevice1> dxgiDevice;
        DX::ThrowIfFailed(m_d3dDevice.As(&dxgiDevice));

        // Identify the physical adapter (GPU or card) this device is running on.
        ComPtr<IDXGIAdapter> dxgiAdapter;
        DX::ThrowIfFailed(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));

        // And obtain the factory object that created it.
        ComPtr<IDXGIFactory1> dxgiFactory;
        DX::ThrowIfFailed(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf())));

        ComPtr<IDXGIFactory2> dxgiFactory2;
        if (SUCCEEDED(dxgiFactory.As(&dxgiFactory2)))
        {
            // DirectX 11.1 or later

            // Create a descriptor for the swap chain.
            DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
            swapChainDesc.Width = backBufferWidth;
            swapChainDesc.Height = backBufferHeight;
            swapChainDesc.Format = backBufferFormat;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.BufferCount = backBufferCount;

            DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = { 0 };
            fsSwapChainDesc.Windowed = TRUE;

            // Create a SwapChain from a Win32 window.
            DX::ThrowIfFailed(dxgiFactory2->CreateSwapChainForHwnd(
                m_d3dDevice.Get(),
                m_window,
                &swapChainDesc,
                &fsSwapChainDesc,
                nullptr,
                m_swapChain1.ReleaseAndGetAddressOf()
                ));

            DX::ThrowIfFailed(m_swapChain1.As(&m_swapChain));
        }
        else
        {
            DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
            swapChainDesc.BufferCount = backBufferCount;
            swapChainDesc.BufferDesc.Width = backBufferWidth;
            swapChainDesc.BufferDesc.Height = backBufferHeight;
            swapChainDesc.BufferDesc.Format = backBufferFormat;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.OutputWindow = m_window;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.Windowed = TRUE;

            DX::ThrowIfFailed(dxgiFactory->CreateSwapChain(m_d3dDevice.Get(), &swapChainDesc, m_swapChain.ReleaseAndGetAddressOf()));
        }

        // This template does not support 'full-screen' mode and prevents the ALT+ENTER shortcut from working
        DX::ThrowIfFailed(dxgiFactory->MakeWindowAssociation(m_window, DXGI_MWA_NO_ALT_ENTER));
    }

    // Obtain the backbuffer for this window which will be the final 3D rendertarget.
    ComPtr<ID3D11Texture2D> backBuffer;
    DX::ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));

    // Create a view interface on the rendertarget to use on bind.
    DX::ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.ReleaseAndGetAddressOf()));

    // Allocate a 2-D surface as the depth/stencil buffer and
    // create a DepthStencil view on this surface to use on bind.
    CD3D11_TEXTURE2D_DESC depthStencilDesc(depthBufferFormat, backBufferWidth, backBufferHeight, 1, 1, D3D11_BIND_DEPTH_STENCIL);

    ComPtr<ID3D11Texture2D> depthStencil;
    DX::ThrowIfFailed(m_d3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, depthStencil.GetAddressOf()));

    CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
    DX::ThrowIfFailed(m_d3dDevice->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, m_depthStencilView.ReleaseAndGetAddressOf()));

    // TODO: Initialize windows-size dependent objects here.
	
	// FOV
	m_proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 2.5f, float(backBufferWidth) / float(backBufferHeight),0.1f,1000.f);
	skybox->CreateResources(m_view, m_proj);

	//font position
	m_FontPos.x = backBufferWidth / 5.f;
	m_FontPos.y = backBufferHeight / 6.f;

	// menu background position
	m_menuBackground.left = 0;
	m_menuBackground.top = 0;
	m_menuBackground.right = backBufferWidth;
	m_menuBackground.bottom = backBufferHeight;
	// New Game button position
	m_newGame.left = long(backBufferWidth / 2.5f);
	m_newGame.top = long(backBufferHeight / 4.1f);
	m_newGame.right = long(backBufferWidth / 1.7f);
	m_newGame.bottom = long(backBufferHeight / 2.8f);
	// Exit button position
	m_exit.left = long(backBufferWidth / 2.5f);
	m_exit.top = long(backBufferHeight / 2.75f);
	m_exit.right = long(backBufferWidth / 1.7f);
	m_exit.bottom = long(backBufferHeight / 2.095f);
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.
    m_depthStencilView.Reset();
    m_renderTargetView.Reset();
    m_swapChain1.Reset();
    m_swapChain.Reset();
    m_d3dContext1.Reset();
    m_d3dContext.Reset();
    m_d3dDevice1.Reset();
    m_d3dDevice.Reset();
	
	m_fxFactory.reset();
	m_states.reset();
	

	// textures

	
	m_background.Reset();
	// geometry & font
	
	m_font.reset();
	m_starship.reset();
	
	CreateDevice();

    CreateResources();
}