#pragma once
#include "CharacterBase.h"
#include "WeaponData.h"

class Player : public CharacterBase
{
public:
	Player();
	~Player();
	
	void Init() override;
	void Update(float _deltaTime) override;
	void Render(float _deltaTime, DirectX::SpriteBatch& _sprBatch) override;
	// Link object to owning mode
	//void SetParentMode(PlayMode& _playMode) { m_ptrPlayMode = &_playMode; }

	// std::vector <std::shared_ptr<ProjectileTEMP>> GetWeapons() const { return m_weaponsTEMP; }
	void SetupWeapons();
	std::vector<Weapon*> GetWeapons() const { return m_weapons; }
private:
	std::vector<Weapon*> m_weapons;

	//Sprite m_thrust;

	void GetPlayerInput(float _deltaTime);

	void LoadShipTexture(D3D& _d3d, const std::string& _txtrName) override;

	void CheckForCollision();

	void FireWeapon(const Weapon::weap_type& _weaponType);
};