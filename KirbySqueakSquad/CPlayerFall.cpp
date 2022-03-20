#include "framework.h"
#include "CPlayerState.h"
#include "CStateManager.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CTile.h"
#include "CAnimator.h"
#include "CGravity.h"

void OnFallCollisonEnter(DWORD_PTR state, CCollider* other)
{
	if (((CPlayerMove*)state)->GetIsActive())
	{
		CGameObject* pOtherObj = other->GetObj();
		if (pOtherObj->GetGroup() == GROUP_GAMEOBJ::TILE)
		{
			if (((CTile*)pOtherObj)->GetGroup() == GROUP_TILE::GROUND)
			{
				float playerY = CStateManager::getInst()->GetPlayer()->GetCollider()->GetDownPos().y;
				float groundY = other->GetUpPos().y;
				if (1 >= abs(playerY - groundY))
					((CPlayerFall*)state)->SetTarget(CPlayerFall::COLLIONTARGET::GROUND);
			}

		}
	}
}


CPlayerFall::CPlayerFall()
{
	m_eState = PLAYERSTATE::Fall;
	m_fGravity = m_eInfo.m_fVerticalSpeed;
	m_eTarget = COLLIONTARGET::END;
	//m_pPlayer->SetCollisonEnterCallBack(OnFallCollisonEnter, (DWORD_PTR)this);
}

CPlayerFall::~CPlayerFall()
{

}

void CPlayerFall::SetTarget(COLLIONTARGET target)
{
	m_eTarget = target;
}


void CPlayerFall::update()
{
	if(m_pPlayer->GetGravity()->GetIsGround())
		Exit(PLAYERSTATE::IDLE);
	
	//fPoint pos = m_pPlayer->GetPos();
	//switch (m_eTarget)
	//{
	//case CPlayerFall::COLLIONTARGET::GROUND:
	//	Exit(PLAYERSTATE::IDLE);
	//	break;
	//case CPlayerFall::COLLIONTARGET::MON:
	//	break;
	//case CPlayerFall::COLLIONTARGET::END:
	//	//pos += fPoint(0, m_fGravity) * fDT;
	//	break;
	//default:
	//	break;
	//}
	//m_pPlayer->SetPos(pos);
}

void CPlayerFall::Anim()
{
	m_pPlayer->GetAnimator()->SetReverce(!m_pPlayer->GetDir());
	m_pPlayer->GetAnimator()->Play(L"Fall0");
}

void CPlayerFall::Enter()
{
	m_eTarget = COLLIONTARGET::END;
	m_bIsActive = true;
}

void CPlayerFall::Exit(PLAYERSTATE state)
{
	m_bIsActive = false;
	CEventManager::getInst()->EventLoadPlayerState(state);
	CStateManager::getInst()->ExitState(m_eState);	
}