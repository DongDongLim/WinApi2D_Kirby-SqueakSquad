#include "framework.h"
#include "CPlayerState.h"
#include "CStateManager.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CTile.h"
#include "CAnimator.h"

void OnCollisonEnter(DWORD_PTR state, CCollider* other)
{
	if (((CPlayerMove*)state)->GetIsActive())
	{
		CGameObject* pOtherObj = other->GetObj();
		if (pOtherObj->GetGroup() == GROUP_GAMEOBJ::TILE)
		{
			if (((CTile*)pOtherObj)->GetGroup() == GROUP_TILE::GROUND)
			{
				((CPlayerFall*)state)->SetTarget(CPlayerFall::COLLIONTARGET::GROUND);
			}

		}
	}
}


CPlayerFall::CPlayerFall()
{
	m_eState = PLAYERSTATE::Fall;
	m_fGravity = 50.f;
	m_eTarget = COLLIONTARGET::END;
	m_pPlayer->SetCollisonEnterCallBack(OnCollisonEnter, (DWORD_PTR)this);
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
	fPoint pos = m_pPlayer->GetPos();
	switch (m_eTarget)
	{
	case CPlayerFall::COLLIONTARGET::GROUND:
		Exit(PLAYERSTATE::IDLE);
		break;
	case CPlayerFall::COLLIONTARGET::MON:
		break;
	case CPlayerFall::COLLIONTARGET::END:
		pos += fPoint(0, m_fGravity) * fDT;
		break;
	default:
		break;
	}
	m_pPlayer->SetPos(pos);
}

void CPlayerFall::Enter()
{
	m_fGravity = 50.f;
	m_eTarget = COLLIONTARGET::END;
	m_pPlayer->GetAnimator()->Play(L"Fall0");
	m_bIsActive = true;

}

void CPlayerFall::Exit(PLAYERSTATE state)
{
	m_bIsActive = false;
	CEventManager::getInst()->EventLoadPlayerState(state);
	CStateManager::getInst()->ExitState(m_eState);	
}