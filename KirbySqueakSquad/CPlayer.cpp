#include "framework.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CD2DImage.h"
#include "CState.h"


void CPlayer::playerIdle(DWORD_PTR, DWORD_PTR)
{
}

void CPlayer::playerMove(DWORD_PTR, DWORD_PTR)
{
	fPoint pos = GetPos();

	pos.x += m_dir * m_fVelocity * fDT;

	SetPos(pos);
}

void CPlayer::playerRight(DWORD_PTR, DWORD_PTR)
{
	m_dir = 1;
}

void CPlayer::playerLeft(DWORD_PTR, DWORD_PTR)
{
	m_dir = -1;
}

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
		LoadD2DImage(m_wImgKey[0], L"texture\\Animation\\sprite0.png"));
	m_pImg.push_back(CResourceManager::getInst()->
		LoadD2DImage(m_wImgKey[1], L"texture\\Animation\\sprite1.png"));
	m_pImg.push_back(CResourceManager::getInst()->
		LoadD2DImage(m_wImgKey[2], L"texture\\Animation\\sprite2.png"));
	m_pImg.push_back(CResourceManager::getInst()->
		LoadD2DImage(m_wImgKey[3], L"texture\\Animation\\sprite3.png"));
	m_pImg.push_back(CResourceManager::getInst()->
		LoadD2DImage(m_wImgKey[4], L"texture\\Animation\\sprite4.png"));
	m_pImg.push_back(CResourceManager::getInst()->
		LoadD2DImage(m_wImgKey[5], L"texture\\Animation\\sprite5.png"));
	m_pImg.push_back(CResourceManager::getInst()->
		LoadD2DImage(m_wImgKey[6], L"texture\\Animation\\sprite6.png"));
	m_pImg.push_back(CResourceManager::getInst()->
		LoadD2DImage(m_wImgKey[7], L"texture\\Animation\\sprite7.png"));
	m_pImg.push_back(CResourceManager::getInst()->
		LoadD2DImage(m_wImgKey[8], L"texture\\Animation\\sprite8.png"));

	for (int i = 0; i < m_pImg.size(); ++i)
	{
		m_wAnimKey.push_back(new vector<wstring>);
	}

	m_wAnimKey[0]->push_back(L"Idle");
	m_wAnimKey[0]->push_back(L"Down");
	m_wAnimKey[1]->push_back(L"Move");
	m_wAnimKey[2]->push_back(L"Dash");
	m_wAnimKey[2]->push_back(L"QUICKSTOP");
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

	GetAnimator()->CreateAnimation(
		m_wAnimKey[0]->at(0),
		m_pImg[0],
		fPoint(0.f, 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(0.f, 0.f), 0.5f, 1);

	GetAnimator()->CreateAnimation(
		m_wAnimKey[0]->at(1),
		m_pImg[0],
		fPoint(pixelSize, 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(0.f, 0.f), 0.5f, 1);

	GetAnimator()->CreateAnimation(
		m_wAnimKey[2]->at(1),
		m_pImg[0],
		fPoint(0.f, 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(pixelSize, 0.f), 0.1f, 8);

	GetAnimator()->CreateAnimation(
		m_wAnimKey[2]->at(1),
		m_pImg[0],
		fPoint((float)(pixelSize * 8), 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(pixelSize, 0.f), 0.5f, 1);

	GetAnimator()->CreateAnimation(
		m_wAnimKey[7]->at(0),
		m_pImg[0],
		fPoint(0.f, 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(pixelSize, 0.f), 0.1f, 2);

	GetAnimator()->CreateAnimation(
		m_wAnimKey[7]->at(1),
		m_pImg[0],
		fPoint((float)(pixelSize * 2), 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(pixelSize, 0.f), 0.1f, 2);

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
				fPoint(pixelSize, 0.f), 0.1f, frameCount);
		}
	}
	GetAnimator()->Play(L"Idle");

	CAnimation* pAni;
	pAni = GetAnimator()->FindAnimation(L"Idle");
	pAni->GetFrame(0).fptOffset = fPoint(0.f, 5.f);
	pAni = GetAnimator()->FindAnimation(L"Down");
	pAni->GetFrame(0).fptOffset = fPoint(0.f, 5.f);


	CState* pIdle = new CState(this);
	//pIdle->SetUpdageCallBack(&playerIdle, 0, 0);
	CStateManager::getInst()->AddState(PLAYERSTATE::IDLE, pIdle);
	CState* pMove = new CState(this);
	pMove->SetUpdageCallBack(&playerMove, 0, 0);
	CStateManager::getInst()->AddState(PLAYERSTATE::MOVE, pMove);

	CState* pLEFT = new CState(this);
	CStateManager::getInst()->AddState(PLAYERSTATE::LEFT, pLEFT);
	CState* pRIGHT = new CState(this);
	CStateManager::getInst()->AddState(PLAYERSTATE::RIGHT, pRIGHT);

	m_pCurAtiveState = pIdle;
	m_pDirState = pRIGHT;
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

	if (Key(VK_LEFT) || Key(VK_RIGHT))
	{
		Key(VK_LEFT) ? CStateManager::getInst()->ChangeState(PLAYERSTATE::LEFT, m_pDirState) : CStateManager::getInst()->ChangeState(PLAYERSTATE::RIGHT, m_pDirState);
		CStateManager::getInst()->ChangeState(PLAYERSTATE::MOVE, m_pCurAtiveState);
	}

	GetAnimator()->update();
}

void CPlayer::render()
{
	component_render();
}