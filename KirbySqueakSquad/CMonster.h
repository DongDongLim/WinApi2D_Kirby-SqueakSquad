#pragma once
#include "CGameObject.h"

class CD2DImage;
class AI;

struct tMonInfo
{
	float fSpeed;
	float fHP;
	float fRecogRange;
	float fAttRange;
	float fAtt;
};

enum class MON_TYPE
{
	NORMAL,
	CUTTER,

	SIZE,
};

class CMonster : public CGameObject
{
private:
	MON_TYPE m_eType;
	tMonInfo m_tInfo;
	AI* m_pAI;
	bool m_bIsEaten;
	float m_fRegenPosX;

public:
	CMonster();
	virtual ~CMonster();
	virtual CMonster* Clone();

	static CMonster* Create(MON_TYPE type, fPoint pos);


	virtual void render();
	virtual void update();
	virtual void finalupdate();

	float GetSpeed();
	const tMonInfo& GetMonInfo();

	void SetIsEaten(bool isEaten);
	void SetSpeed(float speed);
	void SetAI(AI* ai);
	void SetMonInfo(const tMonInfo& info);
	void SetEaten(bool isEaten);
	void SetType(MON_TYPE type);
	void SetRegenPosX(float posX);
			
	MON_TYPE GetType();
	bool GetIsEaten();
	float GetRegenPosX();

	void OnCollisionEnter(CCollider* pOther);
};

