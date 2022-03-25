#include "framework.h"
#include "CCameraManager.h"
#include "CGameObject.h"
#include "CTexture.h"

CCameraManager::CCameraManager()
{
	m_fptLookAt = fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f);
	m_fptCurLookAt = m_fptLookAt;
	m_fptPrevLookAt = m_fptLookAt;
	m_pTargetObj = nullptr;
	m_fAccTime = m_fTime;
	m_fSpeed = 0;
	m_fZoom = 3.f;
	m_fDisLimmit = fPoint(0, 0);
}

CCameraManager::~CCameraManager()
{

}

void CCameraManager::init()
{
}

void CCameraManager::update()
{
	if (m_pTargetObj)
	{
		if (m_pTargetObj->isDead())
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			SetLookAt(m_pTargetObj->GetPos());
		}
	}

	// ȭ�� �߾Ӱ� ī�޶� LookAt ��ǥ ������ ���� ���
	CalDiff();
}

void CCameraManager::render()
{
	if (m_listCamEffect.empty())
	{
		return;
	}

	tCamEffect& effect = m_listCamEffect.front();
	effect.fCurTime += fDT;

	float fRatio = 0.f;
	fRatio = effect.fCurTime / effect.fDuration;
	if (fRatio < 0.f)
		fRatio = 0.f;
	else if (fRatio > 1.f)
		fRatio = 1.f;


	else if (CAM_EFFECT::FADE_IN == effect.m_eEffect)
		fRatio = 1.f - fRatio;

	CRenderManager::getInst()->RenderFillRectangle(0, 0, WINSIZEX, WINSIZEY, RGB(0, 0, 0), fRatio);
	/*
	AlphaBlend(hDC
		, 0, 0
		, (int)(m_pImg->GetBmpWidth())
		, (int)(m_pImg->GetBmpHeight())
		, m_pImg->GetDC()
		, 0, 0
		, (int)(m_pImg->GetBmpWidth())
		, (int)(m_pImg->GetBmpHeight())
		, bf);
		*/

	if (effect.fDuration < effect.fCurTime)
	{
		m_listCamEffect.pop_front();
	}
}

void CCameraManager::SetLookAt(fPoint lookAt)
{
	m_fptLookAt = lookAt;
	/*
	float fMoveDist = (m_fptLookAt - m_fptPrevLookAt).Length();

	m_fSpeed = fMoveDist / m_fTime;
	m_fAccTime = 0.f;
	*/
}

void CCameraManager::SetTargetObj(CGameObject* target)
{
	m_pTargetObj = target;
}

void CCameraManager::SetDisLimmit(fPoint limmit)
{
	m_fDisLimmit = limmit;
}

fPoint CCameraManager::GetLookAt()
{
	return m_fptCurLookAt;
}

fPoint CCameraManager::GetRenderPos(fPoint objPos)
{
	return objPos - m_fptDiff;
}

fPoint CCameraManager::GetRealPos(fPoint renderPos)
{
	// ������ ��ǥ���� ���̰���ŭ �����ָ� ���� ��ǥ�� ����.
	return renderPos + m_fptDiff;
}

fPoint CCameraManager::GetDisLimmit()
{
	return m_fDisLimmit;
}

float CCameraManager::GetZoom()
{
	return m_fZoom;
}

void CCameraManager::FadeIn(float duration)
{
	tCamEffect ef = {};
	ef.m_eEffect = CAM_EFFECT::FADE_IN;
	ef.fDuration = duration;
	ef.fCurTime = 0.f;

	m_listCamEffect.push_back(ef);

	if (0.f == duration)
	{
		assert(nullptr);
	}
}

void CCameraManager::FadeOut(float duration)
{
	tCamEffect ef = {};
	ef.m_eEffect = CAM_EFFECT::FADE_OUT;
	ef.fDuration = duration;
	ef.fCurTime = 0.f;

	m_listCamEffect.push_back(ef);

	if (0.f == duration)
	{
		assert(nullptr);
	}
}

void CCameraManager::Scroll(fVec2 vec, float velocity)
{
	m_fptLookAt = m_fptLookAt + vec * velocity * fDT;
	m_fptCurLookAt = m_fptCurLookAt + vec * velocity * fDT;

	fPoint fptCenter = fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f);
	m_fptDiff = m_fptCurLookAt - fptCenter / m_fZoom;
}

void CCameraManager::CalDiff()
{
	// Ŀ��� ī�޶� �ٷ� �����
	m_fptCurLookAt = m_fptLookAt;
	fPoint fptCenter = fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f);
	fPoint fptLimitDis = m_fptCurLookAt - (fptCenter);
	// ī�޶� �� ������ �ȳ��������ϱ�
	float fpointX = (m_fDisLimmit - (fptCenter ) * 2).x;
	float fpointY = (m_fDisLimmit - (fptCenter ) * 2).y;
	// limmit�� size�� windowsize���� ���� ��� ����ó��
	if (fpointX < 0)
		fpointX = 0; 
	if (fpointY < 0)
		fpointY = 0;
	if (0 <= fptLimitDis.x && fptLimitDis.x <= fpointX)
		m_fptDiff.x = fptLimitDis.x;
	if (0 <= fptLimitDis.y && fptLimitDis.y <= fpointY)
		m_fptDiff.y = fptLimitDis.y;

	/*
	m_fAccTime += fDT;

	// �ð��� ������, �����Ѱ����� ����
	if (m_fTime <= m_fAccTime)
	{
		m_fptCurLookAt = m_fptLookAt;
	}
	else
	{
		fPoint fptCenter = fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f);

		m_fptCurLookAt = m_fptPrevLookAt + (m_fptLookAt - m_fptPrevLookAt).normalize() * m_fSpeed * fDT;
		m_fptDiff = m_fptCurLookAt - fptCenter;
		m_fptPrevLookAt = m_fptCurLookAt;
	}
	*/
}
