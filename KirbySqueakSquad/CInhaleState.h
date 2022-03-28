#pragma once
#include "CState.h"
class CInhaleState : public CState
{
public:
	CInhaleState(STATE_MON state);
	virtual ~CInhaleState();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

