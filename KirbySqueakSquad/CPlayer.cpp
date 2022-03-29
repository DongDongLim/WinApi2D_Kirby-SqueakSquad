#include "framework.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CD2DImage.h"
#include "CState.h"
#include "CPlayerState.h"
#include "CTile.h"
#include "CGravity.h"
#include "CMonster.h"
#include "CScene.h"


void CPlayer::SetAnim()
{
	CD2DImage* pImg = CResourceManager::getInst()->
		LoadD2DImage(L"NomalP", L"texture\\Animation\\NomalSprite.png");
	wstring keepPath = CPathManager::getInst()->GetContentPath();
	wstring path = keepPath;
	path += L"anim\\Idle.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\Move.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\Dash.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\Down.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\QuickStop.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\WallImpact.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\DownSlide.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\Jump.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\Turn.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\Fall0.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\Fall0_Down.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\Fall_Turn.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\Fall1.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\Fall1_Down.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\Eat.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\Up.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\UpIdle.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\UpMove.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\InHale0.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\InHale1.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\InHale2.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\InHale3.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\Eating.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	pImg = CResourceManager::getInst()->
		LoadD2DImage(L"CutterP", L"texture\\Animation\\cutterSprite.png");
	path = keepPath;
	path += L"anim\\CIdle.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\CMove.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\CDash.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\CDown.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\CQuickStop.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\CWallImpact.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\CDownSlide.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\CJump.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\CTurn.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\CFall0.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\CFall0_Down.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\CFall_Turn.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\CFall1.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\CFall1_Down.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\CUp.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\CUpIdle.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\CUpMove.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\CAttack0.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\CAttack1.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	pImg = CResourceManager::getInst()->
		LoadD2DImage(L"ThrowP", L"anim\\ThrowSprite.png");
	path = keepPath;
	path += L"anim\\TIdle.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\TMove.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\TDash.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\TDown.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\TQuickStop.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\TWallImpact.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\TDownSlide.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\TJump.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\TTurn.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\TFall0.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\TFall0_Down.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\TFall_Turn.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\TFall1.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\TFall1_Down.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\TUp.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\TUpIdle.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\TUpMove.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\TAttackD.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\TAttackN.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\TAttackU.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\TAttackSetD.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\TAttackSetN.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\TAttackSetU.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\TAttackSet.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\TAttackSet0.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
	path = keepPath;
	path += L"anim\\TAttackSet1.anim";
	CSceneManager::getInst()->GetCurScene()->LoadAnim(path, this, pImg);
}


CPlayer::CPlayer()
{
	//m_bIsGroundCount = 0;
	CStateManager::getInst()->SetPlayer(this);
	m_eAttackType = ATTACK_TYPE::NORMAL;
	m_pEatingMon = MON_TYPE::SIZE;
	m_colliderState = 0;
	m_colliderEnterState = 0;
	m_colliderExitState = 0;
	m_bIsRight = true;
	m_bISInhaleObj = false;
	for (int i = 0; i < 8; ++i)
	{
		m_pTileCollider[i] = nullptr;
	}

	SetName(L"Player");
	SetScale(fPoint(32.f, 32.f));

	// 콜라이더
	CreateCollider();
	GetCollider()->SetScale(fPoint(17.f, 17.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 7.f));

	// 애니메이션

	CreateAnimator();
	SetAnimString();
	SetAnim();
	GetAnimator()->Play(GetAnimString().g_wIDLE);
	// 중력
	CreateGravity();

	// 리지드바디 쓰자 충돌부분 보니까 써야겠다
	CreateRigidBody();
	CRigidBody* rigid = GetRigidBody();
	rigid->SetMass(1);
	rigid->SetFricCoeff(150.f);

	// 상태
	CPlayerState* pAnim = new CPlayerAnim();
	CStateManager::getInst()->AddState(PLAYERSTATE::Anim, pAnim);
	CEventManager::getInst()->EventLoadPlayerState(PLAYERSTATE::Anim);
	CPlayerState* pIdle = new CPlayerIdle();
	CStateManager::getInst()->AddState(PLAYERSTATE::IDLE, pIdle);
	CPlayerState* pMove = new CPlayerMove();
	CStateManager::getInst()->AddState(PLAYERSTATE::MOVE, pMove);
	CPlayerState* pAttack = new CPlayerAttack();
	CStateManager::getInst()->AddState(PLAYERSTATE::ATTACK, pAttack);
	CPlayerState* pJump = new CPlayerJump();
	CStateManager::getInst()->AddState(PLAYERSTATE::JUMP, pJump);
	CPlayerState* pFall = new CPlayerFall();
	CStateManager::getInst()->AddState(PLAYERSTATE::Fall, pFall);
	CPlayerState* pFly = new CPlayerFly();
	CStateManager::getInst()->AddState(PLAYERSTATE::FLY, pFly);
	CPlayerState* pEat = new CPlayerEat();
	CStateManager::getInst()->AddState(PLAYERSTATE::EAT, pEat);
	CPlayerState* pDown = new CPlayerDown();
	CStateManager::getInst()->AddState(PLAYERSTATE::DOWN, pDown);

	CEventManager::getInst()->EventLoadPlayerState(PLAYERSTATE::IDLE);
	CEventManager::getInst()->EventLoadPlayerState(PLAYERSTATE::Fall);


	m_fTileLength = (GetCollider()->GetScale() / 2).Length()
		+ (fPoint(CTile::SIZE_TILE, CTile::SIZE_TILE) / 2).Length();

}

