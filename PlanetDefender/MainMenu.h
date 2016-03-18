#pragma once
using namespace DirectX;
class MainMenu
{
public:
	MainMenu();
	~MainMenu();
	void MouseInit(HWND window);
	void Update();
	void Draw();
	bool Textures(ID3D11Device * device, bool menuAndPause, bool contbtn, bool newgamebtn, bool exitbtn);
	void CreateResources(float bufferwidth, float bufferheight);

	bool get_isPaused();
	bool get_menu();
	bool get_menuOn();
	bool get_continuebtn();
	bool get_newgamebtnHover();
	bool get_exitbtnHover();


private:
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::Mouse> m_mouse;

	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatchs;

	RECT m_menuBackground, m_newGame, m_exit;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_background;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_btnNewGame;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_btnExit;

	// for game pausing
	bool isPaused, menu, menuOn, continuebtn, newgamebtnHover, exitbtnHover;

};

