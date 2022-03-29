#include "framework.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "CAttackObj.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"
#include "CMonster.h"
#include "CScene.h"

#define INF 99999.f

CAttackObj::CAttackObj()
{
	SetName(L"AttackObj");
	m_eMoveType = MOVETYPE::END;
	m_fDelateRange = 0;
	m_pPlayer = CStateManager::getInst()->GetPlayer();

	SetScale(m_pPlayer->GetCollider()->GetScale());
	CreateCollider();
	CreateAnimator();
	CD2DImage* pImg = CResourceManager::getInst()->
		LoadD2DImage(L"CutterPAtk", L"texture\\Animation\\CutterWeapon.png");
	wstring keepPath = CPathManager::getInst()->GetContentPath();
	wstring path = keepPath;
	path += L"anim\\CWeapon.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	pImg = CResourceManager::getInst()->
		LoadD2DImage(L"UpPAtk", L"anim\\UpAttack.png");
	path = keepPath;
	path += L"anim\\UpAttack.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);

	CreateRigidBody();
	CRigidBody* rigid = GetRigidBody();
	rigid->SetMass(1);

	m_pImgEffect[(int)EFFECT_TYPE::NINHALE0] = CResourceManager::getInst()->
		LoadD2DImage(L"CutterPAtk", L"texture\\Effect\\0.png"); 
	m_pImgEffect[(int)EFFECT_TYPE::NINHALE1] = CResourceManager::getInst()->
		LoadD2DImage(L"CutterPAtk", L"texture\\Effect\\1.png");

	// 나중에 애니메이션 시간 잴 일 있으면 쓰기
	nomalanimtime = 0;
	nomalanimKeeptime = nomalanimtime;
	SetDead();
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

void CAttackObj::SetDelateRange(float range)
{
	m_fDelateRange = range;
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
	if (nullptr != CStateManager::getInst()->FindPlayeState(PLAYERSTATE::EAT))
	{
		m_eMoveType = MOVETYPE::VARIANCE;
		GetCollider()->SetScale(fPoint(16.f, 16.f));
		GetCollider()->SetOffsetPos(fPoint(m_fDir.x * (m_pPlayer->GetCollider()->GetScale() / 2).x, 0.f));
		GetRigidBody()->SetMaxPositiveVelocity(fPoint(200.f, 75.f));
		GetRigidBody()->SetMaxNegativeVelocity(fPoint(-200.f, -75.f));
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
		int a = 1;
		int b = 1;
		int c = 1;
		// TODO : 이거 나중에하자 시간 너무 잡아먹겠다
		for (int i = 1; i < GetCollider()->GetScale().x / 10; ++i)
		{
			c = a;
			a += b;
			b = c;
			m_aEffect.push_back(a);
		}
	}
}

void CAttackObj::CutterSetting()
{
	m_eMoveType = MOVETYPE::VARIANCE;
	SetScale(m_pPlayer->GetCollider()->GetScale() * 2.f);
	GetCollider()->SetScale(fPoint(16.f, 16.f));
	GetCollider()->SetOffsetPos(fPoint(0, 0.f));
	GetRigidBody()->SetMaxPositiveVelocity(fPoint(200.f, 75.f));
	GetRigidBody()->SetMaxNegativeVelocity(fPoint(-200.f, -75.f));
	SetReverceVelocity(5.f);
	SetRange(fPoint(m_fDir.x * 15.f, 0.f));
	SetDelateRange(WINSIZEX / 2.f);

	SetStartPos(GetPos());
	SetVelocity(30.f);
}

void CAttackObj::ThrowSetting()
{
	if (m_pPlayer->GetAnimator()->GetCurAnim()->GetName() == L"TAttackSet")
	{
		m_eMoveType = MOVETYPE::FIX;
		GetCollider()->SetScale(fPoint(80.f, 64.f));
		GetCollider()->SetOffsetPos(fPoint(m_fDir.x * (40.f + (m_pPlayer->GetCollider()->GetScale() / 2).x), 0.f));
	}
	else if (m_pPlayer->GetAnimator()->GetCurAnim()->GetName() == L"TAttackSet1")
	{
		m_eMoveType = MOVETYPE::FIX;
		GetCollider()->SetScale(fPoint(32.f, 32.f));
	}
	else
	{
		m_eMoveType = MOVETYPE::VARIANCE;
		GetCollider()->SetScale(fPoint(16.f, 16.f));
		GetCollider()->SetOffsetPos(fPoint(m_fDir.x * (m_pPlayer->GetCollider()->GetScale() / 2).x, 0.f));
		GetRigidBody()->SetMaxPositiveVelocity(fPoint(200.f, 75.f));
		GetRigidBody()->SetMaxNegativeVelocity(fPoint(-200.f, -75.f));
		SetReverceVelocity(50.f);
		SetRange(fPoint(m_fDir.x * INF, 0.f));
		SetStartPos(GetPos());
		SetVelocity(30.f);
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
		switch (m_pPlayer->GetAttackType())
		{
		case ATTACK_TYPE::NORMAL:
		{
		}
		case ATTACK_TYPE::CUTTER:
		{
		}
		case ATTACK_TYPE::THROW:
		{
			int dir = 0;
			if (GetRigidBody()->GetDir().x > 0)
				dir = 1;
			else if (GetRigidBody()->GetDir().x < 0)
				dir = -1;
			float realDis = abs((GetPos() - m_fStartPos).Length());
			float range = abs(m_fRange.Length());
			if ((dir != 0) && (m_fDir.x != dir))
			{
				if (realDis >= abs(m_fDelateRange))
					Exit();
				else
					GetRigidBody()->AddVelocity(fPoint(m_fDir.x * -m_fReverceVelocity, 0));
			}
			else
			{
				if (realDis >= range)
				{
					GetRigidBody()->AddVelocity(fPoint(m_fDir.x * -m_fReverceVelocity, 0));
				}
				else
					GetRigidBody()->AddVelocity(fPoint(m_fDir.x * m_fVelocity, 0));

				if (Key('C'))
				{
					if (realDis <= 5 * range)
					{
						GetRigidBody()->AddVelocity(fPoint(m_fDir.x * m_fVelocity, 0));
					}
					if (Key(VK_UP))
						GetRigidBody()->AddForce(fPoint(0, -200.f));
					else if (Key(VK_DOWN))
						GetRigidBody()->AddForce(fPoint(0, 200.f));
				}
			}
		}
		break;
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

MOVETYPE CAttackObj::GetMoveType()
{
	return m_eMoveType;
}

void CAttackObj::Enter()
{
	SetLive();
	
	m_pPlayer->GetDir() ?
		m_fDir = fPoint(1, 0) :
		m_fDir = fPoint(-1, 0);
	GetRigidBody()->SetVelocity(fPoint(0, 0));

	SetPos(m_pPlayer->GetCollider()->GetFinalPos());
	if (CStateManager::getInst()->FindPlayeState(PLAYERSTATE::FLY))
	{
		m_eMoveType = MOVETYPE::VARIANCE;
		SetScale(fPoint(32.f, 32.f));
		GetCollider()->SetScale(fPoint(16.f, 16.f));
		GetCollider()->SetOffsetPos(fPoint( 0.f, 0.f));
		GetRigidBody()->SetMaxPositiveVelocity(fPoint(200.f, 75.f));
		GetRigidBody()->SetMaxNegativeVelocity(fPoint(-200.f, -75.f));
		SetReverceVelocity(50.f);
		SetRange(fPoint(m_fDir.x * 60.f, 0.f));
		SetDelateRange(0.f);
		SetStartPos(GetPos());
		SetVelocity(30.f);
	}
	else if (CStateManager::getInst()->FindPlayeState(PLAYERSTATE::DOWN))
	{
		m_eMoveType = MOVETYPE::FIX;
		GetCollider()->SetScale(fPoint((m_pPlayer->GetCollider()->GetScale().x) / 2.f, 16.f));
		GetCollider()->SetOffsetPos(fPoint(m_fDir.x * (m_pPlayer->GetCollider()->GetScale().x) / 4.f, 0.f));
	}
	else
	{
		switch (m_pPlayer->GetAttackType())
		{
		case ATTACK_TYPE::NORMAL:
		{
			NomalSetting();
		}
		break;
		case ATTACK_TYPE::CUTTER:
		{
			CutterSetting();
		}
		break;
		case ATTACK_TYPE::THROW:
		{
			ThrowSetting();
		}
		break;
		default:
			break;
		}
	}

}

void CAttackObj::Exit()
{
	if (0 != m_aEffect.size())
		m_aEffect.clear();
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
	if (0 == m_fDelateRange && m_eMoveType == MOVETYPE::VARIANCE)
	{
		GetAnimator()->Play(L"UpAttack");
	}
	else
	{
		switch (m_pPlayer->GetAttackType())
		{
		case ATTACK_TYPE::NORMAL:
			NommalRender();
			break;
		case ATTACK_TYPE::CUTTER:
			CutterRender();
			break;
		case ATTACK_TYPE::THROW:
			ThrowRender();
			break;
		case ATTACK_TYPE::SIZE:
			break;
		default:
			break;
		}
	}

	component_render();
}

void CAttackObj::NommalRender()
{
	if (0 != m_aEffect.size())
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
}

void CAttackObj::CutterRender()
{
	GetAnimator()->Play(L"CWeapon");
}

void CAttackObj::ThrowRender()
{
	if (m_pPlayer->GetAnimator()->GetCurAnim()->GetName() == L"TAttackSet0")
		GetAnimator()->Play(L"CWeapon");
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
			case ATTACK_TYPE::CUTTER:
			{
				monster->SetDead();
				Exit();
			}
				break;
			case ATTACK_TYPE::THROW:
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
