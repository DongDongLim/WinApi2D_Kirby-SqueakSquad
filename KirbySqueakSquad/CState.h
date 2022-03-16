#pragma once
#include "CPlayer.h"

// �Լ������͸� ���� Ÿ������
typedef void(CPlayer::*ONER_FUNC)(DWORD_PTR, DWORD_PTR);

class CState
{
protected:
	ONER_FUNC m_pFunc;
	DWORD_PTR m_pParam1;
	DWORD_PTR m_pParam2;

	ONER_FUNC m_pEFunc;
	DWORD_PTR m_pEParam1;
	DWORD_PTR m_pEParam2;

	ONER_FUNC m_pUFunc;
	DWORD_PTR m_pUParam1;
	DWORD_PTR m_pUParam2;

	CPlayer* m_pOner;

public:
	CState();
	CState(CPlayer* oner);
	~CState();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
	
	void (CPlayer::* SetEnter)(DWORD_PTR, DWORD_PTR);
	void (CPlayer::* SetUpdage)(DWORD_PTR, DWORD_PTR);
	void (CPlayer::* SetExit)(DWORD_PTR, DWORD_PTR);


	void SetEnterCallBack(ONER_FUNC pFunc, DWORD_PTR param1, DWORD_PTR param2);

	void SetUpdageCallBack(ONER_FUNC pFunc, DWORD_PTR param1, DWORD_PTR param2);

	void SetExitCallBack(ONER_FUNC pFunc, DWORD_PTR param1, DWORD_PTR param2);
};

