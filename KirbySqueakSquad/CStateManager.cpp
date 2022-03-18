#include "framework.h"
#include "CStateManager.h"
#include "CState.h"


CStateManager::CStateManager()
{
	m_pPlayer = nullptr;
	m_mPlayerState = {};
	m_eCurState = PLAYERSTATE::IDLE;
}

CStateManager::~CStateManager()
{
	map<PLAYERSTATE, CState*>::iterator iter = m_mPlayerState.begin();
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

void CStateManager::AddState(PLAYERSTATE state, CState* stateclass)
{
	m_mPlayerState.insert(make_pair(state, stateclass));
}

void CStateManager::ChangeState(PLAYERSTATE state, PLAYERSTATE& curstate)
{
	CState* pState = FindState(state);
	CState* pCurstate = FindState(curstate);
	if (nullptr != pState && pCurstate != pState)
	{
		if (nullptr != pCurstate)//현재 상태
			pCurstate->Exit();
		pState->Enter();
		curstate = state;
	}

}

CState* CStateManager::FindState(PLAYERSTATE state)
{
	map<PLAYERSTATE, CState*>::iterator iter = m_mPlayerState.find(state);
	if (m_mPlayerState.end() != iter)
		return iter->second;
	return nullptr;
}
