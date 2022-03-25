#pragma once

class CMonster;
class CState;

class AI
{
	friend class CMonster;

private:
	map<STATE_MON, CState*> m_mapState;
	CMonster* m_pOwner;
	CState* m_pCurState;
	fPoint m_fStartPos;

public:
	AI();
	~AI();

	void SetCurState(STATE_MON state);
	void SetStartPos(fPoint pos);


	CMonster* GetOwnerAI();
	CState* GetState(STATE_MON state);
	fPoint GetStartPos();

	void update();

	void AddState(CState* state);
	void ChangeState(STATE_MON nextState);

};

