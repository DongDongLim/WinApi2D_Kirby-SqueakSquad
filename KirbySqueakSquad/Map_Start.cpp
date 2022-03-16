#include "framework.h"
#include "Map_Start.h"
#include "CD2DImage.h"

Map_Start::Map_Start()
{
    m_indexBG = 1;
    pimgBG = new CD2DImage;
    pimgMap = new CD2DImage;
    pimgBG = CResourceManager::getInst()->LoadD2DImage(L"bg", L"texture\\bg\\background.png");
    pimgMap = CResourceManager::getInst()->LoadD2DImage(L"stage", L"texture\\map\\stage1.png");
}

Map_Start::~Map_Start()
{
}

Map_Start* Map_Start::Clone()
{
    return nullptr;
}

void Map_Start::update()
{
    /*
    fPoint pos = GetPos();

    if (Key(VK_LEFT))
    {
        pos.x -= 100 * fDT;
    }

    if (Key(VK_RIGHT))
    {
        pos.x += 100 * fDT;
    }

    if (Key(VK_DOWN))
    {
        pos.y += 100 * fDT;
    }

    if (Key(VK_UP))
    {
        pos.y -= 100 * fDT;
    }

    SetPos(pos);
    */
}

void Map_Start::render()
{
    fPoint pos = GetPos();
    fPoint scale = GetScale();

    // 카메라 영향
    pos = CCameraManager::getInst()->GetRenderPos(pos);
    
    // 배경 및 맵은 좌상단 기준으로 그려줌
    // TODO : 크기 정리
    CRenderManager::getInst()->RenderFrame(
        pimgBG,
        pos.x,
        pos.y,
        pos.x + 512,
        pos.y + 192,
        0,
        192 * m_indexBG,
        553,
        192 * (m_indexBG + 1)
    );


    CRenderManager::getInst()->RenderImage(
        pimgMap,
        pos.x,
        pos.y,
        pos.x + scale.x,
        pos.y + scale.y
    );
}
