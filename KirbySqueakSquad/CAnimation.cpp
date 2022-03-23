#include "framework.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CGameObject.h"
#include "CTexture.h"

CAnimation::CAnimation()
{
    m_strName = L"";
    m_pAnimator = nullptr;
    m_pImg = nullptr;
    m_iCurFrm = 0;
    m_fAccTime = 0;
    m_bReverseRenderRenderPlay = false;
}

CAnimation::CAnimation(const CAnimation& pOther)
{
    m_strName = pOther.m_strName;
    for (int i = 0; i < pOther.m_vecFrm.size(); i++)
    {
        m_vecFrm.push_back(pOther.m_vecFrm[i]);
    }
    m_iCurFrm = pOther.m_iCurFrm;
    m_fAccTime = pOther.m_fAccTime;
    m_bReverseRender = pOther.m_bReverseRender;

    m_pAnimator = nullptr;
    m_pImg = pOther.m_pImg;
}

CAnimation::~CAnimation()
{
}

void CAnimation::SetName(const wstring& strName)
{
    m_strName = strName;
}

const wstring& CAnimation::GetName()
{
    return m_strName;
}

void CAnimation::SetReversePlay(bool isreverse)
{
    m_bReverseRenderRenderPlay = isreverse;
}

void CAnimation::SetReverse(bool reverse)
{
    m_bReverseRender = reverse;
}

void CAnimation::SetFrame(int frmIndex)
{
    m_iCurFrm = frmIndex;
}

tAniFrm& CAnimation::GetFrame(int frmIndex)
{
    return m_vecFrm[frmIndex];
}

int CAnimation::GetAnimSize()
{
    return m_vecFrm.size();
}

float CAnimation::GetFrameSpeed()
{
    return m_vecFrm[0].fDuration;
}

void CAnimation::update()
{
    m_fAccTime += fDT;

    if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
    {
        if (m_bReverseRenderRenderPlay)
        {
            --m_iCurFrm;
            m_iCurFrm %= m_vecFrm.size();
            m_fAccTime -= m_vecFrm[m_iCurFrm].fDuration;
        }
        else
        {
            ++m_iCurFrm;
            m_iCurFrm %= m_vecFrm.size();
            m_fAccTime -= m_vecFrm[m_iCurFrm].fDuration;
        }
    }
}

void CAnimation::render()
{
    CGameObject* pObj = m_pAnimator->GetObj();
    fPoint fptPos = pObj->GetPos();
    fPoint fptScale = pObj->GetScale();
    tAniFrm frm = m_vecFrm[m_iCurFrm];

    fptPos = fptPos + frm.fptOffset;
    fptPos = CCameraManager::getInst()->GetRenderPos(fptPos);


    if (m_bReverseRender)
    {
        CRenderManager::getInst()->RenderRevFrame(
            m_pImg,
            fptPos.x - fptScale.x / 2.f,
            fptPos.y - fptScale.y / 2.f,
            fptPos.x + fptScale.x / 2.f,
            fptPos.y + fptScale.y / 2.f,
            frm.fptLT.x,
            frm.fptLT.y,
            frm.fptLT.x + frm.fptSlice.x,
            frm.fptLT.y + frm.fptSlice.y
        );
    }
    else
    {
        CRenderManager::getInst()->RenderFrame(
            m_pImg,
            fptPos.x - fptScale.x / 2.f,
            fptPos.y - fptScale.y / 2.f,
            fptPos.x + fptScale.x / 2.f,
            fptPos.y + fptScale.y / 2.f,
            frm.fptLT.x,
            frm.fptLT.y,
            frm.fptLT.x + frm.fptSlice.x,
            frm.fptLT.y + frm.fptSlice.y
        );
    }

}

void CAnimation::Create(CD2DImage* img,     // �ִϸ��̼��� �̹���
    fPoint lt,          // �ִϸ��̼� ���� �������� �»�� ��ǥ
    fPoint slice,       // �ִϸ��̼� �������� ũ��
    fPoint step,        // �ִϸ��̼� �������� �ݺ� ��ġ
    float duration,     // �ִϸ��̼� ������ ���ӽð�
    UINT frmCount)      // �ִϸ��̼� ������ ����
{
    m_pImg = img;

    tAniFrm frm = {};
    for (UINT i = 0; i < frmCount; i++)
    {
        frm.fDuration = duration;
        frm.fptSlice = slice;
        frm.fptLT = lt + step * i;

        m_vecFrm.push_back(frm);
    }
}
