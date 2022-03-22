#pragma once
#include "framework.h"
#include "CPlayerState.h"
#include "CAnimator.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CTile.h"
#include "CGravity.h"



void OnIdleCollisonEnter(DWORD_PTR state, CCollider* other)
{
	if (other->GetObj()->GetGroup() == GROUP_GAMEOBJ::TILE)
	{
		CTile* tile = (CTile*)other->GetObj();
		if (tile->GetGroup() == GROUP_TILE::GROUND)
		{
			CPlayerIdle* idle = (CPlayerIdle*)state;
			idle->AddGroundCollider((CCollider*)other);
		}
	}
}


CPlayerIdle::CPlayerIdle()
{
	m_eState = PLAYERSTATE::IDLE;
	m_pPlayer->SetCollisonEnterCallBack(OnIdleCollisonEnter, (DWORD_PTR)this);
	m_fWallLength = 0;
	m_pPlayerCollider = m_pPlayer->GetCollider();
	m_fGroundLength = (m_pPlayerCollider->GetScale() / 2).Length()
		+ (fPoint(CTile::SIZE_TILE, CTile::SIZE_TILE) / 2).Length();
	m_bIsJump = false;
	for (int i = 0; i < 8; ++i)
	{
		m_pGroundCollider[i] = nullptr;
	}
}

CPlayerIdle::~CPlayerIdle()
{

}



void CPlayerIdle::GoundCheck()
{
	m_eInfo.g_bIsRight = false;
	m_eInfo.g_bIsLeft = false;
	m_eInfo.g_bIsUp = false;
	m_eInfo.g_bIsDown = false;
	fPoint fLeftUpPos = fPoint(-1, -1).normalize();
	fPoint fRightDownPos = fPoint(1, 1).normalize();
	float fRealTimeLength;
	float fLengthX;
	float fLengthY;

	// 지금 오브젝트 기준으로 생각했는데 플레이어 기준으로 생각해보자 굳이?
	/* TODO:
		지금은 정사각 콜라이더들을 기준으로 했기 때문에 기능이 돌아가지만
		직각사각형 콜라이더들이 부딫혔을때는 두 콜라이더를 이어주는 선이 둘과 겹치지 않을때
		각각의 가장 가까운 대각선을 기준으로 다시 설정해서 비교해주는 과정이 필요함
		현재 커비의 콜라이더는 정사각이므로 추가하지는 않았음
	*/
	for (int i = 0; i < 8; ++i)
	{
		if (nullptr != m_pGroundCollider[i])
		{
			fLengthX = (m_pPlayerCollider->GetFinalPos() - m_pGroundCollider[i]->GetFinalPos()).x;
			fLengthY = (m_pPlayerCollider->GetFinalPos() - m_pGroundCollider[i]->GetFinalPos()).y;
			fRealTimeLength = fPoint(abs(fLengthX), abs(fLengthY)).Length();
			if (abs(fLengthX) > abs(fLengthY))
			{
				m_fGroundLength = fPoint(
					abs((m_pGroundCollider[i]->GetScale()/2).x
						+ (m_pPlayerCollider->GetScale()/2).x)
					, abs(fLengthY)).Length();
			}
			else
			{
				m_fGroundLength = fPoint(
					abs(fLengthX)
					, abs((m_pGroundCollider[i]->GetScale() / 2).y
						+ (m_pPlayerCollider->GetScale() / 2).y)).Length();
			}

			if (m_fGroundLength >= fRealTimeLength)
			{
				fPoint fPlayerDisPos = fPoint(fLengthX, fLengthY).normalize();

				if (fPlayerDisPos.y <= fLeftUpPos.y)
				{
					if (m_pPlayer->GetRigidBody()->GetDir().y > 0)
					{
						m_pPlayer->GetRigidBody()->SetVelocity(
							fPoint(m_pPlayer->GetRigidBody()->GetVelocity().x, 0));
						

						m_pPlayer->SetPos(fPoint(m_pPlayer->GetPos().x
							, (m_pGroundCollider[i]->GetFinalPos().y)
							- ((m_pPlayerCollider->GetOffsetPos().y)
								+ (m_pPlayerCollider->GetScale() / 2).y
								+ (m_pGroundCollider[i]->GetScale() / 2).y)));
					}
					m_eInfo.g_bIsDown = true;
					m_pPlayer->GetGravity()->SetIsGround(true);
				}
				else if (fPlayerDisPos.y >= fRightDownPos.y)
				{
					if (m_pPlayer->GetRigidBody()->GetDir().y < 0)
					{
						m_pPlayer->GetRigidBody()->SetVelocity(
							fPoint(m_pPlayer->GetRigidBody()->GetVelocity().x, 0));
						

						m_pPlayer->SetPos(fPoint(m_pPlayer->GetPos().x
							, (m_pGroundCollider[i]->GetFinalPos().y)
							+ ((m_pPlayerCollider->GetOffsetPos().y)
								+ (m_pPlayerCollider->GetScale() / 2).y
								+ (m_pGroundCollider[i]->GetScale() / 2).y)));
					}

					m_eInfo.g_bIsUp = true;
				}
				else if (fPlayerDisPos.x < fLeftUpPos.x)
				{
					if (m_pPlayer->GetRigidBody()->GetDir().x > 0)
					{
						m_pPlayer->GetRigidBody()->SetVelocity(
							fPoint(0, m_pPlayer->GetRigidBody()->GetVelocity().y));
						

						m_pPlayer->SetPos(fPoint(
							(m_pGroundCollider[i]->GetFinalPos().x)
							- ((m_pPlayerCollider->GetOffsetPos().x)
								+ (m_pPlayerCollider->GetScale() / 2).x
								+ (m_pGroundCollider[i]->GetScale() / 2).x)
							, m_pPlayer->GetPos().y));
					}

					m_eInfo.g_bIsRight = true;
				}
				else if (fPlayerDisPos.x > fRightDownPos.x)
				{
					if (m_pPlayer->GetRigidBody()->GetDir().x < 0)
					{
						m_pPlayer->GetRigidBody()->SetVelocity(
							fPoint(0, m_pPlayer->GetRigidBody()->GetVelocity().y));
						

						m_pPlayer->SetPos(fPoint(
							(m_pGroundCollider[i]->GetFinalPos().x)
							+ ((m_pPlayerCollider->GetOffsetPos().x)
								+ (m_pPlayerCollider->GetScale() / 2).x
								+ (m_pGroundCollider[i]->GetScale() / 2).x)
							, m_pPlayer->GetPos().y));
					}

					m_eInfo.g_bIsLeft = true;
				}
			}
			else
			{
				m_pGroundCollider[i] = nullptr;
			}
		}
	}
	if (!m_eInfo.g_bIsDown)
	{
		m_pPlayer->GetGravity()->SetIsGround(false);
	}
}

