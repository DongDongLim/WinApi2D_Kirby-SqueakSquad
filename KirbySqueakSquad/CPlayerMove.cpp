#pragma once
#include "framework.h"
#include "CPlayerState.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CTile.h"
#include "CGravity.h"

/* TODO :
	���߿� ���굵 �׽� �������� �ٲ㼭 ���⼭ �ӵ��� 0�̸� idle �ִϸ��̼� ����޵��� �ؾ߰ڴ� �׷� idle �����Լ��� ���ĵ� ����������..?
*/

CPlayerMove::CPlayerMove()
{
	m_eState = PLAYERSTATE::MOVE;
	m_eCurCommand = COMMANDMOVE::NONE;
	m_ePrevCommand = m_eCurCommand;
	m_fAnimStayTime = m_eInfo.m_fMoveInertia;
	m_bIsDash = false;
	m_bIsStop = false;
	m_bStartDir = true;
	m_bIsDirChange = false;
	m_dir = 0;
}

CPlayerMove::~CPlayerMove()
{

}

void CPlayerMove::KeyUpdate()
{
	if (KeyUp(VK_LEFT) || KeyUp(VK_RIGHT))
	{
		if (!Key(VK_LEFT) && !Key(VK_RIGHT))
		{
			if (COMMANDMOVE::TURNOFF != m_eCurCommand)
			{
				m_fAnimStayTime = m_eInfo.m_fMoveInertia;
				m_eCurCommand = COMMANDMOVE::TURNOFF;
			}
		}
	}
	// Ŀ�ǵ� �Է�
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
				m_fAnimStayTime = m_eInfo.m_fMoveInertia;
				m_eCurCommand = COMMANDMOVE::CHANGEDIR;
			}
		}
	}/*
	if (KeyDown('C'))
	{
		if (nullptr == CStateManager::getInst()->FindPlayeState(PLAYERSTATE::FLY))
		{
			if (m_pPlayer->GetGravity()->GetIsGround())
				m_pPlayer->GetRigidBody()->SetVelocity(fPoint(0, 0));
			Exit(PLAYERSTATE::ATTACK);
		}
	}*/
}

void CPlayerMove::update()
{
	Move();
	KeyUpdate();
}



