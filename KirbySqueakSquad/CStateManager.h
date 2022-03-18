#pragma once
class CPlayer;
class CState;
class CPlayerState;

enum class PLAYERSTATE
{
	IDLE,
	MOVE,
	DOWN,
	FLY,
	EAT,
	ATTACK,
	TRANSFORM,
	RIGHT,
	LEFT,

	END,
};

enum class COMMANDKEY
{
	DASH,

	END
};


class CStateManager
{
	SINGLETON(CStateManager);

private:

	CPlayer* m_pPlayer;
	map<PLAYERSTATE, CState*> m_mPlayerState;
	PLAYERSTATE m_eCurState;

public:
	void SetPlayer(CPlayer* player);
	CPlayer* GetPlayer();

	void AddState(PLAYERSTATE state, CState* stateclass);
	void ChangeState(PLAYERSTATE state, PLAYERSTATE& curstate);

	CState* FindState(PLAYERSTATE state);
};

