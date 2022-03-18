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

const static float g_fCommandTime = 0.5f;
const static float g_fAccel = 1.2f;

class CPlayer : public CGameObject
{
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

