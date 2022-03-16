#pragma once
#include "CGameObject.h"


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

	float m_fVelocity = 300;

public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();

	
	virtual void update();
	virtual void render();


};

