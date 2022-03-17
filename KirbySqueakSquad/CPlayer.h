#pragma once
#include "CGameObject.h"

#define LEFTDEFINE Key(VK_LEFT)
#define RIGHTDEFINE Key(VK_RIGHT)
#define UPDEFINE Key(VK_UP)
#define DOWNDEFINE Key(VK_DOWN)
#define ACTTACKDEFINE Key('C')
#define JUMPDEFINE Key('V')||Key('X')
#define TRANSFORMDEFINE Key('Z')
#define KEYEMPTYDEFINE !LEFTDEFINE&&!RIGHTDEFINE&&!UPDEFINE&&!DOWNDEFINE&&!ACTTACKDEFINE&&!JUMPDEFINE&&!TRANSFORMDEFINE

class CState;
class CD2DImage;

const static float g_fCommandTime = 0.5f;

class CPlayer : public CGameObject
{
private:
	// 에니메이션 대기
	bool m_bIsAnimStay;

	// 대기 시간
	float m_animStayTime;
	float m_commandStayTime;

	// 플레이어 애니메이션 재생을 위한 이미지들
	vector<CD2DImage*> m_pImg;
	// 플레이어 애니메이션 이미지의 키값
	vector<wstring> m_wImgKey;
	// 플레이어 애니메이션 동작의 키값
	vector<vector<wstring>*> m_wAnimKey;

	PLAYERSTATE m_pPevState;
	PLAYERSTATE m_pCurAtiveState;
	PLAYERSTATE m_pDirState;

	int m_dir = 1;

	float m_fVelocity = 200;

	void PlayerIdle(DWORD_PTR, DWORD_PTR);

	void PlayerMove(DWORD_PTR, DWORD_PTR);

	void PlayerRight(DWORD_PTR, DWORD_PTR);

	void PlayerLeft(DWORD_PTR, DWORD_PTR);

	void PlayerJump(DWORD_PTR, DWORD_PTR);

	void PlayerInHale(DWORD_PTR, DWORD_PTR);

	void PlayerEat(DWORD_PTR, DWORD_PTR);

	void PlayerFly(DWORD_PTR, DWORD_PTR);

	void PlayerTransForm(DWORD_PTR, DWORD_PTR);

	void PlayerChangeDir(DWORD_PTR, DWORD_PTR);


public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();
	
	virtual void update();
	virtual void render();


};

