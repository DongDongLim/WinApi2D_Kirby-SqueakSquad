#include "framework.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "CAttackObj.h"
#include "CAnimator.h"
#include "CRigidBody.h"
#include "CMonster.h"

CAttackObj::CAttackObj()
{
	SetName(L"AttackObj");

	m_pPlayer = CStateManager::getInst()->GetPlayer();

	SetScale(m_pPlayer->GetCollider()->GetScale());

	CreateCollider();

	CreateRigidBody();
	CRigidBody* rigid = GetRigidBody();
	rigid->SetMass(1);
}

CAttackObj::~CAttackObj()
{
}

CAttackObj* CAttackObj::Clone()
{
	return new CAttackObj();
}

void CAttackObj::SetRange(fPoint range)
{
	m_fRange = range;
}

void CAttackObj::NomalSetting()
{

}

void CAttackObj::Enter()
{
	m_bIsActivity = true;

	
	m_pPlayer->GetDir() ?
		m_fDir = fPoint(1, 0) :
		m_fDir = fPoint(-1, 0);

	SetPos(m_pPlayer->GetCollider()->GetFinalPos());

	switch (m_pPlayer->GetAttackType())
	{
	case ATTACK_TYPE::NORMAL:
	{
		GetCollider()->SetScale(fPoint(80.f, 64.f));
		GetCollider()->SetOffsetPos(fPoint(m_fDir.x * (40.f + (m_pPlayer->GetCollider()->GetScale() / 2).x), 0.f));
	}
	break;
	default:
		break;
	}
}

void CAttackObj::Exit()
{
	m_bIsActivity = false;
}




void CAttackObj::update()
{
	if (m_bIsActivity)
	{
		SetPos(m_pPlayer->GetCollider()->GetFinalPos());

		if (nullptr != GetAnimator())
			GetAnimator()->update();
	}
}

void CAttackObj::render()
{
	if (m_bIsActivity)
	{
		if (m_pPlayer->GetAttackType() == ATTACK_TYPE::NORMAL)
		{
			fPoint pos = GetCollider()->GetFinalPos();
			fPoint scale = GetCollider()->GetScale();
			pos = CCameraManager::getInst()->GetRenderPos(pos);

			COLORREF rgb = RGB(0, 0, 0);

			rgb = RGB(255, 255, 255);


			CRenderManager::getInst()->RenderRectangle(
				pos.x - scale.x / 2,
				pos.y - m_fRange.y / 2.f,
				pos.x + m_fRange.x / 2.f,
				pos.y + m_fRange.y / 2.f,
				rgb);
		}

		component_render();
	}
}

void CAttackObj::finalupdate()
{
	if (m_bIsActivity)
	{
		if (nullptr != GetRigidBody())
		{
			GetRigidBody()->finalupdate();
		}
		if (nullptr != GetCollider())
		{
			GetCollider()->finalupdate();
		}
	}
}

void CAttackObj::OnCollision(CCollider* _pOther)
{
	CGameObject* owner = _pOther->GetObj();
	if (owner->GetGroup() == GROUP_GAMEOBJ::MONSTER)
	{
		CMonster* monster = (CMonster*)owner;
		if (!monster->GetIsEaten())
		{
			switch (m_pPlayer->GetAttackType())
			{
			case ATTACK_TYPE::NORMAL:
			{
				float lengthX = abs(_pOther->GetFinalPos().x
					- GetPos().x) - _pOther->GetScale().x;
				float lengthY = abs(_pOther->GetFinalPos().y
					- GetPos().y) - _pOther->GetScale().y;
				if (m_fRange.x >= lengthX && m_fRange.y >= lengthY)
				{
					monster->SetEaten(true);
					Exit();
				}
			}
			break;
			default:
				break;
			}
		}
	}
}