void CPlayerIdle::AddGroundCollider(CCollider* ground)
{
	for(int i = 0; i < 8; ++i)
	{
		if (nullptr == m_pGroundCollider[i])
		{
			m_pGroundCollider[i] = ground;
			break;
		}
	}
}


void CPlayerIdle::KeyUpdate()
{
	if (Key(VK_LEFT))
	{
		if (!m_eInfo.g_bIsLeft)
			Exit(PLAYERSTATE::MOVE);
		else
			CStateManager::getInst()->ExitState(PLAYERSTATE::MOVE);
	}
	if (Key(VK_RIGHT))
	{
		if (!m_eInfo.g_bIsRight)
			Exit(PLAYERSTATE::MOVE);
		else
			CStateManager::getInst()->ExitState(PLAYERSTATE::MOVE);
	}
	if (KeyDown('C'))
	{
		Exit(PLAYERSTATE::ATTACK);
	}
	if (KeyDown('X') || KeyDown('V'))
	{
		if (m_pPlayer->GetGravity()->GetIsGround())
		{
			if (nullptr == CStateManager::getInst()->FindPlayeState(PLAYERSTATE::FLY))
			{
				CEventManager::getInst()->EventLoadPlayerState(PLAYERSTATE::JUMP);
				m_bIsJump = true;
			}
		}
	}
}

void CPlayerIdle::update()
{
	GoundCheck();

	if (m_pPlayer->GetGravity()->GetIsGround())
	{
		if (nullptr != CStateManager::getInst()->FindPlayeState(PLAYERSTATE::Fall))
		{
			CStateManager::getInst()->ExitState(PLAYERSTATE::Fall);
		}
	}
	else
	{
		if (nullptr == CStateManager::getInst()->FindPlayeState(PLAYERSTATE::JUMP))
		{
			CEventManager::getInst()->EventLoadPlayerState(PLAYERSTATE::Fall);
		}
	}


	KeyUpdate();
}



void CPlayerIdle::Anim()
{
	m_pPlayer->GetAnimator()->Play(L"Idle");
}

void CPlayerIdle::render()
{
	for (int i = 0; i < 8; ++i)
	{
		if (nullptr != m_pGroundCollider[i])
		{
			float fRealTimeLength = fPoint(abs(m_pPlayerCollider->GetFinalPos().x
				- m_pGroundCollider[i]->GetFinalPos().x)
				, abs(m_pPlayerCollider->GetFinalPos().y
					- m_pGroundCollider[i]->GetFinalPos().y)).Length();
			if (m_fGroundLength > fRealTimeLength)
			{

				COLORREF rgb = RGB(0, 0, 0);
				rgb = RGB(255, 0, 255);

				fPoint fptRenderStartPos = CCameraManager::getInst()->GetRenderPos(m_pGroundCollider[i]->GetFinalPos());
				fPoint fptRenderFinalPos = CCameraManager::getInst()->GetRenderPos(m_pPlayerCollider->GetFinalPos());

				CRenderManager::getInst()->RenderLine(
					fptRenderStartPos,
					fptRenderFinalPos,
					rgb,
					2.f
				);
			}
		}
	}
}

void CPlayerIdle::Enter()
{
	m_bIsActive = true;
}

void CPlayerIdle::Exit(PLAYERSTATE state)
{
	//m_bIsActive = false;
	CEventManager::getInst()->EventLoadPlayerState(state);
	//CStateManager::getInst()->ExitState(m_eState); 
}