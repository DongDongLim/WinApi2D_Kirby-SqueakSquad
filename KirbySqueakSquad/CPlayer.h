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

/* TODO :	어떤 키를 입력 받았었는지를 체크해야함
			이걸 상태로 체크를 한다?
			아래 오른쪽 공격은 어떤 상태로?
			커비의 콤보는 최대 3개까지의 키 입력을 받음
			키 상태를 만들까?
			처음에는 상태를 일정 시간 저장하고 그 상태에서 다른 키가 눌리면
			콤보가 적용되는 것을 생각했는데 일단 그거부터 적용해보자
			키를 입력 받는 순간 그 키를 알아서 저장하면 좋겠지만 
			상태의 enter exit를 사용해서 만들어보는 과정을 먼저 진행해보자
			근데 그러면 일일이 만들어야되는데...
			잠깐 왜 굳이 상태를 저장하는 걸 CState를 사용하려 했지? 그냥 만들면 되잖아
*/

class CState;
class CD2DImage;

const static float g_fCommandTime = 0.5f;
const static float g_fAccel = 1.2f;

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

	COMMANDKEY m_eCurCommand;
	PLAYERSTATE m_ePevState;
	PLAYERSTATE m_eCurAtiveState;
	PLAYERSTATE m_eDirState;

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

	void CommandCheck();

	void CommandSave(PLAYERSTATE key);

public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();
	
	virtual void update();
	virtual void render();


};

