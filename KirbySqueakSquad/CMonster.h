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

	bool g_bIsRight = false;
	bool g_bIsUp = false;
	bool g_bIsDown = false;
	bool g_bIsLeft = false;
};

enum class MON_TYPE
{
	NORMAL,
	CUTTER,
	THROW,

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

	// Ÿ�ϰ��� �Ÿ�üũ
	float m_fTileLength;

	//�ѹ��� ������ Ÿ���� �ִ� 8����;
	CCollider* m_pTileCollider[8];
public:
	CMonster();
	virtual ~CMonster();
	virtual CMonster* Clone();

	static CMonster* Create(MON_TYPE type, fPoint pos);


	virtual void render();
	virtual void update();
	void TileCheckRender();
	virtual void finalupdate();

	float GetSpeed();
	const tMonInfo& GetMonInfo();

	void AddTileCollider(CCollider* ground);
	void TileCheck();


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
	virtual void OnCollision(CCollider* Other);
};

