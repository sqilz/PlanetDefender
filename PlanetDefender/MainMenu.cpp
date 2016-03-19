#include "pch.h"
#include "MainMenu.h"
using namespace DirectX;

MainMenu::MainMenu()
{
	menuOn = true;
	newgamebtnHover = true;
	exitbtnHover = true;
	isPaused = true;
}

MainMenu::~MainMenu()
{
	m_background.Reset();
}

bool MainMenu::Update(DirectX::Keyboard* m_keyboard, DirectX::Mouse *m_mouse)
{
	// Booleans go into the Draw function or into Game.cpp as getters

	auto kb = m_keyboard->GetState();
	auto mouse = m_mouse->GetState();
	
	// showing/hiding menu
	if (kb.Escape)
	{
		menuOn = true;
		isPaused = true;
	}
	// New game / continue button colour change on hover
	if (mouse.x > m_newGame.left && mouse.x < m_newGame.right && mouse.y > m_newGame.top && mouse.y < m_newGame.bottom)
		newgamebtnHover = false;
	else
		newgamebtnHover = true;
	
	// Exit button colour change on hover
	// Booleans go into the Draw function
	if (mouse.x > m_exit.left && mouse.x < m_exit.right && mouse.y > m_exit.top && mouse.y < m_exit.bottom && menuOn == true)
		exitbtnHover = false;
	else
		exitbtnHover = true;
	
	// for menu navigation, specifying the clickable area where buttons are located
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
	return isPaused;
}

void MainMenu::Draw(DirectX::SpriteBatch* m_spriteBatch)
{
	m_spriteBatch->Begin();

	// background texture drawing
	m_spriteBatch->Draw(m_background.Get(), m_menuBackground);
	
	//new game/continue buttonm texture +  colour hover/no-hover
	if (newgamebtnHover)
		m_spriteBatch->Draw(m_btnNewGame.Get(), m_newGame);
	else
		m_spriteBatch->Draw(m_btnNewGame.Get(), m_newGame, Colors::Chartreuse);
	
	// exit button, texture + colour hover/no-hover
	if (exitbtnHover)
		m_spriteBatch->Draw(m_btnExit.Get(), m_exit);
	else
		m_spriteBatch->Draw(m_btnExit.Get(), m_exit, Colors::Chartreuse);

	m_spriteBatch->End();
}

void MainMenu::Textures(ID3D11Device * device)
{	
	// Loading button textures into ShaderResouceView
	//
	// menu background
	if (m_background.Get() == nullptr)
		DX::ThrowIfFailed(CreateWICTextureFromFile(device, L"menubackground.jpg", nullptr, m_background.ReleaseAndGetAddressOf()));
	// buttons
	if (continuebtn == true)
		DX::ThrowIfFailed(CreateWICTextureFromFile(device, L"continue.jpg", nullptr, m_btnNewGame.ReleaseAndGetAddressOf()));
	if (m_btnNewGame == nullptr)
		DX::ThrowIfFailed(CreateWICTextureFromFile(device, L"newGame.jpg", nullptr, m_btnNewGame.ReleaseAndGetAddressOf()));
	if (m_btnExit == nullptr)
		DX::ThrowIfFailed(CreateWICTextureFromFile(device, L"exit.jpg", nullptr, m_btnExit.ReleaseAndGetAddressOf()));
}

void MainMenu::CreateResources(float backBufferWidth,float backBufferHeight)
{
	// menu background position
	m_menuBackground.left = 0;
	m_menuBackground.top = 0;
	m_menuBackground.right = long(backBufferWidth);
	m_menuBackground.bottom = long(backBufferHeight);
	// New Game / continue button position
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
// getters
bool MainMenu::get_isPaused()
{
	return isPaused;
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