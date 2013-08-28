//--------------------------------------------------------------------------------------
//File: Stage1Enemy.cpp
//
//Desc: 
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#include "Stage1Enemy.h"
#include "GameManager.h"
#include "Effect.h"
#include "MotionTrack.h"
#include "Bullet.h"
#include "BulletFactory.h"
#include "Player.h"

#define BOSS_STATE_INTERVAl  60
//--------------------------------------------------------------------------------------
//Enemy_01_01
//--------------------------------------------------------------------------------------
Enemy_01_01::Enemy_01_01(D3DXVECTOR2 &position, int mode, int startShootFrame)	: Enemy(TEXTURE_STG1ENM)
{
	m_position			= position;
	m_startShootFrame	= startShootFrame;
	m_actionMode		= mode;
	m_hp				= 4;
	m_name				= "blue elf";
	m_shootInterval		= 120;
	m_maxShootCount		= 1;
	m_shootLoopFrame	= 0;
	RECT rect ;
	SetRect(&rect, 0, 0, 256, 32);
	SetSprite(rect, 8, 8, 32, 32);
	switch(m_actionMode)
	{
	case 1:
		motionInfos.push_back(new MotionInfo(0, new LineTrack(D3DXVECTOR2(1, 10), 3, 0, 0, NULL_POSITION), true));
		motionInfos.push_back(new MotionInfo(60, new CircleTrack(D3DX_PI, 60, 3, 60, false), true));
		motionInfos.push_back(new MotionInfo(120, new CircleTrack(D3DX_PI, 60, 3, 120, true), true));
		motionInfos.push_back(new MotionInfo(180, new LineTrack(D3DXVECTOR2(1, 10), 3, 0, 180, NULL_POSITION), true));
		motionIndex = 0;
		break;
	case 2:
		motionInfos.push_back(new MotionInfo(0, new LineTrack(D3DXVECTOR2(-1, 10), 3, 0, 0, NULL_POSITION), true));
		motionInfos.push_back(new MotionInfo(60, new CircleTrack(D3DX_PI, 60, 3, 60, true), true));
		motionInfos.push_back(new MotionInfo(120, new CircleTrack(D3DX_PI, 60, 3, 120, false), true));
		motionInfos.push_back(new MotionInfo(180, new LineTrack(D3DXVECTOR2(-1, 10), 3, 0, 180, NULL_POSITION), true));
		motionIndex = 0;
		break;
	default:
		break;
	}
}

void	Enemy_01_01::Update()
{
	Enemy::Update();
}

void	Enemy_01_01::Shoot()
{
	if (m_shootInterval == 0)
		return;

	int shootCount = m_shootFrame / m_shootInterval + 1;
	if (m_shootFrame % m_shootInterval == 0 && shootCount <= m_maxShootCount)
	{
		Bullet *pBullet = &BulletFactory::GetBullet(GetCenter(), BULLET_SHAPE_LITTLE_CIRCLE, 0);
		pBullet->motionInfos.push_back(new MotionInfo(0, new LineTrack(gm.GetPlayer()->GetCenter() - GetCenter(), 6, 0, 0, GetPosition())));
		pBullet->motionIndex = 0;
		gm.AddBullet(pBullet);
	}
	++m_shootFrame;
	if (m_shootLoopFrame > 0 && m_shootFrame > m_shootLoopFrame)
	{
		m_shootFrame = 0;
	}
	

}
void	Enemy_01_01::OnWipped()
{
	Enemy::OnWipped();
	if (IsInScreen())
	{
		gm.AddObject(new EffectEnemyDead(GetCenter()));
		dsMgr.playSound(rm.GetSoundBuffer(SOUND_ENEP));
	}
}

//--------------------------------------------------------------------------------------
//Enemy_01_02
//--------------------------------------------------------------------------------------
Enemy_01_02::Enemy_01_02(D3DXVECTOR2 &position, int actionMode, int startShootFrame) :Enemy(TEXTURE_STG1ENM)
{
	m_position			= position;
	m_startShootFrame	= startShootFrame;
	m_shootInterval		= 10;
	m_maxShootCount		= 2;
	m_shootLoopFrame	= 0;

	m_actionMode	= actionMode;
	m_name			= "red elf";
//	m_v				= 2;
	RECT rect ;
	SetRect(&rect, 0, 32, 256, 64);
	SetSprite(rect, 8, 8, 32, 32);
	switch(m_actionMode)
	{
	case 1:
		motionInfos.push_back(new MotionInfo(0, new LineTrack(D3DXVECTOR2(0, 1), 2, 0, 0, NULL_POSITION), true));
		motionInfos.push_back(new MotionInfo(30, new LineTrack(D3DXVECTOR2(0, 1), 0, 0, 30, NULL_POSITION), true));
		motionInfos.push_back(new MotionInfo(40, new CircleTrack(D3DX_PI * 0.5, 60, 2, 40, true, D3DXVECTOR2(0, -60)), true));
		motionIndex = 0;
		break;
	case 2:
		motionInfos.push_back(new MotionInfo(0, new LineTrack(D3DXVECTOR2(0, 1), 2, 0, 0, NULL_POSITION), true));
		motionInfos.push_back(new MotionInfo(30, new LineTrack(D3DXVECTOR2(0, 1), 0, 0, 30, NULL_POSITION), true));
		motionInfos.push_back(new MotionInfo(40, new CircleTrack(D3DX_PI * 0.5, 60, 2, 40, false, D3DXVECTOR2(0, -60)), true));
		motionIndex = 0;
		break;
	default:
		motionIndex = 0;
		break;
	}
}
void	Enemy_01_02::Shoot()
{
	if (m_shootInterval == 0)
		return;

	int shootCount = m_shootFrame / m_shootInterval + 1;
	if (m_shootFrame % m_shootInterval == 0 && shootCount <= m_maxShootCount)
	{
		float theta = 0;
		for (int i = 0; i < 6; i ++)
		{
			Bullet *pBullet = &BulletFactory::GetBullet(GetPosition(), BULLET_SHAPE_SOLIDCIRCLE, 2);
			pBullet->motionInfos.push_back(new MotionInfo(0, new LineTrack(D3DXVECTOR2(cos(theta), sin(theta)), 10, 0, 0, NULL_POSITION), true));
			pBullet->motionInfos.push_back(new MotionInfo(5, new LineTrack(D3DXVECTOR2(cos(theta), sin(theta)), 3, 0, 0, NULL_POSITION), true));
			pBullet->motionIndex =  0;
			gm.AddBullet(pBullet);
			theta += D3DX_PI / 6;		
		}
	}

	++m_shootFrame;
	if (m_shootLoopFrame > 0 && m_shootFrame > m_shootLoopFrame)
	{
		m_shootFrame = 0;
	}


}
void	Enemy_01_02::Update()
{
	Enemy::Update();
}

void	Enemy_01_02::OnWipped()
{

	Enemy::OnWipped();
	if (IsInScreen())
	{
		EffectEnemyDead01 *pEffect = new EffectEnemyDead01();
		pEffect->SetCenter(this->GetCenter());
		gm.AddObject(pEffect);
		dsMgr.playSound(rm.GetSoundBuffer(SOUND_ENEP));
	}
}