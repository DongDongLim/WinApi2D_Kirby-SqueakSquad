#pragma once
#include "CGameObject.h"
#include "CPlayer.h"

class CPlayerAttack;


class CAttackObj : public CGameObject
{
private:
	CPlayer* m_pPlayer;
	CPlayerAttack* m_pOwner;
	bool m_bIsActivity;
	fPoint m_fDir;
	fPoint m_fRange;

public:
	CAttackObj();
	virtual ~CAttackObj();
	virtual CAttackObj* Clone();

	void SetRange(fPoint range);


	void Enter();
	void Exit();

	virtual void finalupdate();

	virtual void update();
	virtual void render();



	virtual void OnCollision(CCollider* _pOther);
};