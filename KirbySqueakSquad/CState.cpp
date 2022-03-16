#include "framework.h"
#include "CState.h"
#include "CPlayer.h"

CState::CState()
{
	m_pFunc = nullptr;
	m_pParam1 = 0;
	m_pParam2 = 0;
	m_pUFunc = nullptr;
	m_pUParam1 = 0;
	m_pUParam2 = 0;
	m_pEFunc = nullptr;
	m_pEParam1 = 0;
	m_pEParam2 = 0;
}

CState::CState(CPlayer* oner)
{
	m_pOner = oner;
	m_pFunc = nullptr;
	m_pParam1 = 0;
	m_pParam2 = 0;
	m_pUFunc = nullptr;
	m_pUParam1 = 0;
	m_pUParam2 = 0;
	m_pEFunc = nullptr;
	m_pEParam1 = 0;
	m_pEParam2 = 0;
}

CState::~CState()
{
}

void CState::Enter()
{
	if (nullptr != m_pFunc)
	{
		(m_pOner->*m_pFunc)(m_pParam1, m_pParam2);
	}
}
void CState::update()
{
	if (nullptr != m_pUFunc)
	{
		(m_pOner->*m_pUFunc)(m_pUParam1, m_pUParam2);
	}
}


void CState::Exit()
{
	if (nullptr != m_pEFunc)
	{
		(m_pOner->*m_pEFunc)(m_pEParam1, m_pEParam2);
	}
}

void CState::SetEnterCallBack(ONER_FUNC pFunc, DWORD_PTR param1, DWORD_PTR param2)
{
	m_pFunc = pFunc;
	m_pParam1 = param1;
	m_pParam2 = param2;
}

void CState::SetUpdageCallBack(ONER_FUNC pFunc, DWORD_PTR param1, DWORD_PTR param2)
{
	m_pUFunc = pFunc;
	m_pUParam1 = param1;
	m_pUParam2 = param2;
}

void CState::SetExitCallBack(ONER_FUNC pFunc, DWORD_PTR param1, DWORD_PTR param2)
{
	m_pEFunc = pFunc;
	m_pEParam1 = param1;
	m_pEParam2 = param2;
}


