#pragma once
#include "Singleton.h"
#include "MenuManager.h"
#include "GameClock.h"

class MainGame;
class PlayMode;

class PlayerUI : public Singleton<PlayerUI>
{
public:
	// Structs to keep collections of UI components
	// together and organised for easier referencing

	struct HealthBar {
		HealthBar();
		void Update(float _deltaTime);

		MenuManager& menuMgr;		// MenuManager reference from PlayerUI

		MenuImage* healthBarBG;		// Health bar background
		MenuImage* healthBarFG;		// Health bar foreground
		MenuText* healthBarDisplay;	// Health bar health remaining display
	};

	struct InGameClock {
		InGameClock();
		void Update(float _deltaTime);

		MenuManager& menuMgr;

		GameClock clock;
		MenuText* clockDisplay;
	};

	// Used to display on-screen FPS
	struct FPSDisplay {
		FPSDisplay();
		void Update(float _deltaTime);

		MenuManager& menuMgr;

		MenuText* frameCountDisplay;
		float fpsUpdateDelay = 0.f;
		float delayRemaining = 0.f;
	};

	PlayerUI(PlayMode& _playMode);
	void Update(float _deltaTime);
	//void Render(float _deltaTime, DirectX::SpriteBatch& _sprBatch);
	~PlayerUI();
private:
	MenuManager& m_menuManager;	// Holds the menu manager reference
	PlayMode& m_playMode;		// Holds the playMode reference
	MenuNode* m_rootUINode;		// Holds root menu node for player UI

	D3D& m_d3d;					// Holds reference to MainGames d3d
	FPSDisplay* m_fpsDisplay;	// On-screen Frames per second
	HealthBar* m_healthBar;		// Players health bar
};
