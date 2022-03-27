#pragma once
#include "CGameObject.h"
#include "CPlayer.h"

class CPlayerAttack;

enum class MOVETYPE
{
	FIX,
	VARIANCE,
	
	END,
};

class CAttackObj : public CGameObject
{
private:
	MOVETYPE m_eMoveType;
	CPlayer* m_pPlayer;
	CPlayerAttack* m_pOwner;
	fPoint m_fDir;
	fPoint m_fRange;
	fPoint m_fStartPos;
	float m_fDelateRange;
	float m_fVelocity;
	float m_fReverceVelocity;

public:
	CAttackObj();
	virtual ~CAttackObj();
	virtual CAttackObj* Clone();

	void SetRange(fPoint range);
	void SetDelateRange(float range);
	void SetStartPos(fPoint range);
	void SetVelocity(float velocity);
	void SetReverceVelocity(float velocity);

	void NomalSetting();
	void CutterSetting();
	void MoveUpdate();



	void Enter();
	void Exit();

	virtual void finalupdate();

	virtual void update();
	virtual void render();
	void CutterRender();



	virtual void OnCollision(CCollider* _pOther);
};