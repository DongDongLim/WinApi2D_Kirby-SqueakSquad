#pragma once
#include "CGameObject.h"


class CD2DImage;

class CPlayer : public CGameObject
{
private:
	// �÷��̾� ����
	int m_iDir;

	// Fly �ִϸ��̼� �����ΰ� üũ
	bool m_isFly;

	// �÷��̾� �ִϸ��̼� ����� ���� �̹�����
	vector<CD2DImage*> m_pImg;
	// �÷��̾� �ִϸ��̼� �̹����� Ű��
	vector<wstring> m_wImgKey;
	// �÷��̾� �ִϸ��̼� ������ Ű��
	vector<vector<wstring>*> m_wAnimKey;

	float m_fVelocity = 200;

	// �̵�
	void Move();
	// ����
	void Fly();
	// ����
	void Jump();
	// ���� ����
	void SetDir();


public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();

	
	virtual void update();
	virtual void render();


};

