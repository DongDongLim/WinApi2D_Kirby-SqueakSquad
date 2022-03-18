#include "framework.h"
#include "CMap.h"
#include "CD2DImage.h"

CMap::CMap()
{
    m_pImg = nullptr;
}

CMap::~CMap()
{
}

void CMap::Load(wstring strKey, wstring strPath)
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
    SetScale(fPoint(m_pImg->GetWidth(), m_pImg->GetHeight()));
    
}

CMap* CMap::Clone()
{
    return nullptr;
}

void CMap::update()
{
    
}

// ÁÂ»ó´Ü ±âÁØ
void CMap::render()
{
    if (nullptr == m_pImg)
    {
        return;
    }
    fPoint pos = fPoint(0, 0);
    fPoint scale = GetScale();
    pos = CCameraManager::getInst()->GetRenderPos(pos);

    CRenderManager::getInst()->RenderImage(
        m_pImg,
        pos.x,
        pos.y,
        pos.x + scale.x,
        pos.y + scale.y
    );
}
