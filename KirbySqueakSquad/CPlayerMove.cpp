#pragma once
#include "framework.h"
#include "CPlayerState.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CTile.h"


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
				m_fAnimStayTime = m_eInfo.m_fMoveInertia;
				m_eCurCommand = COMMANDMOVE::CHANGEDIR;
			}
		}
	}
	if (KeyDown('X') || KeyDown('V'))
	{
		CEventManager::getInst()->EventLoadPlayerState(PLAYERSTATE::JUMP);
	}
}

void CPlayerMove::update()
{
	if (m_pPlayer->GetIsWall()[0])
	{
		m_pPlayer->GetRigidBody()->SetVelocity(fPoint(0, m_pPlayer->GetRigidBody()->GetVelocity().y));
		Exit(PLAYERSTATE::IDLE);
	}
	else
	{
		KeyUpdate();
	}
	Move();
}



void CPlayerMove::Move()
{	
	fPoint pos = m_pPlayer->GetPos();
	int dir = m_pPlayer->GetDir() ? 1 : -1;

	//pos.x += dir * m_eInfo.m_fVelocity * m_fAccel * fDT;

	m_pPlayer->GetRigidBody()->AddForce(fPoint(dir * m_eInfo.m_fVelocity, m_pPlayer->GetRigidBody()->GetVelocity().y));
	/*
	if (0 <= pos.x && pos.x <= CCameraManager::getInst()->GetDisLimmit().x)
	{
		m_pPlayer->SetPos(pos);
	}
	*/
}


void CPlayerMove::Anim()
{
	m_pPlayer->GetAnimator()->SetReverce(!m_bStartDir);
	switch (m_eCurCommand)
	{
	case CPlayerMove::COMMANDMOVE::NONE:
		m_pPlayer->GetAnimator()->Play(L"Move");
		m_pPlayer->GetRigidBody()->SetMaxSpeed(m_eInfo.m_fMaxSpeed);
		break;
	case CPlayerMove::COMMANDMOVE::DASH:
		m_pPlayer->GetAnimator()->Play(L"Dash");
		m_pPlayer->GetRigidBody()->SetMaxSpeed(m_eInfo.m_fMaxSpeed * m_eInfo.g_fAccel);
		break;
	case CPlayerMove::COMMANDMOVE::CHANGEDIR:
		m_fAnimStayTime -= fDT;
		m_pPlayer->GetAnimator()->Play(L"QuickStop");
		m_bStartDir ? m_pPlayer->GetRigidBody()->SetVelocity(fPoint(0.f, m_pPlayer->GetRigidBody()->GetVelocity().y))
			: m_pPlayer->GetRigidBody()->SetVelocity(fPoint(0.f, m_pPlayer->GetRigidBody()->GetVelocity().y));
		if (0 >= m_fAnimStayTime)
		{
			m_fAnimStayTime = 0;
			m_bStartDir = m_pPlayer->GetDir();
			m_bIsDash ? m_eCurCommand = COMMANDMOVE::DASH : m_eCurCommand = COMMANDMOVE::NONE;
		}
		/*
		m_fAnimStayTime -= fDT;
		m_fAccel = m_fAnimStayTime;
		if (0 >= m_fAnimStayTime)
		{
			m_fAnimStayTime = 0;
			m_bStartDir = m_pPlayer->GetDir();
			m_bIsDash ? m_eCurCommand = COMMANDMOVE::DASH : m_eCurCommand = COMMANDMOVE::NONE;
		}
		*/
		break;
	case CPlayerMove::COMMANDMOVE::TURNOFF:
		m_fAnimStayTime -= fDT;
		m_bStartDir ? m_pPlayer->GetRigidBody()->SetVelocity(fPoint(m_fAnimStayTime * 50, m_pPlayer->GetRigidBody()->GetVelocity().y))
			: m_pPlayer->GetRigidBody()->SetVelocity(fPoint(m_fAnimStayTime * -50, m_pPlayer->GetRigidBody()->GetVelocity().y));
		if (0 >= m_fAnimStayTime)
		{
			m_fAnimStayTime = 0;
			Exit(PLAYERSTATE::IDLE);
		}
		/*
		m_fAccel = m_fAnimStayTime;
		if (0 >= m_fAnimStayTime)
		{
			m_fAnimStayTime = 0;
			Exit(PLAYERSTATE::IDLE);
		}
		*/
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
}

void CPlayerMove::Exit(PLAYERSTATE state)
{
	m_bIsActive = false;
	CEventManager::getInst()->EventLoadPlayerState(state);
	CStateManager::getInst()->ExitState(m_eState);
}