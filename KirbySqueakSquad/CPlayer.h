#pragma once
#include "CGameObject.h"

/*
#define LEFTDEFINE Key(VK_LEFT)
#define RIGHTDEFINE Key(VK_RIGHT)
#define UPDEFINE Key(VK_UP)
#define DOWNDEFINE Key(VK_DOWN)
#define ACTTACKDEFINE Key('C')
#define TRANSFORMDEFINE Key('Z')
*/
#define JUMPDEFINE Key('V')||Key('X')
#define KEYEMPTYDEFINE !Key(VK_LEFT)&&!Key(VK_RIGHT)&&! Key(VK_UP)&&!Key(VK_DOWN)&&! Key('C')&&!JUMPDEFINE&&!Key('Z')
#define ANYKEYDOWN KeyDown(VK_LEFT)||KeyDown(VK_RIGHT)||KeyDown(VK_UP)||KeyDown(VK_DOWN)||KeyDown('C')||KeyDown('V')||KeyDown('X')||KeyDown('Z')

/* TODO :	� Ű�� �Է� �޾Ҿ������� üũ�ؾ���
			�̰� ���·� üũ�� �Ѵ�?
			�Ʒ� ������ ������ � ���·�?
			Ŀ���� �޺��� �ִ� 3�������� Ű �Է��� ����
			Ű ���¸� �����?
			ó������ ���¸� ���� �ð� �����ϰ� �� ���¿��� �ٸ� Ű�� ������
			�޺��� ����Ǵ� ���� �����ߴµ� �ϴ� �װź��� �����غ���
			Ű�� �Է� �޴� ���� �� Ű�� �˾Ƽ� �����ϸ� �������� 
			������ enter exit�� ����ؼ� ������ ������ ���� �����غ���
			�ٵ� �׷��� ������ �����ߵǴµ�...
			��� �� ���� ���¸� �����ϴ� �� CState�� ����Ϸ� ����? �׳� ����� ���ݾ�
*/

class CState;
class CD2DImage;

struct PLAYERINFO
{
	const float g_fCommandTime = 0.2f;
	const float g_fAccel = 1.5f;
	const float m_fVelocity = 150;
	int m_dir = 1;

};

class CPlayer : public CGameObject
{
	friend CStateManager;
private:
	// ���ϸ��̼� ���
	bool m_bIsAnimStay;

	// ��� �ð�
	float m_animStayTime;
	float m_commandStayTime;

	// �÷��̾� �ִϸ��̼� ����� ���� �̹�����
	vector<CD2DImage*> m_pImg;
	// �÷��̾� �ִϸ��̼� �̹����� Ű��
	vector<wstring> m_wImgKey;
	// �÷��̾� �ִϸ��̼� ������ Ű��
	vector<vector<wstring>*> m_wAnimKey;

	COMMANDKEY m_eCurCommand;
	PLAYERSTATE m_ePevState;
	PLAYERSTATE m_eCurAtiveState;
	PLAYERSTATE m_eDirState;


	void PlayerIdle(DWORD_PTR, DWORD_PTR);

	void PlayerMove(DWORD_PTR, DWORD_PTR);

	void PlayerRight(DWORD_PTR, DWORD_PTR);

	void PlayerLeft(DWORD_PTR, DWORD_PTR);

	void PlayerJump(DWORD_PTR, DWORD_PTR);

	void PlayerAttack(DWORD_PTR, DWORD_PTR);

	void PlayerEat(DWORD_PTR, DWORD_PTR);

	void PlayerFly(DWORD_PTR, DWORD_PTR);

	void PlayerTransForm(DWORD_PTR, DWORD_PTR);

	void PlayerChangeDir(DWORD_PTR, DWORD_PTR);

	void CommandCheck(DWORD_PTR, DWORD_PTR);

	void CommandSave(PLAYERSTATE key);

public:

	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();
	
	virtual void update();
	virtual void render();


};

