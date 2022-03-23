#pragma once

class CAnimator;
class CD2DImage;

struct tAniFrm
{
	fPoint fptLT;
	fPoint fptSlice;
	fPoint fptOffset;
	float fDuration;
};

class CAnimation
{
	friend class CAnimator;

private:
	wstring			m_strName;		// 애니메이션 이름
	CAnimator* m_pAnimator;	// 애니메이터
	CD2DImage* m_pImg;			// 애니메이션 이미지
	vector<tAniFrm> m_vecFrm;		// 모든 프레임의 자르기 영역 및 유지시간
	int				m_iCurFrm;		// 현재 프레임의 index
	float			m_fAccTime;		// 다음 프레임까지 축적시간

	bool			m_bReverseRender;
	bool			m_bReverseRenderRenderPlay;

public:
	CAnimation();
	CAnimation(const CAnimation& pOther);
	~CAnimation();

	void SetName(const wstring& strName);
	const wstring& GetName();

	void SetReversePlay(bool isreverse);
	void SetReverse(bool reverse);
	void SetFrame(int frmIndex);
	tAniFrm& GetFrame(int frmIndex);	
	int GetAnimSize();
	float GetFrameSpeed();

	void update();
	void render();

	void Create(CD2DImage* tex, fPoint lt, fPoint slice, fPoint step, float duration, UINT frmCount);	// 애니메이션 생성
};

