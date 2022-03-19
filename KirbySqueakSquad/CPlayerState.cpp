#include "framework.h"
#include "CPlayerState.h"


CPlayerState::CPlayerState()
{
	m_eState = PLAYERSTATE::END;
	m_pPlayer = CStateManager::getInst()->GetPlayer();
}

CPlayerState::~CPlayerState()
{
}

CPlayer* CPlayerState::GetPlayer()
{
	return m_pPlayer;
}

bool CPlayerState::GetIsActive()
{
	return m_bIsActive;
}



