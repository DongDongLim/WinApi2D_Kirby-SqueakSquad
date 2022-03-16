#pragma once
#include "CGameObject.h"


class CD2DImage;

class CPlayer : public CGameObject
{
private:
	// 플레이어 방향
	int m_iDir;

	// Fly 애니메이션 상태인가 체크
	bool m_isFly;

	// 플레이어 애니메이션 재생을 위한 이미지들
	vector<CD2DImage*> m_pImg;
	// 플레이어 애니메이션 이미지의 키값
	vector<wstring> m_wImgKey;
	// 플레이어 애니메이션 동작의 키값
	vector<vector<wstring>*> m_wAnimKey;

	float m_fVelocity = 200;

	// 이동
	void Move();
	// 날기
	void Fly();
	// 점프
	void Jump();
	// 방향 세팅
	void SetDir();


public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();

	
	virtual void update();
	virtual void render();


};

