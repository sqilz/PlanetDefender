#pragma once
using namespace DirectX;
class MainMenu
{
public:
	MainMenu();
	~MainMenu();
	
	// functions
	bool Update(DirectX::Keyboard* m_keyboard, DirectX::Mouse *m_mouse);
	void Draw(DirectX::SpriteBatch *m_spriteBatch);
	void Textures(ID3D11Device * device);
	void CreateResources(float bufferwidth, float bufferheight);

	// getters
	bool get_isPaused();
	bool get_menuOn();
	bool get_continuebtn();
	bool get_newgamebtnHover();
	bool get_exitbtnHover();


private:
	// position/size of menu items
	RECT m_menuBackground, m_newGame, m_exit;

	// for holding textures
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_background;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_btnNewGame;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_btnExit;

	// for game pausing
	bool isPaused, menuOn, continuebtn, newgamebtnHover, exitbtnHover;

};

