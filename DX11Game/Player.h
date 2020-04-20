#pragma once
#include "GameObject.h"
#include "HealthHandler.h"

class PlayMode;

class Player : public GameObject
{
public:
	Player(float _maxHealth = 0.f, float _curHealth = 0.f);
	void Update(float _deltaTime) override;
	void Render(float _deltaTime, DirectX::SpriteBatch& _sprBatch) override;
	// Link object to owning mode
	void SetParentMode(PlayMode& _playMode) { m_ptrPlayMode = &_playMode; };

	HealthHandler& GetHealthHandler();
private:
	PlayMode* m_ptrPlayMode = nullptr;		// Mode owner of object

	Sprite m_thrust;
	std::vector<TextureCache::Data::Sprite> m_thrustFrames;

	HealthHandler m_healthHandler;

	DirectX::SimpleMath::Vector2 m_moveSpeed{ 250.f, 250.f };
	void PlayerInput(float _deltaTime);

	void LoadShipTexture(D3D& _d3d);
	void LoadThrustTexture(D3D& _d3d);
};