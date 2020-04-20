#include "MainGame.h"
#include "D3DUtil.h"
#include "CommonStates.h"
#include "WindowUtil.h"

// Static member variable instances
Input MainGame::mouseKeyboardInput;
GamePadInput MainGame::gamePad;


MainGame::MainGame(D3D& _d3d) 
	: m_d3d(_d3d), m_ptrSprBatch(nullptr) {
	// Set up main window for KB+M inputs
	mouseKeyboardInput.Init(WindowUtil::Get().GetMainWindow(), MOUSE_VISIBLE, MOUSE_CONFINED);
	gamePad.Init();
	m_ptrSprBatch = new DirectX::SpriteBatch(&m_d3d.GetDeviceCtx());

	// Load up fonts to be used in game
	m_menuManager.LoadFont(L"fonts/comicSansMS.spritefont", "comicsans", 12, APPEND_PATH);
	m_menuManager.LoadFont(L"fonts/bauhaus93Regular.spritefont", "bauhaus", 12, APPEND_PATH);
	m_menuManager.LoadFont(L"fonts/algerian.spritefont", "algerian", 12, APPEND_PATH);

	m_modeManager.AddMode(new PlayMode());
	m_modeManager.ChangeMode(PlayMode::MODE_NAME);
}

void MainGame::Update(float _deltaTime) {
	gamePad.Update();
	gamePad.IsEnabled(0);

	m_modeManager.Update(_deltaTime);
}

void MainGame::Render(float _deltaTime) {
	m_d3d.BeginRender(Colours::Black);

	DirectX::CommonStates dxState(&m_d3d.GetDevice());
	m_ptrSprBatch->Begin(DirectX::SpriteSortMode_Deferred, dxState.NonPremultiplied(), &m_d3d.GetWrapSampler());

	m_modeManager.Render(_deltaTime, *m_ptrSprBatch);
	m_menuManager.Render(_deltaTime, *m_ptrSprBatch, m_d3d.GetTextureCache(), mouseKeyboardInput);

	m_ptrSprBatch->End();

	m_d3d.EndRender();
	mouseKeyboardInput.PostProcess();
}

void MainGame::Release() {
	m_modeManager.Release();
	delete m_ptrSprBatch;
	m_ptrSprBatch = nullptr;
}