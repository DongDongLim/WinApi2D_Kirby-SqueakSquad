#include "framework.h"
#include "CPlayerState.h"


CPlayerState::CPlayerState()
{
	m_pPlayer = CStateManager::getInst()->GetPlayer();
}

CPlayerState::~CPlayerState()
{
}

CPlayer* CPlayerState::GetPlayer()
{
	return m_pPlayer;
}




CPlayerIdle::CPlayerIdle()
{
}

CPlayerIdle::~CPlayerIdle()
{
}

void CPlayerIdle::update()
{
}

void CPlayerIdle::Enter()
{
}

void CPlayerIdle::Exit(PLAYERSTATE state)
{
}
