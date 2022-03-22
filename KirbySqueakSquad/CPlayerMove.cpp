#pragma once
#include "framework.h"
#include "CPlayerState.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CTile.h"
#include "CGravity.h"


void OnMoveCollison(DWORD_PTR state, CCollider* other)
{
	CPlayerMove* stateMove = (CPlayerMove*)state;
	if (stateMove->GetIsActive())
	{
		CGameObject* pOtherObj = other->GetObj();
		if (pOtherObj->GetGroup() == GROUP_GAMEOBJ::TILE)
		{
			if (((CTile*)pOtherObj)->GetGroup() == GROUP_TILE::GROUND)
			{
				CPlayer* player = CStateManager::getInst()->GetPlayer();
				float playerX;
				float groundX;
				float playerY;
				float groundY;
				playerY = player->GetCollider()->GetDownPos().y;
				groundY = other->GetUpPos().y;
				if (player->GetDir())
				{
					playerX = player->GetCollider()->GetRightPos().x;
					groundX = other->GetLeftPos().x;
				}
				else
				{
					playerX = player->GetCollider()->GetLeftPos().x;
					groundX = other->GetRightPos().x;
				}
				if (1 >= abs(playerX - groundX) && 1 <= abs(playerY - groundY))
				{
					player->GetRigidBody()->SetVelocity(fPoint(0, player->GetRigidBody()->GetVelocity().y));
					stateMove->Exit(PLAYERSTATE::IDLE);
				}
			}
		}
	}
}


CPlayerMove::CPlayerMove()
{
	//m_pPlayer->SetCollisonCallBack(OnMoveCollison, (DWORD_PTR)this);
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
	}
}

void CPlayerMove::update()
{
	KeyUpdate();
	Move();
}



void CPlayerMove::Move()
{	
	fPoint pos = m_pPlayer->GetPos();
	m_dir = m_bStartDir ? 1 : -1;

	switch (m_eCurCommand)
	{
	case CPlayerMove::COMMANDMOVE::NONE:
		if (m_pPlayer->GetGravity()->GetIsGround())
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
		
		if (m_fAnimStayTime > 0.2f)
		{
			m_bStartDir = m_pPlayer->GetDir();
			m_bIsDash ? m_eCurCommand = COMMANDMOVE::DASH : m_eCurCommand = COMMANDMOVE::NONE;
		}
		/*
		// TODO: ���� ������ �ٲٱ�
		if ((m_dir > 0 && m_dir > m_pPlayer->GetRigidBody()->GetVelocity().x)
			|| (m_dir < 0 && m_dir < m_pPlayer->GetRigidBody()->GetVelocity().x))
		{
			m_bStartDir = m_pPlayer->GetDir();
			m_bIsDash ? m_eCurCommand = COMMANDMOVE::DASH : m_eCurCommand = COMMANDMOVE::NONE;
		}
		*/
		break;
	case CPlayerMove::COMMANDMOVE::TURNOFF:
		if (nullptr != CStateManager::getInst()->FindPlayeState(PLAYERSTATE::Fall))
		{
			//Exit(PLAYERSTATE::IDLE);
		}
		else
		{
			m_fAnimStayTime += fDT;
			m_bStartDir ? m_pPlayer->GetRigidBody()->AddVelocity(fPoint(-m_fAnimStayTime, 0))
				: m_pPlayer->GetRigidBody()->AddVelocity(fPoint(m_fAnimStayTime,0));

			if (m_fAnimStayTime > 0.2f)
			{
				m_pPlayer->GetRigidBody()->SetVelocity(fPoint(0, 0));
				Exit(PLAYERSTATE::IDLE);
			}

			/* �ӽ÷� �ٲ�ߵʤФ�
			// TODO: ���� ������ �ٲٱ�
			if ((m_dir > 0 && m_dir > m_pPlayer->GetRigidBody()->GetVelocity().x)
				|| (m_dir < 0 && m_dir < m_pPlayer->GetRigidBody()->GetVelocity().x))
			{
				//m_bStartDir = m_pPlayer->GetDir();
				m_pPlayer->GetRigidBody()->SetVelocity(fPoint(0, 0));
				Exit(PLAYERSTATE::IDLE);
			}
			*/
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
	CEventManager::getInst()->EventLoadPlayerState(state);
	CStateManager::getInst()->ExitState(m_eState);
}