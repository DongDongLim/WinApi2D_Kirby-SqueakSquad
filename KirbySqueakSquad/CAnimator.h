#pragma once

class CGameObject;
class CAnimation;
class CD2DImage;

class CAnimator
{
	friend class CGameObject;

private:
	map<wstring, CAnimation*>	m_mapAni;
	CAnimation* m_pCreatenAni;
	CAnimation* m_pCurAni;
	CGameObject* m_pOwner;
	bool m_bIsStop;

public:
	CAnimator();
	CAnimator(const CAnimator& pOther);
	~CAnimator();

	CGameObject* GetObj();

	void update();
	void render();

	void Stop();

	void SetReverce(bool reverce);
	void CreateAnimation(const wstring& strName, CD2DImage* tex, fPoint lt, fPoint slice,
		fPoint step, float duration, UINT frmCount, bool reverse = false);
	CAnimation* FindAnimation(const wstring& strName);
	void Play(const wstring& strName);
	void ReversePlay(const wstring& strName);
	int GetAnimSize();
	float GetFrameSpeed();
	CAnimation* GetCurAnim();
	CAnimation* GetCreatenAnim();
};

