#include "framework.h"
#include "CBackGround.h"
#include "CD2DImage.h"

CBackGround::CBackGround()
{
	m_pImg = nullptr;
}

CBackGround::~CBackGround()
{
    
}

void CBackGround::Load(wstring strKey, wstring strPath)
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
    SetScale(fPoint(m_pImg->GetWidth(), m_pImg->GetHeight()));
}

CBackGround* CBackGround::Clone()
{
	return nullptr;
}

void CBackGround::update()
{
}

void CBackGround::render()
{
    if (nullptr == m_pImg)
    {
        return;
    }


    fPoint pos = fPoint(0, 0);
    fPoint scale = GetScale();
    pos = CCameraManager::getInst()->GetRenderPos(pos);
    pos = pos / 6;

    CRenderManager::getInst()->RenderImage(
        m_pImg,
        pos.x,
        pos.y,
        pos.x + scale.x,
        pos.y + scale.y
    );
}
