#include "ModeManager.h"
#include "D3DUtil.h"

ModeManager::~ModeManager() {
	Release();
}

void ModeManager::ChangeMode(const std::string & _newMode) {
	int idx = 0;
	// Make sure there are game modes in container
	assert(!m_modes.empty());

	// Check if the mode already exists
	while (idx < (int)m_modes.size() && m_modes.at(idx)->GetModeName() != _newMode) {
		++idx;
	}
	assert(idx < (int)m_modes.size());

	// Set the desired mode
	m_desModeIdx = idx;
	DBOUT("Current mode changed to: " << _newMode);
}

void ModeManager::Update(float _dTime) {
	if (m_desModeIdx != m_curModeIdx) {
		// Has the current mode been set or exited?
		if (m_curModeIdx == -1 || m_modes.at(m_curModeIdx)->Exit()) {
			m_curModeIdx = m_desModeIdx;
			// Enter new mode
			m_modes.at(m_curModeIdx)->Enter();
		}
	}

	assert(m_curModeIdx != -1);

	m_modes.at(m_curModeIdx)->Update(_dTime);
}

void ModeManager::Render(float _dTime, DirectX::SpriteBatch & _sprBatch) {
	// Ensure current mode index is valid
	if (CurIndexValid()) {
		m_modes.at(m_curModeIdx)->Render(_dTime, _sprBatch);
	}
}

void ModeManager::AddMode(std::shared_ptr<ModeBase> _modePtr) {
	// Ensure passed arg is valid
	assert(_modePtr);
	m_modes.push_back(_modePtr);
}

void ModeManager::Release() {
	m_modes.clear();
}

bool ModeManager::CurIndexValid() {
	return (m_curModeIdx >= 0 && m_curModeIdx < (int)m_modes.size());
}
