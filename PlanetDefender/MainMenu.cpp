#include "pch.h"
#include "MainMenu.h"
using namespace DirectX;

MainMenu::MainMenu()
{
	menuOn = true;
	newgamebtnHover = true;
	exitbtnHover = true;
}

MainMenu::~MainMenu()
{
	m_background.Reset();
}

void MainMenu::MouseInit(HWND window)
{
	m_keyboard = std::make_unique<Keyboard>();
	m_mouse = std::make_unique<Mouse>();
	m_mouse->SetWindow(window);
}
void MainMenu::Update()
{/*
	auto kb = m_keyboard->GetState();
	auto mouse = m_mouse->GetState();
	
	// showing/hiding menu
	if (kb.Escape)
		menuOn = true;

	// New game/ continue button color change on hover
	if (mouse.x > m_newGame.left && mouse.x < m_newGame.right && mouse.y > m_newGame.top && mouse.y < m_newGame.bottom)
		newgamebtnHover = false;
	else
		newgamebtnHover = true;


	// Exit button color change on hover
	if (mouse.x > m_exit.left && mouse.x < m_exit.right && mouse.y > m_exit.top && mouse.y < m_exit.bottom && menuOn == true)
		exitbtnHover = false;
	else
		exitbtnHover = true;
	
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
	}*/
}

void MainMenu::Draw()
{
	m_spriteBatchs->Begin();
	// background texture drawing
	m_spriteBatchs->Draw(m_background.Get(), m_menuBackground);
	// new game/continue + color change
	if (newgamebtnHover)
		m_spriteBatchs->Draw(m_btnNewGame.Get(), m_newGame);
	else
		m_spriteBatchs->Draw(m_btnNewGame.Get(), m_newGame, Colors::Chartreuse);

	// exit button + color change
	if (exitbtnHover)
		m_spriteBatchs->Draw(m_btnExit.Get(), m_exit);
	else
		m_spriteBatchs->Draw(m_btnExit.Get(), m_exit, Colors::Chartreuse);

	m_spriteBatchs->End();
}

bool MainMenu::Textures(ID3D11Device * device, bool menuAndPause, bool contbtn, bool newgamebtn, bool exitbtn)
{
	// for pausing udpate / showing menu
	menu = menuAndPause;
	isPaused = menuAndPause;
	newgamebtnHover = newgamebtn;
	exitbtnHover = exitbtn;

	// main menu textures for bg and buttons
	continuebtn = contbtn;
	if (continuebtn == true)
		DX::ThrowIfFailed(CreateWICTextureFromFile(device, L"continue.jpg", nullptr, m_btnNewGame.ReleaseAndGetAddressOf()));
	if (m_background.Get() == nullptr)
		DX::ThrowIfFailed(CreateWICTextureFromFile(device, L"menubackground.jpg", nullptr, m_background.ReleaseAndGetAddressOf()));
	if (m_btnNewGame == nullptr)
		DX::ThrowIfFailed(CreateWICTextureFromFile(device, L"newGame.jpg", nullptr, m_btnNewGame.ReleaseAndGetAddressOf()));
	if (m_btnExit == nullptr)
		DX::ThrowIfFailed(CreateWICTextureFromFile(device, L"exit.jpg", nullptr, m_btnExit.ReleaseAndGetAddressOf()));

	return menu;
}

void MainMenu::CreateResources(float backBufferWidth,float backBufferHeight)
{
	// menu background position
	m_menuBackground.left = 0;
	m_menuBackground.top = 0;
	m_menuBackground.right = long(backBufferWidth);
	m_menuBackground.bottom = long(backBufferHeight);
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

bool MainMenu::get_isPaused()
{
	return isPaused;
}
bool MainMenu::get_menu()
{
	return menu;
}
bool MainMenu::get_menuOn()
{
	return menuOn;
}
bool MainMenu::get_continuebtn()
{
	return continuebtn;
}
bool MainMenu::get_newgamebtnHover()
{
	return newgamebtnHover;
}
bool MainMenu::get_exitbtnHover()
{
	return exitbtnHover;
}