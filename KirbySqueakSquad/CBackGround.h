#pragma once
#include "CGameObject.h"
class CBackGround : public CGameObject
{
private:
	CD2DImage* m_pImg;

public:
	CBackGround();
	~CBackGround();

	virtual CBackGround* Clone();
	virtual void update();
	virtual void render();

	void Load(wstring strKey, wstring strPath);
};

