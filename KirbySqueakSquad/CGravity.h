#pragma once
class CGameObject;

class CGravity
{
	friend class CGameObject;
private:
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

