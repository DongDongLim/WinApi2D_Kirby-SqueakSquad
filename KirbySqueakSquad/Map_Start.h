#pragma once
#include "CGameObject.h"

class CD2DImage;

class Map_Start : public CGameObject
{
private:
	int m_indexBG;

public:
	CD2DImage* pimgBG;
	CD2DImage* pimgMap;

	Map_Start();
	~Map_Start();

	virtual Map_Start* Clone();
	virtual void update();
	virtual void render();
};