void CPlayerMove::Move()
{	
	fPoint pos = m_pPlayer->GetPos();
	m_dir = m_bStartDir ? 1 : -1;

	if (m_dir == 1)
	{
		if(m_pPlayer->GetPlaeyrInfo().g_bIsRight)
			m_eCurCommand = COMMANDMOVE::IMPACT;
	}
	else
	{
		if (m_pPlayer->GetPlaeyrInfo().g_bIsLeft)
			m_eCurCommand = COMMANDMOVE::IMPACT;
	}

	switch (m_eCurCommand)
	{
	case CPlayerMove::COMMANDMOVE::NONE:
		if (nullptr != CStateManager::getInst()->FindPlayeState(PLAYERSTATE::JUMP)
			&& nullptr != CStateManager::getInst()->FindPlayeState(PLAYERSTATE::Fall))
		{
			m_pPlayer->GetRigidBody()->SetVelocity(fPoint(m_dir * m_eInfo.m_fVelocity,
				m_pPlayer->GetRigidBody()->GetVelocity().y));
		}
		else
		{
			m_pPlayer->GetRigidBody()->SetVelocity(fPoint(m_dir * m_eInfo.m_fVelocity * m_eInfo.g_fAccel,
				m_pPlayer->GetRigidBody()->GetVelocity().y));
		}
		break;
	case CPlayerMove::COMMANDMOVE::DASH:
		m_pPlayer->GetRigidBody()->SetVelocity(fPoint(m_dir * m_eInfo.m_fVelocity * m_eInfo.g_fAccel,
			m_pPlayer->GetRigidBody()->GetVelocity().y));
		break;
	case CPlayerMove::COMMANDMOVE::CHANGEDIR:
		
		m_fAnimStayTime += fDT;
		
		m_bStartDir ? m_pPlayer->GetRigidBody()->AddVelocity(fPoint(-m_fAnimStayTime, 0))
			: m_pPlayer->GetRigidBody()->AddVelocity(fPoint(m_fAnimStayTime, 0));
		
		
		// TODO: ���� ������ �ٲٱ�
		if ((m_dir > 0 && m_dir > m_pPlayer->GetRigidBody()->GetVelocity().x)
			|| (m_dir < 0 && m_dir < m_pPlayer->GetRigidBody()->GetVelocity().x))
		{
			m_bStartDir = m_pPlayer->GetDir();
			m_bIsDash ? m_eCurCommand = COMMANDMOVE::DASH : m_eCurCommand = COMMANDMOVE::NONE;
		}
		break;
	case CPlayerMove::COMMANDMOVE::TURNOFF:
		if ((nullptr != CStateManager::getInst()->FindPlayeState(PLAYERSTATE::Fall)))
		{
			if (m_pPlayer->GetGravity()->GetIsGround())
			{
				m_pPlayer->GetRigidBody()->SetVelocity(fPoint(0, 0));
				Exit(PLAYERSTATE::END);
			}

		}
		else if (nullptr != CStateManager::getInst()->FindPlayeState(PLAYERSTATE::JUMP))
		{
			//Exit(PLAYERSTATE::END);
		}
		else
		{
			m_fAnimStayTime += fDT;
			m_bStartDir ? m_pPlayer->GetRigidBody()->AddVelocity(fPoint(-m_fAnimStayTime, 0))
				: m_pPlayer->GetRigidBody()->AddVelocity(fPoint(m_fAnimStayTime,0));

			/*if (m_fAnimStayTime > 0.2f)
			{
				m_pPlayer->GetRigidBody()->SetVelocity(fPoint(0, 0));
				Exit(PLAYERSTATE::END);
			}*/

			// TODO: ���� ������ �ٲٱ�
			if ((m_dir > 0 && m_dir > m_pPlayer->GetRigidBody()->GetVelocity().x)
				|| (m_dir < 0 && m_dir < m_pPlayer->GetRigidBody()->GetVelocity().x))
			{
				//m_bStartDir = m_pPlayer->GetDir();
				m_pPlayer->GetRigidBody()->SetVelocity(fPoint(0, 0));
				Exit(PLAYERSTATE::END);
			}
		}
		break;
	case CPlayerMove::COMMANDMOVE::IMPACT:
		m_fAnimStayTime += fDT;
		if (m_fAnimStayTime > 0.2f)
		{
			m_pPlayer->GetRigidBody()->SetVelocity(fPoint(0, 0));
			Exit(PLAYERSTATE::END);
		}
		break;
	case CPlayerMove::COMMANDMOVE::END:
		break;
	default:
		break;
	}
}


void CPlayerMove::Anim()
{
	switch (m_eCurCommand)
	{
	case CPlayerMove::COMMANDMOVE::NONE:
		m_pPlayer->GetAnimator()->Play(L"Move");
		break;
	case CPlayerMove::COMMANDMOVE::DASH:
		m_pPlayer->GetAnimator()->Play(L"Dash");	
		break;
	case CPlayerMove::COMMANDMOVE::CHANGEDIR:
		m_pPlayer->GetAnimator()->SetReverce(m_pPlayer->GetDir());
		m_pPlayer->GetAnimator()->Play(L"QuickStop");
		break;
	case CPlayerMove::COMMANDMOVE::TURNOFF:
		break;
	case CPlayerMove::COMMANDMOVE::IMPACT:
		m_pPlayer->GetAnimator()->Play(L"WallImpact");
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
	m_fAnimStayTime = m_eInfo.m_fMoveInertia;
	m_bStartDir = m_pPlayer->GetDir();
	m_bIsDash = false;
	m_bIsStop = false;
	m_bIsDirChange = false;
	m_bIsActive = true;
	m_dir = 0;
}

void CPlayerMove::Exit(PLAYERSTATE state)
{
	m_bIsActive = false;
	if (state != PLAYERSTATE::END)
		CEventManager::getInst()->EventLoadPlayerState(state);
	CStateManager::getInst()->ExitState(m_eState);
}