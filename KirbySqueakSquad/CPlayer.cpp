#include "framework.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CD2DImage.h"
#include "CState.h"



void CPlayer::PlayerIdle(DWORD_PTR, DWORD_PTR)
{
	GetAnimator()->Play(L"Idle");
}

void CPlayer::PlayerMove(DWORD_PTR, DWORD_PTR)
{

	fPoint pos = GetPos();
	GetAnimator()->SetReverce(m_dir < 0 ? true : false);
	if (!m_bIsAnimStay)
	{
		if (m_eCurCommand == COMMANDKEY::DASH)
		{
			GetAnimator()->Play(L"Move");
			pos.x += m_dir * m_fVelocity * fDT;
		}
		else
		{
			GetAnimator()->Play(L"Dash");
			pos.x += m_dir * m_fVelocity * g_fAccel * fDT;
		}
	}
	else
	{
		GetAnimator()->Play(L"QuickStop");
		pos.x += m_dir * m_fVelocity * m_animStayTime * fDT;
		m_animStayTime -= fDT;
		if (m_animStayTime <= 0)
		{
			m_animStayTime = 0;
			m_bIsAnimStay = false;
		}
	}

	SetPos(pos);

}

void CPlayer::PlayerLeft(DWORD_PTR, DWORD_PTR)
{
	if (!m_bIsAnimStay)
		m_dir = -1;
}

void CPlayer::PlayerRight(DWORD_PTR, DWORD_PTR)
{
	if (!m_bIsAnimStay)
		m_dir = 1;
}

void CPlayer::PlayerJump(DWORD_PTR, DWORD_PTR)
{
}

void CPlayer::PlayerInHale(DWORD_PTR, DWORD_PTR)
{
	GetAnimator()->Play(L"InHale");
}

void CPlayer::PlayerEat(DWORD_PTR, DWORD_PTR)
{
}

void CPlayer::PlayerFly(DWORD_PTR, DWORD_PTR)
{
}

void CPlayer::PlayerTransForm(DWORD_PTR, DWORD_PTR)
{
}

void CPlayer::PlayerChangeDir(DWORD_PTR, DWORD_PTR)
{
	if (m_eCurAtiveState == PLAYERSTATE::MOVE)
	{
		m_bIsAnimStay = true;
		m_animStayTime = 0.3f;
	}
}

void CPlayer::CommandCheck()
{
	switch (m_ePevState)
	{
	case PLAYERSTATE::MOVE:
		m_eCurCommand = COMMANDKEY::DASH;
		break;
	default:
		break;
	}
}

void CPlayer::CommandSave(PLAYERSTATE key)
{
	m_ePevState = key;
	m_commandStayTime = g_fCommandTime;
}


CPlayer::CPlayer()
{
	m_commandStayTime = g_fCommandTime;
	m_bIsAnimStay = false;
	m_animStayTime = 0;
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
	m_wAnimKey[2]->push_back(L"QuickStop");
	m_wAnimKey[3]->push_back(L"DownSlide");
	m_wAnimKey[4]->push_back(L"Jump");
	m_wAnimKey[5]->push_back(L"Eat");
	m_wAnimKey[6]->push_back(L"Up");
	m_wAnimKey[7]->push_back(L"UpIdle");
	m_wAnimKey[7]->push_back(L"UpMove");
	m_wAnimKey[8]->push_back(L"InHale");


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
		m_wAnimKey[2]->at(0),
		m_pImg[2],
		fPoint(0.f, 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(pixelSize, 0.f), 0.1f, 8);

	GetAnimator()->CreateAnimation(
		m_wAnimKey[2]->at(1),
		m_pImg[2],
		fPoint((float)(pixelSize * 8), 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(pixelSize, 0.f), 0.5f, 1);

	GetAnimator()->CreateAnimation(
		m_wAnimKey[7]->at(0),
		m_pImg[7],
		fPoint(0.f, 0.f),
		fPoint(pixelSize, pixelSize),
		fPoint(pixelSize, 0.f), 0.1f, 2);

	GetAnimator()->CreateAnimation(
		m_wAnimKey[7]->at(1),
		m_pImg[7],
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
	pIdle->SetUpdageCallBack(&CPlayer::PlayerIdle, 0, 0);
	CStateManager::getInst()->AddState(PLAYERSTATE::IDLE, pIdle);
	CState* pMove = new CState(this);
	pMove->SetUpdageCallBack(&CPlayer::PlayerMove, 0, 0);
	CStateManager::getInst()->AddState(PLAYERSTATE::MOVE, pMove);

	CState* pLEFT = new CState(this);
	pLEFT->SetUpdageCallBack(&CPlayer::PlayerLeft, 0, 0);
	pLEFT->SetEnterCallBack(&CPlayer::PlayerChangeDir, 0, 0);
	CStateManager::getInst()->AddState(PLAYERSTATE::LEFT, pLEFT);
	CState* pRIGHT = new CState(this);
	pRIGHT->SetUpdageCallBack(&CPlayer::PlayerRight, 0, 0);
	pRIGHT->SetEnterCallBack(&CPlayer::PlayerChangeDir, 0, 0);
	CStateManager::getInst()->AddState(PLAYERSTATE::RIGHT, pRIGHT);
	CState* pInHale = new CState(this);
	pInHale->SetUpdageCallBack(&CPlayer::PlayerInHale, 0, 0);
	CStateManager::getInst()->AddState(PLAYERSTATE::INHALE, pInHale);

	m_eCurAtiveState = PLAYERSTATE::IDLE;
	m_eDirState = PLAYERSTATE::RIGHT;
	m_ePevState = PLAYERSTATE::END;
	m_eCurCommand = COMMANDKEY::END;
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
	if (m_ePevState != PLAYERSTATE::END)
	{
		m_commandStayTime -= fDT;
		if (m_commandStayTime <= 0)
		{
			m_ePevState = PLAYERSTATE::END;
			m_commandStayTime = g_fCommandTime;
		}
	}

	if (LEFTDEFINE || RIGHTDEFINE)
	{
		Key(VK_LEFT) ? CStateManager::getInst()->ChangeState(PLAYERSTATE::LEFT, m_eDirState) : CStateManager::getInst()->ChangeState(PLAYERSTATE::RIGHT, m_eDirState);
		CStateManager::getInst()->ChangeState(PLAYERSTATE::MOVE, m_eCurAtiveState);
	}
	if (ACTTACKDEFINE)
	{
		CStateManager::getInst()->ChangeState(PLAYERSTATE::INHALE, m_eCurAtiveState);
	}
	if (KEYEMPTYDEFINE)
	{
		CStateManager::getInst()->ChangeState(PLAYERSTATE::IDLE, m_eCurAtiveState);
	}

	CStateManager::getInst()->FindState(m_eDirState)->update();
	CStateManager::getInst()->FindState(m_eCurAtiveState)->update();
	/*
	m_eDirState->update();
	m_eCurAtiveState->update();
	*/
	GetAnimator()->update();
}

void CPlayer::render()
{
	component_render();
}