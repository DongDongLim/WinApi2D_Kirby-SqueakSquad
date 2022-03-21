#pragma once
class CGameObject;

class CGravity
{
	friend class CGameObject;
private:
	// ���� �ӷ� ����
	const fPoint m_fMaxPositiveVelocity = fPoint(75.f, 200.f);
	// ���� �ӷ� ����
	const fPoint m_fMaxNegativeVelocity = fPoint(-75.f, -200.f);
	CGameObject* m_pOwner;
	bool m_bisGround;
	fPoint m_fGAccel;
public:
	CGravity();
	~CGravity();

	void SetIsGround(bool isGround);
	bool GetIsGround();


	void finalupdate();
};

