#pragma once
#include "framework.h"
#include "CPlayerState.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CPlayer.h"

CPlayerMove::CPlayerMove()
{
	m_eState = PLAYERSTATE::MOVE;
	m_eCurCommand = COMMANDMOVE::NONE;
	m_ePrevCommand = m_eCurCommand;
	m_animStayTime = m_eInfo.m_fMoveInertia;
	m_gfAccel = 0;
	m_bIsDash = false;
	m_bIsStop = false;
	m_bStartDir = true;
	m_bIsDirChange = false;
}

CPlayerMove::~CPlayerMove()
{

}

void CPlayerMove::update()
{
	if (KeyUp(VK_LEFT) || KeyUp(VK_RIGHT))
	{
		if (!Key(VK_LEFT) && !Key(VK_RIGHT))
		{
			if (COMMANDMOVE::TURNOFF != m_eCurCommand)
			{
				m_animStayTime = m_eInfo.m_fMoveInertia;
				m_eCurCommand = COMMANDMOVE::TURNOFF;
			}
		}
	}
	// 커맨드 입력
	if (KeyDown(VK_LEFT) || KeyDown(VK_RIGHT))
	{
		if (m_pPlayer->GetDir() == m_bStartDir)
		{
			if (COMMANDMOVE::DASH != m_eCurCommand)
			{
				m_bIsDash = true;
				m_eCurCommand = COMMANDMOVE::DASH;
			}
		}
		else
		{
			if (COMMANDMOVE::CHANGEDIR != m_eCurCommand)
			{
				m_animStayTime = m_eInfo.m_fMoveInertia;
				m_eCurCommand = COMMANDMOVE::CHANGEDIR;
			}
		}
	}

	Move();
	Anim();
}

void CPlayerMove::Move()
{
	fPoint pos = m_pPlayer->GetPos();
	int dir = m_pPlayer->GetDir() ? 1 : -1;

	pos.x += dir * m_eInfo.m_fVelocity * m_gfAccel * fDT;

	if (0 <= pos.x && pos.x <= CCameraManager::getInst()->GetDisLimmit().x)
		m_pPlayer->SetPos(pos);
}

void CPlayerMove::Anim()
{
	m_pPlayer->GetAnimator()->SetReverce(!m_bStartDir);
	switch (m_eCurCommand)
	{
	case CPlayerMove::COMMANDMOVE::NONE:
		m_pPlayer->GetAnimator()->Play(L"Move");
		m_gfAccel = 1;
		break;
	case CPlayerMove::COMMANDMOVE::DASH:
		m_pPlayer->GetAnimator()->Play(L"Dash");
		m_gfAccel = m_eInfo.g_fAccel;
		break;
	case CPlayerMove::COMMANDMOVE::CHANGEDIR:
		m_pPlayer->GetAnimator()->Play(L"QuickStop");
		m_animStayTime -= fDT;
		m_gfAccel = m_animStayTime;
		if (0 >= m_animStayTime)
		{
			m_animStayTime = 0;
			m_bStartDir = m_pPlayer->GetDir();
			m_bIsDash ? m_eCurCommand = COMMANDMOVE::DASH : m_eCurCommand = COMMANDMOVE::NONE;
		}
		break;
	case CPlayerMove::COMMANDMOVE::TURNOFF:
		m_animStayTime -= fDT;
		m_gfAccel = m_animStayTime;
		if (0 >= m_animStayTime)
		{
			m_animStayTime = 0;
			Exit(PLAYERSTATE::IDLE);
		}
		break;
	case CPlayerMove::COMMANDMOVE::END:
		break;
	default:
		break;
	}
}


void CPlayerMove::Enter()
{
	m_eCurCommand = COMMANDMOVE::NONE;
	m_ePrevCommand = m_eCurCommand;
	m_animStayTime = m_eInfo.m_fMoveInertia;
	m_bStartDir = m_pPlayer->GetDir();
	m_bIsDash = false;
	m_bIsStop = false;
	m_bIsDirChange = false;
	m_gfAccel = 1;
}

void CPlayerMove::Exit(PLAYERSTATE state)
{
	CEventManager::getInst()->EventLoadPlayerState(state);
	CStateManager::getInst()->ExitState(m_eState);
}