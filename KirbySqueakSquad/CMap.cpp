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
    // 전체 크기가 map이 아니라 bg에 맞춰있어 bg를 로드할때 카메라 제한거리 입력해줌
    CCameraManager::getInst()->SetDisLimmit(fPoint(GetScale().x - 16.f, GetScale().y - 64.f));
}

CMap* CMap::Clone()
{
    return nullptr;
}

void CMap::update()
{
    
}

// 좌상단 기준
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
