//--------------------------------------------------------------------------------------    
//File		:  SpellCard.cpp
//Path		:  D:\MYPROJECTS\TH06-LIKE\TH06-LIKE\
//Author    :  Liu.zhenxing
//CreateTime:  N/A
//Desc		:  Spell Card control boss's action include moving and attacking
//--------------------------------------------------------------------------------------
#include "SpellCard.h"
#include "Boss.h"
#include "Bullet.h"
SpellCard::SpellCard(unsigned int id, string name, Boss *pBoss, unsigned int score, int countdown)
{
	m_id		= id;
	m_name		= name;
	m_pBoss		= pBoss;
	m_score		= score;
	m_countdown = countdown * 60;
	m_elapsedFrame	= 0;
	m_pBoss		= NULL;
}

SpellCard::~SpellCard()
{
	for (int i = (unsigned int)m_motionInfos.size() - 1; i >=  0; --i)
	{
		MotionInfo* pInfo = m_motionInfos[i];
		m_motionInfos.pop_back();
		SAFE_DELETE(pInfo);
	}
}


SpellCard01::SpellCard01(Boss *pBoss) : SpellCard(1, "Test01", pBoss,100000, 60) 
{
	m_motionInfos.push_back(new MotionInfo(0, new StaticTrack(0, D3DXVECTOR2(ACTIVE_RECT_CENTER_X, ACTIVE_RECT_TOP + 125))));
}

void SpellCard01::InitBoss()
{
}
void SpellCard01::Update()
{
	if (m_pBoss == NULL)
		return;
}

void SpellCard01::Shoot()
{
	if (m_pBoss == NULL)
		return;
	
}

void SpellCard01::OnComplete()
{

}

SpellCard02::SpellCard02(Boss *pBoss) : SpellCard(2, "Test02", pBoss,100000, 60) 
{
	m_motionInfos.push_back(new MotionInfo(0, new StaticTrack(0, D3DXVECTOR2(ACTIVE_RECT_CENTER_X, ACTIVE_RECT_TOP + 125))));
}

void SpellCard02::InitBoss()
{
}

void SpellCard02::Update()
{
	if (m_pBoss == NULL)
		return;
}

void SpellCard02::Shoot()
{
	if (m_pBoss == NULL)
		return;
}

void SpellCard02::OnComplete()
{

}