CPlayer::~CPlayer()
{
	for (int i = 0; i < m_wAnimKey.size(); ++i)
	{
		delete m_wAnimKey[i];
	}
}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
}


void CPlayer::update()
{
	if (KeyDown(VK_LEFT) || KeyDown(VK_RIGHT))
	{
		KeyDown(VK_LEFT) ? SetDir(false) : SetDir(true);
	}
	else if (KeyDown('Z'))
	{
		if (ATTACK_TYPE::NORMAL != m_eAttackType)
		{
			m_eAttackType = ATTACK_TYPE::NORMAL;
			SetAnimString();
		}
	}

	TileCheck();
	CStateManager::getInst()->update();
	GetAnimator()->update();
}

void CPlayer::render()
{
	component_render();
	CStateManager::getInst()->render();
	TileCheckRender();
}

void CPlayer::TileCheckRender()
{
	float fRealTimeLength;
	float fLengthX;
	float fLengthY;
	CCollider* m_pPlayerCollider = GetCollider();
	for (int i = 0; i < 8; ++i)
	{
		if (nullptr != m_pTileCollider[i])
		{
			fLengthX = (m_pPlayerCollider->GetFinalPos() - m_pTileCollider[i]->GetFinalPos()).x;
			fLengthY = (m_pPlayerCollider->GetFinalPos() - m_pTileCollider[i]->GetFinalPos()).y;
			fRealTimeLength = fPoint(abs(fLengthX), abs(fLengthY)).Length();
			if (abs(fLengthX) > abs(fLengthY))
			{
				m_fTileLength = fPoint(
					abs((m_pTileCollider[i]->GetScale() / 2).x
						+ (m_pPlayerCollider->GetScale() / 2).x)
					, abs(fLengthY)).Length();
			}
			else
			{
				m_fTileLength = fPoint(
					abs(fLengthX)
					, abs((m_pTileCollider[i]->GetScale() / 2).y
						+ (m_pPlayerCollider->GetScale() / 2).y)).Length();
			}
			if (m_fTileLength >= fRealTimeLength)
			{

				COLORREF rgb = RGB(0, 0, 0);
				rgb = RGB(255, 0, 255);

				fPoint fptRenderStartPos = CCameraManager::getInst()->GetRenderPos(m_pTileCollider[i]->GetFinalPos());
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

PLAYERINFO& CPlayer::GetPlaeyrInfo()
{
	return info;
}


void CPlayer::AddTileCollider(CCollider* ground)
{
	bool istrue = false;
	for (int i = 0; i < 8; ++i)
	{
		if (nullptr != m_pTileCollider[i])
		{
			if (m_pTileCollider[i] == ground)
				istrue = true;
			break;
		}
	}
	if (!istrue)
	{
		for (int i = 0; i < 8; ++i)
		{
			if (nullptr == m_pTileCollider[i])
			{
				m_pTileCollider[i] = ground;
				break;
			}
		}
	}
}

void CPlayer::TileCheck()
{
	info.g_bIsDown = false;
	info.g_bIsUp = false;
	info.g_bIsRight = false;
	info.g_bIsLeft = false;

	fPoint fLeftUpPos = fPoint(-1, -1).normalize();
	fPoint fRightDownPos = fPoint(1, 1).normalize();
	float fRealTimeLength;
	float fLengthX;
	float fLengthY;
	CCollider* m_pPlayerCollider = GetCollider();
	float fDirX = GetRigidBody()->GetDir().x;
	float fDirY = GetRigidBody()->GetDir().y;

	// 지금 오브젝트 기준으로 생각했는데 플레이어 기준으로 생각해보자 굳이?
	/* TODO:
		지금은 정사각 콜라이더들을 기준으로 했기 때문에 기능이 돌아가지만
		직각사각형 콜라이더들이 부딫혔을때는 두 콜라이더를 이어주는 선이 둘과 겹치지 않을때
		각각의 가장 가까운 대각선을 기준으로 다시 설정해서 비교해주는 과정이 필요함
		현재 커비의 콜라이더는 정사각이므로 추가하지는 않았음
	*/
	for (int i = 0; i < 8; ++i)
	{
		if (nullptr != m_pTileCollider[i])
		{
			fLengthX = (m_pPlayerCollider->GetFinalPos() - m_pTileCollider[i]->GetFinalPos()).x;
			fLengthY = (m_pPlayerCollider->GetFinalPos() - m_pTileCollider[i]->GetFinalPos()).y;
			fRealTimeLength = fPoint(abs(fLengthX), abs(fLengthY)).Length();
			CTile* tile = (CTile*)m_pTileCollider[i]->GetObj();
			if (abs(fLengthX) > abs(fLengthY))
			{
				m_fTileLength = fPoint(
					abs((m_pTileCollider[i]->GetScale() / 2).x
						+ (m_pPlayerCollider->GetScale() / 2).x)
					, abs(fLengthY)).Length();
			}
			else
			{
				m_fTileLength = fPoint(
					abs(fLengthX)
					, abs((m_pTileCollider[i]->GetScale() / 2).y
						+ (m_pPlayerCollider->GetScale() / 2).y)).Length();
			}

			if (m_fTileLength >= fRealTimeLength)
			{
				fPoint fPlayerDisPos = fPoint(fLengthX, fLengthY).normalize();

				if (fPlayerDisPos.y <= fLeftUpPos.y)
				{
					if (tile->GetGroup() == GROUP_TILE::PLATFORM)
					{
						if ((m_fTileLength - fRealTimeLength) > 1.f)
						{
							continue;
						}
					}
					if (fDirY >= 0)
					{
						GetRigidBody()->SetVelocity(
							fPoint(GetRigidBody()->GetVelocity().x, 0));


						SetPos(fPoint(GetPos().x
							, (m_pTileCollider[i]->GetFinalPos().y)
							- ((m_pPlayerCollider->GetOffsetPos().y)
								+ (m_pPlayerCollider->GetScale() / 2).y
								+ (m_pTileCollider[i]->GetScale() / 2).y)));
						info.g_bIsDown = true;
						GetGravity()->SetIsGround(true);
					}
				}
				else if (tile->GetGroup() == GROUP_TILE::GROUND)
				{
					if (fPlayerDisPos.y >= fRightDownPos.y)
					{
						if (fDirY < 0)
						{
							GetRigidBody()->SetVelocity(
								fPoint(GetRigidBody()->GetVelocity().x, 0));


							SetPos(fPoint(GetPos().x
								, (m_pTileCollider[i]->GetFinalPos().y)
								+ ((m_pPlayerCollider->GetOffsetPos().y)
									+ (m_pPlayerCollider->GetScale() / 2).y
									+ (m_pTileCollider[i]->GetScale() / 2).y)));
						}

						info.g_bIsUp = true;
					}
					else if (fPlayerDisPos.x < fLeftUpPos.x)
					{
						if (fDirX > 0)
						{
							GetRigidBody()->SetVelocity(
								fPoint(0, GetRigidBody()->GetVelocity().y));


							SetPos(fPoint(
								(m_pTileCollider[i]->GetFinalPos().x)
								- ((m_pPlayerCollider->GetOffsetPos().x)
									+ (m_pPlayerCollider->GetScale() / 2).x
									+ (m_pTileCollider[i]->GetScale() / 2).x)
								, GetPos().y));

						}

						info.g_bIsRight = true;
					}
					else if (fPlayerDisPos.x > fRightDownPos.x)
					{
						if (fDirX < 0)
						{
							GetRigidBody()->SetVelocity(
								fPoint(0, GetRigidBody()->GetVelocity().y));


							SetPos(fPoint(
								(m_pTileCollider[i]->GetFinalPos().x)
								+ ((m_pPlayerCollider->GetOffsetPos().x)
									+ (m_pPlayerCollider->GetScale() / 2).x
									+ (m_pTileCollider[i]->GetScale() / 2).x)
								, GetPos().y));

						}

						info.g_bIsLeft = true;
					}
				}
				else
				{
					m_pTileCollider[i] = nullptr;
				}
			}
			else
			{
				m_pTileCollider[i] = nullptr;
			}
		}
	}
	if (!info.g_bIsDown)
	{
		GetGravity()->SetIsGround(false);
	}
}


MON_TYPE CPlayer::GetMonType()
{
	return m_pEatingMon;
}

const PLAYERANIM& CPlayer::GetAnimString()
{
	return anim;
}

void CPlayer::SetAnimString()
{
	switch (m_eAttackType)
	{
	case ATTACK_TYPE::NORMAL:
		anim.g_wIDLE = L"Idle";
		anim.g_wMOVE = L"Move";
		anim.g_wDASH = L"Dash";
		anim.g_wDOWN = L"Down";
		anim.g_wQUICKSTOP = L"QuickStop";
		anim.g_wWALLIMPACT = L"WallImpact";
		anim.g_wDOWNSLIDE = L"DownSlide";
		anim.g_wJUMP = L"Jump";
		anim.g_wTURN = L"Turn";
		anim.g_wFALL0 = L"Fall0";
		anim.g_wFALL_DOWN = L"Fall0_Down";
		anim.g_wFALL_TURN = L"Fall_Turn";
		anim.g_wFALL1 = L"Fall1";
		anim.g_wFALL1_DOWN = L"Fall1_Down";
		anim.g_wUP = L"Up";
		anim.g_wUPIDLE = L"UpIdle";
		anim.g_wUPMOVE = L"UpMove";
		break;
	case ATTACK_TYPE::CUTTER:
		anim.g_wIDLE = L"CIdle";
		anim.g_wMOVE = L"CMove";
		anim.g_wDASH = L"CDash";
		anim.g_wDOWN = L"CDown";
		anim.g_wQUICKSTOP = L"CQuickStop";
		anim.g_wWALLIMPACT = L"CWallImpact";
		anim.g_wDOWNSLIDE = L"CDownSlide";
		anim.g_wJUMP = L"CJump";
		anim.g_wTURN = L"CTurn";
		anim.g_wFALL0 = L"CFall0";
		anim.g_wFALL_DOWN = L"CFall0_Down";
		anim.g_wFALL_TURN = L"CFall_Turn";
		anim.g_wFALL1 = L"CFall1";
		anim.g_wFALL1_DOWN = L"CFall1_Down";
		anim.g_wUP = L"CUp";
		anim.g_wUPIDLE = L"CUpIdle";
		anim.g_wUPMOVE = L"CUpMove";
		break;
	case ATTACK_TYPE::THROW:
		anim.g_wIDLE = L"TIdle";
		anim.g_wMOVE = L"TMove";
		anim.g_wDASH = L"TDash";
		anim.g_wDOWN = L"TDown";
		anim.g_wQUICKSTOP = L"TQuickStop";
		anim.g_wWALLIMPACT = L"TWallImpact";
		anim.g_wDOWNSLIDE = L"TDownSlide";
		anim.g_wJUMP = L"TJump";
		anim.g_wTURN = L"TTurn";
		anim.g_wFALL0 = L"TFall0";
		anim.g_wFALL_DOWN = L"TFall0_Down";
		anim.g_wFALL_TURN = L"Tall_Turn";
		anim.g_wFALL1 = L"TFall1";
		anim.g_wFALL1_DOWN = L"TFall1_Down";
		anim.g_wUP = L"TUp";
		anim.g_wUPIDLE = L"TUpIdle";
		anim.g_wUPMOVE = L"TUpMove";
		break;
	case ATTACK_TYPE::SIZE:
		break;
	default:
		break;
	}
}

void CPlayer::SetIsInhale(bool isInhale)
{
	m_bISInhaleObj = isInhale;
}

bool CPlayer::GetDir()
{
	return m_bIsRight;
}

bool CPlayer::GetIsInhale()
{
	return m_bISInhaleObj;
}

void CPlayer::SetAttackType(ATTACK_TYPE type)
{
	m_eAttackType = type;
	SetAnimString();
}

void CPlayer::SetMonType(MON_TYPE type)
{
	m_pEatingMon = type;
}

void CPlayer::SetDir(bool dir)
{
	m_bIsRight = dir;
}


void CPlayer::SetCollisonCallBack(COLLIDER_FUNC pFunc, DWORD_PTR state)
{
	m_arrFunc.push_back(pFunc);
	m_colliderState = state;
}

void CPlayer::SetCollisonEnterCallBack(COLLIDER_FUNC pFunc, DWORD_PTR state)
{
	m_arrEnterFunc.push_back(pFunc);
	m_colliderEnterState = state;
}
void CPlayer::SetCollisonExitCallBack(COLLIDER_FUNC pFunc, DWORD_PTR state)
{
	m_arrExitFunc.push_back(pFunc);
	m_colliderExitState = state;
}

ATTACK_TYPE CPlayer::GetAttackType()
{
	return m_eAttackType;
}

void CPlayer::OnCollision(CCollider* other)
{
	if (other->GetObj()->GetGroup() == GROUP_GAMEOBJ::TILE)
	{
		AddTileCollider((CCollider*)other);
	}

	list<COLLIDER_FUNC>::iterator iter = m_arrFunc.begin();
	for (; iter != m_arrFunc.end(); ++iter)
	{
		COLLIDER_FUNC collFunc = *iter;
		collFunc(m_colliderState, other);
	}
}

void CPlayer::OnCollisionEnter(CCollider* other)
{
	if (other->GetObj()->GetGroup() == GROUP_GAMEOBJ::MONSTER)
	{
		CMonster* mon = (CMonster*)other->GetObj();
		if (mon->GetIsEaten())
		{
			if (m_eAttackType == ATTACK_TYPE::NORMAL)
				SetMonType(mon->GetType());
			CStateManager::getInst()->LoadState(PLAYERSTATE::EAT);
		}
	}

	list<COLLIDER_FUNC>::iterator iter = m_arrEnterFunc.begin();
	for (; iter != m_arrEnterFunc.end(); ++iter)
	{
		COLLIDER_FUNC collFunc = *iter;
		collFunc(m_colliderEnterState, other);
	}
}

void CPlayer::OnCollisionExit(CCollider* other)
{
	list<COLLIDER_FUNC>::iterator iter = m_arrExitFunc.begin();
	for (; iter != m_arrExitFunc.end(); ++iter)
	{
		COLLIDER_FUNC collFunc = *iter;
		collFunc(m_colliderExitState, other);
	}
}