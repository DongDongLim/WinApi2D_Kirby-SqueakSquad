#include "framework.h"
#include "CAnimButton.h"
#include "CD2DImage.h"
#include "CAnimation.h"
#include "CAnimObj.h"

CAnimButton::CAnimButton()
{
	m_iIdx = 0;
}

CAnimButton::~CAnimButton()
{
}

void CAnimButton::render()
{
	if (nullptr != m_pImg)
	{
		UINT iWidth = m_pImg->GetWidth();
		UINT iHeight = m_pImg->GetHeight();

		UINT iMaxRow = iHeight / CAnimObj::SIZE_ANIM;
		UINT iMaxCol = iWidth / CAnimObj::SIZE_ANIM;

		UINT iCurRow = (m_iIdx / iMaxCol) % iMaxRow;
		UINT iCurCol = (m_iIdx % iMaxCol);


		CRenderManager::getInst()->RenderFrame(
			m_pImg,
			GetFinalPos().x,
			GetFinalPos().y,
			GetFinalPos().x + GetScale().x,
			GetFinalPos().y + GetScale().y,
			iCurCol * GetScale().x,
			iCurRow * GetScale().y,
			(iCurCol + 1) * GetScale().x,
			(iCurRow + 1) * GetScale().y
		);
	}
}

int CAnimButton::GetIdx()
{
	return m_iIdx;
}

void CAnimButton::SetIdx(int idx)
{
	m_iIdx = idx;
}
