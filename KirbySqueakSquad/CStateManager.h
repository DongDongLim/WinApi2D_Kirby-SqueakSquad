#pragma once

class CState;

enum class PLAYERSTATE
{
	IDLE,
	MOVE,
	DOWN,
	FLY,
	EAT,
	INHALE,
	TRANSFORM,
	RIGHT,
	LEFT,

	END,
};


class CStateManager
{

	SINGLETON(CStateManager);

private:
	map<PLAYERSTATE, CState*> m_mPlayerState;
	PLAYERSTATE m_ePlayerState;

public:
	void AddState(PLAYERSTATE state, CState* stateclass);
	void ChangeState(PLAYERSTATE state, PLAYERSTATE& curstate);

	CState* FindState(PLAYERSTATE state);
};

