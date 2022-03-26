#include "framework.h"
#include "CAnimObj.h"

CAnimObj::CAnimObj()
{
	m_iX = 0;
	m_iY = 0;
	m_fAccTime = 0;
	m_fOffSetX = 0;
	m_fOffSetY = 0;
	m_group = GROUP_ANIM::NONE;
	SetScale(fPoint(SIZE_ANIM, SIZE_ANIM));
}

CAnimObj::~CAnimObj()
{
}

CAnimObj* CAnimObj::Clone()
{
	return new CAnimObj(*this);
}

void CAnimObj::update()
{
}

void CAnimObj::render()
{
}

void CAnimObj::SetX(int x)
{
	m_iX = x;
}

void CAnimObj::SetY(int y)
{
	m_iY = y;
}

void CAnimObj::SetAccTime(float time)
{
	m_fAccTime = time;
}

void CAnimObj::SetOffSet(fPoint offset)
{
	m_fOffSetX = offset.x;
	m_fOffSetY = offset.y;
}

void CAnimObj::SetGroupAnim(GROUP_ANIM group)
{
	m_group = group;
}

int CAnimObj::GetX()
{
	return m_iX;
}

int CAnimObj::GetY()
{
	return m_iY;
}

float CAnimObj::GetAccTime()
{
	return m_fAccTime;
}

fPoint CAnimObj::GetOffSet()
{
	return fPoint(m_fOffSetX, m_fOffSetY);
}

GROUP_ANIM CAnimObj::GetGroupAnim()
{
	return m_group;
}

void CAnimObj::Save(FILE* pFile)
{
	fwrite(&m_iX, sizeof(int), 1, pFile);
	fwrite(&m_iY, sizeof(int), 1, pFile);
	fwrite(&m_fAccTime, sizeof(int), 1, pFile);
	fwrite(&m_fOffSetX, sizeof(int), 1, pFile);
	fwrite(&m_fOffSetY, sizeof(int), 1, pFile);

	int group = (int)m_group;
	fwrite(&group, sizeof(int), 1, pFile);
}

void CAnimObj::Load(FILE* pFile)
{
	fread(&m_iX, sizeof(int), 1, pFile);
	fread(&m_iY, sizeof(int), 1, pFile);
	fread(&m_fAccTime, sizeof(int), 1, pFile);
	fread(&m_fOffSetX, sizeof(int), 1, pFile);
	fread(&m_fOffSetY, sizeof(int), 1, pFile);

	int group;
	fread(&group, sizeof(int), 1, pFile);
	m_group = (GROUP_ANIM)group;
}
