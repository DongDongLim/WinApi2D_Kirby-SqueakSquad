#include "framework.h"
#include "CStateManager.h"
#include "CState.h"


CStateManager::CStateManager()
{
	m_mPlayerState = {};
	m_ePlayerState = PLAYERSTATE::IDLE;
}

CStateManager::~CStateManager()
{
	map<PLAYERSTATE, CState*>::iterator iter = m_mPlayerState.begin();
	for (; iter != m_mPlayerState.end(); ++iter)
	{
		delete iter->second;
	}
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
		if (nullptr != pCurstate)//���� ����
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
