#pragma once
#include "CGameObject.h"
#include "CPlayer.h"

class CPlayerAttack;
class CAnimation;
class CD2DImage;

enum class MOVETYPE
{
	FIX,
	VARIANCE,
	
	END,
};

enum class EFFECT_TYPE
{
	NINHALE0,
	NINHALE1,

	SIZE,
};

class CAttackObj : public CGameObject
{
private:
	CD2DImage* m_pImgEffect[(int)EFFECT_TYPE::SIZE];
	CAnimation* m_pThrowMon;
	MOVETYPE m_eMoveType;
	CPlayer* m_pPlayer;
	CPlayerAttack* m_pOwner;
	fPoint m_fDir;
	fPoint m_fRange;
	fPoint m_fStartPos;
	vector<float> m_aEffect;
	float m_fDelateRange;
	float m_fVelocity;
	float m_fReverceVelocity;


	float nomalanimtime;
	float nomalanimKeeptime;


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
	void ThrowSetting();
	void MoveUpdate();

	MOVETYPE GetMoveType();

	void Enter();
	void Exit();

	virtual void finalupdate();

	virtual void update();
	virtual void render();
	void NommalRender();
	void CutterRender();
	void ThrowRender();



	virtual void OnCollision(CCollider* _pOther);
};