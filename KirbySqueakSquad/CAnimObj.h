#pragma once
#include "CGameObject.h"
class CAnimObj : public CGameObject
{
private:
	wstring m_wName;	// 애니메이션 이름
	int m_iX;
	int m_iY;
	float m_fAccTime;	// 프레임 지속시간
	int m_fOffSetX;   // 애니메이션 오프셋
	int m_fOffSetY;
	GROUP_ANIM m_group;

public:
	const static int SIZE_ANIM = 32;

	CAnimObj();
	virtual ~CAnimObj();

	virtual CAnimObj* Clone();

	virtual void update();
	virtual void render();

	void SetX(int x);
	void SetY(int y);
	void SetAccTime(float time);
	void SetOffSet(fPoint offset);
	void SetGroupAnim(GROUP_ANIM group);

	int GetX();
	int GetY();
	float GetAccTime();
	fPoint GetOffSet();
	GROUP_ANIM GetGroupAnim();

	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
};

