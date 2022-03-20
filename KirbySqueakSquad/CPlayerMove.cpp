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
					if (1 >= abs(playerX - groundX) && 1 <= abs(playerY - groundY))
					{
						stateMove->SetCrushWallTile(true);
					}
				}
				else
				{
					playerX = player->GetCollider()->GetLeftPos().x;
					groundX = other->GetRightPos().x;
				}
			}
		}
	}
}


CPlayerMove::CPlayerMove()
{
	m_pPlayer->SetCollisonCallBack(OnMoveCollison, (DWORD_PTR)this);
	m_eState = PLAYERSTATE::MOVE;
	m_eCurCommand = COMMANDMOVE::NONE;
	m_ePrevCommand = m_eCurCommand;
	m_fAnimStayTime = m_eInfo.m_fMoveInertia;
	m_fAccel = 0;
	m_fStateStayTime = 0.1f;
	m_bIsDash = false;
	m_bIsStop = false;
	m_bStartDir = true;
	m_bIsDirChange = false;
	m_bIsCrushWallTile = false;
}

CPlayerMove::~CPlayerMove()
{

}

void CPlayerMove::Stay()
{
	if (m_fStateStayTime >= 0)
		m_fStateStayTime -= fDT;
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
	Stay();
	if (m_fStateStayTime <= 0)
	{
		if (m_bIsCrushWallTile)
		{
			Exit(PLAYERSTATE::IDLE);
		}
		else
		{
			KeyUpdate();
		}
	Move();
	}
}



void CPlayerMove::Move()
{	
	fPoint pos = m_pPlayer->GetPos();
	int dir = m_pPlayer->GetDir() ? 1 : -1;

	pos.x += dir * m_eInfo.m_fVelocity * m_fAccel * fDT;

	if (0 <= pos.x && pos.x <= CCameraManager::getInst()->GetDisLimmit().x)
	{
		m_pPlayer->SetPos(pos);
	}	
}


void CPlayerMove::Anim()
{
	if (m_fStateStayTime <= 0)
	{
		if (!m_bIsCrushWallTile)
		{
			m_pPlayer->GetAnimator()->SetReverce(!m_bStartDir);
			switch (m_eCurCommand)
			{
			case CPlayerMove::COMMANDMOVE::NONE:
				m_pPlayer->GetAnimator()->Play(L"Move");
				m_fAccel = 1;
				break;
			case CPlayerMove::COMMANDMOVE::DASH:
				m_pPlayer->GetAnimator()->Play(L"Dash");
				m_fAccel = m_eInfo.g_fAccel;
				break;
			case CPlayerMove::COMMANDMOVE::CHANGEDIR:
				m_pPlayer->GetAnimator()->Play(L"QuickStop");
				m_fAnimStayTime -= fDT;
				m_fAccel = m_fAnimStayTime;
				if (0 >= m_fAnimStayTime)
				{
					m_fAnimStayTime = 0;
					m_bStartDir = m_pPlayer->GetDir();
					m_bIsDash ? m_eCurCommand = COMMANDMOVE::DASH : m_eCurCommand = COMMANDMOVE::NONE;
				}
				break;
			case CPlayerMove::COMMANDMOVE::TURNOFF:
				m_fAnimStayTime -= fDT;
				m_fAccel = m_fAnimStayTime;
				if (0 >= m_fAnimStayTime)
				{
					m_fAnimStayTime = 0;
					Exit(PLAYERSTATE::IDLE);
				}
				break;
			case CPlayerMove::COMMANDMOVE::END:
				break;
			default:
				break;
			}
		}
	}
}

void CPlayerMove::SetCrushWallTile(bool isCrush)
{
	m_bIsCrushWallTile = isCrush;
}



void CPlayerMove::Enter()
{
	m_eCurCommand = COMMANDMOVE::NONE;
	m_ePrevCommand = m_eCurCommand;
	m_fAnimStayTime = m_eInfo.m_fMoveInertia;
	m_bStartDir = m_pPlayer->GetDir();
	m_fAccel = 1;
	m_fStateStayTime = 0.1f;
	m_bIsDash = false;
	m_bIsStop = false;
	m_bIsDirChange = false;
	m_bIsActive = true;
	m_bIsCrushWallTile = false;
}

void CPlayerMove::Exit(PLAYERSTATE state)
{
	m_bIsActive = false;
	CEventManager::getInst()->EventLoadPlayerState(state);
	CStateManager::getInst()->ExitState(m_eState);
}