#include "framework.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CD2DImage.h"


CPlayer::CPlayer()
{
	m_wImgKey.push_back(L"PlayerImg0");
	m_wImgKey.push_back(L"PlayerImg1");
	m_wImgKey.push_back(L"PlayerImg2");
	m_wImgKey.push_back(L"PlayerImg3");
	m_wImgKey.push_back(L"PlayerImg4");
	m_wImgKey.push_back(L"PlayerImg5");
	m_wImgKey.push_back(L"PlayerImg6");
	m_wImgKey.push_back(L"PlayerImg7");
	m_wImgKey.push_back(L"PlayerImg8");


	m_pImg.push_back(CResourceManager::getInst()->
		LoadD2DImage(m_wImgKey[0], L"texture\\sprite0.bmp"));
	m_pImg.push_back(CResourceManager::getInst()->
		LoadD2DImage(m_wImgKey[1], L"texture\\sprite1.bmp"));
	m_pImg.push_back(CResourceManager::getInst()->
		LoadD2DImage(m_wImgKey[2], L"texture\\sprite2.bmp"));
	m_pImg.push_back(CResourceManager::getInst()->
		LoadD2DImage(m_wImgKey[3], L"texture\\sprite3.bmp"));
	m_pImg.push_back(CResourceManager::getInst()->
		LoadD2DImage(m_wImgKey[4], L"texture\\sprite4.bmp"));
	m_pImg.push_back(CResourceManager::getInst()->
		LoadD2DImage(m_wImgKey[5], L"texture\\sprite5.bmp"));
	m_pImg.push_back(CResourceManager::getInst()->
		LoadD2DImage(m_wImgKey[6], L"texture\\sprite6.bmp"));
	m_pImg.push_back(CResourceManager::getInst()->
		LoadD2DImage(m_wImgKey[7], L"texture\\sprite7.bmp"));
	m_pImg.push_back(CResourceManager::getInst()->
		LoadD2DImage(m_wImgKey[8], L"texture\\sprite8.bmp"));

	for (int i = 0; i < m_pImg.size(); ++i)
	{
		m_wAnimKey.push_back(new vector<wstring>);
	}

	m_wAnimKey[0]->push_back(L"Idle");
	m_wAnimKey[0]->push_back(L"Down");
	m_wAnimKey[1]->push_back(L"Move");
	m_wAnimKey[2]->push_back(L"Dash");
	m_wAnimKey[3]->push_back(L"DownSlide");
	m_wAnimKey[4]->push_back(L"Jump");
	m_wAnimKey[5]->push_back(L"Eat");
	m_wAnimKey[6]->push_back(L"Up");
	m_wAnimKey[7]->push_back(L"UpIdle");
	m_wAnimKey[7]->push_back(L"UpMove");
	m_wAnimKey[8]->push_back(L"BreatheIn");


	SetName(L"Player");
	SetScale(fPoint(32.f, 32.f));

	CreateCollider();
	GetCollider()->SetScale(fPoint(30.f, 30.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 0.f));

	CreateAnimator();
	float pixelSize = 32.f;
	for (int i = 0; i < m_wAnimKey.size(); ++i)
	{
		if (1 == m_wAnimKey[i]->size())
		{
			UINT frameCount = (UINT)CResourceManager::getInst()->
				FindD2DImage(m_wImgKey[0])->GetWidth() / (UINT)pixelSize;
			GetAnimator()->CreateAnimation(
				m_wAnimKey[i]->at(0),
				m_pImg[i],
				fPoint(0.f, 0.f),
				fPoint(pixelSize, pixelSize),
				fPoint(pixelSize, 0.f), 0.3f, frameCount);
		}
	}

	GetAnimator()->CreateAnimation(
		m_wAnimKey[0]->at(0),
		m_pImg[0],
		fPoint(0.f, 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(0.f, 0.f), 0.3f, 1);

	GetAnimator()->CreateAnimation(
		m_wAnimKey[0]->at(1),
		m_pImg[0],
		fPoint(pixelSize, 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(0.f, 0.f), 0.3f, 1);

	GetAnimator()->CreateAnimation(
		m_wAnimKey[7]->at(0),
		m_pImg[0],
		fPoint(0.f, 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(pixelSize, 0.f), 0.3f, 2);

	GetAnimator()->CreateAnimation(
		m_wAnimKey[7]->at(1),
		m_pImg[0],
		fPoint((float)(pixelSize * 2), 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(pixelSize, 0.f), 0.3f, 2);

	GetAnimator()->Play(L"Idle");

	CAnimation* pAni;
	pAni = GetAnimator()->FindAnimation(L"Idle");
	pAni->GetFrame(0).fptOffset = fPoint(0.f, 5.f);
	pAni = GetAnimator()->FindAnimation(L"Down");
	pAni->GetFrame(0).fptOffset = fPoint(0.f, 5.f);

}

CPlayer::~CPlayer()
{
	for (int i = 0; i < m_wAnimKey.size(); ++i)
	{
		delete m_wAnimKey[i];
	}
}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
}

void CPlayer::update()
{
	fPoint pos = GetPos();

	if (Key(VK_LEFT))
	{
		pos.x -= m_fVelocity * fDT;
		GetAnimator()->Play(L"LeftMove");
	}
	if (Key(VK_RIGHT))
	{
		pos.x += m_fVelocity * fDT;
		GetAnimator()->Play(L"RightMove");
	}
	if (Key(VK_UP))
	{
		pos.y -= m_fVelocity * fDT;
	}
	if (Key(VK_DOWN))
	{
		pos.y += m_fVelocity * fDT;
	}

	SetPos(pos);


	GetAnimator()->update();
}

void CPlayer::render()
{
	component_render();
}