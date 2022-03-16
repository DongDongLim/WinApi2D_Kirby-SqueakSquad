#pragma once
#include "CGameObject.h"


class CD2DImage;

class CPlayer : public CGameObject
{
private:
	// 플레이어 애니메이션 재생을 위한 이미지들
	vector<CD2DImage*> m_pImg;
	// 플레이어 애니메이션 이미지의 키값
	vector<wstring> m_wImgKey;
	// 플레이어 애니메이션 동작의 키값
	vector<vector<wstring>*> m_wAnimKey;

	float m_fVelocity = 300;

public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();

	
	virtual void update();
	virtual void render();


};

