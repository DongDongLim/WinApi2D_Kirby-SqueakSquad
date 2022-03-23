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
	RANGE,

	SIZE,
};

class CMonster : public CGameObject
{
private:
	tMonInfo m_tInfo;
	AI* m_pAI;
	bool m_bIsEaten;
	bool m_bIsLive;

public:
	CMonster();
	virtual ~CMonster();
	virtual CMonster* Clone();

	static CMonster* Create(MON_TYPE type, fPoint pos);

	virtual void render();
	virtual void update();

	float GetSpeed();
	const tMonInfo& GetMonInfo();

	void SetSpeed(float speed);
	void SetAI(AI* ai);
	void SetMonInfo(const tMonInfo& info);
	void SetLive(bool isLive);
	void SetEaten(bool isEaten);
	bool GetIsEaten();

	void OnCollisionEnter(CCollider* pOther);
};

