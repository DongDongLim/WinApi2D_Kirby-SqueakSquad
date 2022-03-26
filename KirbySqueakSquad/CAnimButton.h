#pragma once
#include "CButtonUI.h"
class CAnimButton : public CButtonUI
{
private:
	int m_iIdx;

public:
	CAnimButton();
	virtual ~CAnimButton();

	virtual void render();

	int GetIdx();
	void SetIdx(int idx);
};

