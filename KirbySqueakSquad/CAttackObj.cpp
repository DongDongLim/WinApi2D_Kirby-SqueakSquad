#include "framework.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "CAttackObj.h"
#include "CAnimator.h"
#include "CRigidBody.h"
#include "CMonster.h"

#define INF 99999.f

CAttackObj::CAttackObj()
{
	SetName(L"AttackObj");
	m_eMoveType = MOVETYPE::END;

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

void CAttackObj::SetStartPos(fPoint range)
{
	m_fStartPos = range;
}

void CAttackObj::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}

void CAttackObj::SetReverceVelocity(float velocity)
{
	m_fReverceVelocity = velocity;
}

void CAttackObj::NomalSetting()
{
	if (CStateManager::getInst()->FindPlayeState(PLAYERSTATE::FLY))
	{
		m_eMoveType = MOVETYPE::VARIANCE;
		GetCollider()->SetScale(fPoint(16.f, 16.f));
		GetCollider()->SetOffsetPos(fPoint(m_fDir.x * (m_pPlayer->GetCollider()->GetScale() / 2).x, 0.f));
		SetReverceVelocity(50.f);
		SetRange(fPoint(m_fDir.x * 15.f, 0.f));
		SetStartPos(GetPos());
		SetVelocity(30.f);
	}
	else if (CStateManager::getInst()->FindPlayeState(PLAYERSTATE::DOWN))
	{
		m_eMoveType = MOVETYPE::FIX;
		GetCollider()->SetScale(fPoint((m_pPlayer->GetCollider()->GetScale().x)/2.f, 16.f));
		GetCollider()->SetOffsetPos(fPoint(m_fDir.x * (m_pPlayer->GetCollider()->GetScale().x) / 4.f, 0.f));
	}
	else if (CStateManager::getInst()->FindPlayeState(PLAYERSTATE::EAT))
	{
		m_eMoveType = MOVETYPE::VARIANCE;
		GetCollider()->SetScale(fPoint(16.f, 16.f));
		GetCollider()->SetOffsetPos(fPoint(m_fDir.x * (m_pPlayer->GetCollider()->GetScale() / 2).x, 0.f));
		SetReverceVelocity(50.f);
		SetRange(fPoint(m_fDir.x * INF, 0.f));
		SetStartPos(GetPos());
		SetVelocity(30.f);
	}
	else
	{
		m_eMoveType = MOVETYPE::FIX;
		GetCollider()->SetScale(fPoint(80.f, 64.f));
		GetCollider()->SetOffsetPos(fPoint(m_fDir.x * (40.f + (m_pPlayer->GetCollider()->GetScale() / 2).x), 0.f));
	}
}

void CAttackObj::MoveUpdate()
{
	switch (m_eMoveType)
	{
	case MOVETYPE::FIX:
		SetPos(m_pPlayer->GetCollider()->GetFinalPos());
		break;
	case MOVETYPE::VARIANCE:
		GetRigidBody()->AddVelocity(m_fDir * m_fVelocity);
		switch (m_pPlayer->GetAttackType())
		{
		case ATTACK_TYPE::NORMAL:
		{
			if (abs((GetPos() - m_fStartPos).Length()) > abs(m_fRange.Length()))
				GetRigidBody()->AddVelocity(m_fDir * -m_fReverceVelocity);
			int dir = 0;
			GetRigidBody()->GetDir().x > 0.f ? dir = 1 : dir = -1;
			if ((dir != 0) && (m_fDir.x != dir))
			{
				Exit();
			}
			break;
		}
		default:
			break;
		}
		break;
	case MOVETYPE::END:
		break;
	default:
		break;
	}
}

void CAttackObj::Enter()
{
	SetLive();
	
	m_pPlayer->GetDir() ?
		m_fDir = fPoint(1, 0) :
		m_fDir = fPoint(-1, 0);

	SetPos(m_pPlayer->GetCollider()->GetFinalPos());

	switch (m_pPlayer->GetAttackType())
	{
	case ATTACK_TYPE::NORMAL:
	{
		NomalSetting();
	}
	break;
	default:
		break;
	}
}

void CAttackObj::Exit()
{
	SetDead();
}




void CAttackObj::update()
{
	MoveUpdate();

	if (nullptr != GetAnimator())
		GetAnimator()->update();
}

void CAttackObj::render()
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

void CAttackObj::finalupdate()
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
				if (GetCollider()->GetScale().x == 80.f)
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
				else
				{
					monster->SetDead();
					Exit();
				}
			}
			break;
			default:
				break;
			}
		}
	}
	else if (owner->GetGroup() == GROUP_GAMEOBJ::TILE)
	{
		if (m_fRange.x == INF)
			Exit();
	}
}
