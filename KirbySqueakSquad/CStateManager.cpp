#include "framework.h"
#include "CState.h"
#include "CPlayerState.h"


CStateManager::CStateManager()
{
	m_pPlayer = nullptr;
	m_mPlayerState = {};
	m_eCurState = PLAYERSTATE::END;
}

CStateManager::~CStateManager()
{
	map<PLAYERSTATE, CPlayerState*>::iterator iter = m_mPlayerState.begin();
	for (; iter != m_mPlayerState.end(); ++iter)
	{
		delete iter->second;
	}
}

void CStateManager::SetPlayer(CPlayer* player)
{
	// 플레이어는 오직 하나!
	if (nullptr != m_pPlayer)
		assert(nullptr);
	m_pPlayer = player;
}

CPlayer* CStateManager::GetPlayer()
{
	return m_pPlayer;
}

void CStateManager::AddState(PLAYERSTATE state, CPlayerState* stateclass)
{
	m_mPlayerState.insert(make_pair(state, stateclass));
}

void CStateManager::ChangeState(PLAYERSTATE state)
{
	if (m_eCurState != state)
	{
		m_pCurState->Exit(state);
	}
}

void CStateManager::StartState(PLAYERSTATE state)
{
	if (m_eCurState != state)
	{
		CPlayerState* pState = FindState(state);

		assert(pState);
		pState->Enter();
		m_pCurState = pState;
		m_eCurState = state;
	}
}


void CStateManager::update()
{
	/* 커비의 커맨드는 일정 시간내에 입력이 아니라 특정 동작 중에 키 입력으로 받고 있음
	if (m_fcommandTimer > 0)
	{
		m_fcommandTimer -= fDT;
		m_ePrevState = PLAYERSTATE::END;
		m_eCurCommand = COMMANDKEY::END;
	}
	*/
	m_pCurState->update();
}

void CStateManager::SetCommend(COMMANDKEY commend)
{
	m_eCurCommand = commend;
}

COMMANDKEY CStateManager::GetCommend()
{
	return m_eCurCommand;
}

/*
void CStateManager::CommandSave()
{
	m_ePrevState = m_eCurState;
	m_fcommandTimer = m_pPlayer->m_fCommandTime;
}
*/

CPlayerState* CStateManager::FindState(PLAYERSTATE state)
{
	map<PLAYERSTATE, CPlayerState*>::iterator iter = m_mPlayerState.find(state);
	if (m_mPlayerState.end() != iter)
		return iter->second;
	return nullptr;
}
