#pragma once
#include "CGameObject.h"

class CState;
class CD2DImage;

class CPlayer : public CGameObject
{
private:

	// �÷��̾� �ִϸ��̼� ����� ���� �̹�����
	vector<CD2DImage*> m_pImg;
	// �÷��̾� �ִϸ��̼� �̹����� Ű��
	vector<wstring> m_wImgKey;
	// �÷��̾� �ִϸ��̼� ������ Ű��
	vector<vector<wstring>*> m_wAnimKey;

	CState* m_pCurAtiveState;
	CState* m_pDirState;

	int m_dir = 1;

	float m_fVelocity = 200;

	void playerIdle(DWORD_PTR, DWORD_PTR);

	void playerMove(DWORD_PTR, DWORD_PTR);

	void playerRight(DWORD_PTR, DWORD_PTR);

	void playerLeft(DWORD_PTR, DWORD_PTR);


public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();
	
	virtual void update();
	virtual void render();


};

