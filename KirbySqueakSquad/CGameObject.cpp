#include "framework.h"
#include "CGameObject.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidBody.h"

CGameObject::CGameObject()
{
	m_eCurGroup = GROUP_GAMEOBJ::SIZE;
	m_fptPos = {};
	m_fptScale = {};
	m_pCollider = nullptr;
	m_pAnimator = nullptr;
	m_pRigid = nullptr;
	m_bAlive = true;
	m_fAccel = 0;
}

CGameObject::CGameObject(const CGameObject& other)
{
	m_strName	= other.m_strName;
	m_fptPos	= other.m_fptPos;
	m_fptScale	= other.m_fptScale;
	m_pCollider = nullptr;
	m_pAnimator = nullptr;
	m_pRigid = nullptr;
	m_bAlive	= true;

	if (nullptr != other.m_pCollider)
	{
		m_pCollider = new CCollider(*other.m_pCollider);
		m_pCollider->m_pOwner = this;
	}
	if (nullptr != other.m_pAnimator)
	{
		m_pAnimator = new CAnimator(*other.m_pAnimator);
		m_pAnimator->m_pOwner = this;
	}
	if (nullptr != other.m_pRigid)
	{
		m_pRigid = new CRigidBody(*other.m_pRigid);
		m_pRigid->m_pOwner = this;
	}
}

CGameObject::~CGameObject()
{
	if (nullptr != m_pCollider)
	{
		delete m_pCollider;
	}
	if (nullptr != m_pAnimator)
	{
		delete m_pAnimator;
	}
	if (nullptr != m_pRigid)
	{
		delete m_pRigid;
	}
}

void CGameObject::SetPos(fPoint pos)
{
	m_fptPos = pos;
}

void CGameObject::SetScale(fPoint scale)
{
	m_fptScale = scale;
}

void CGameObject::SetName(wstring name)
{
	m_strName = name;
}

void CGameObject::SetGroup(GROUP_GAMEOBJ group)
{
	m_eCurGroup = group;
}

fPoint CGameObject::GetPos()
{
	return m_fptPos;
}

fPoint CGameObject::GetScale()
{
	return m_fptScale;
}

wstring CGameObject::GetName()
{
	return m_strName;
}

GROUP_GAMEOBJ CGameObject::GetGroup()
{
	return m_eCurGroup;
}

bool CGameObject::isDead()
{
	return !m_bAlive;
}

void CGameObject::SetDead()
{
	m_bAlive = false;
}

void CGameObject::finalupdate()
{
	if (nullptr != m_pCollider)
	{
		m_pCollider->finalupdate();
	}
	if (nullptr != m_pRigid)
	{
		m_pRigid->finalupdate();
	}
}

void CGameObject::render()
{
	/*
	// ���� ��ġ�� �ѱ��, ������ ��ġ�� �޾ƿ�
	fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(m_fptPos);
	// ī�޶� �������� �׷������ϴ� ��ġ
	CRenderManager::getInst()->RenderRectangle(
		fptRenderPos.x - m_fptScale.x / 2,
		fptRenderPos.y - m_fptScale.y / 2,
		fptRenderPos.x + m_fptScale.x / 2,
		fptRenderPos.y + m_fptScale.y / 2);
	*/
	component_render();
}

void CGameObject::component_render()
{
	if (nullptr != m_pAnimator)
	{
		m_pAnimator->render();
	}
	if (nullptr != m_pCollider)
	{
		m_pCollider->render();
	}
}


CCollider* CGameObject::GetCollider()
{
	return m_pCollider;
}

void CGameObject::CreateCollider()
{
	m_pCollider = new CCollider();
	m_pCollider->m_pOwner = this;
}

CAnimator* CGameObject::GetAnimator()
{
	return m_pAnimator;
}

void CGameObject::CreateAnimator()
{
	m_pAnimator = new CAnimator;
	m_pAnimator->m_pOwner = this;
}

CRigidBody* CGameObject::GetRigidBody()
{
	return m_pRigid;
}

void CGameObject::CreateRigidBody()
{
	m_pRigid = new CRigidBody();
	m_pRigid->m_pOwner = this;
}
