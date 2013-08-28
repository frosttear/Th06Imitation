//--------------------------------------------------------------------------------------
//File: Emitter.cpp
//
//Desc: Include all shoot modes
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#include "Emitter.h"
#include "GameManager.h"

//Emitter::Emitter(const D3DXVECTOR2 &position)
//{
//	m_position		= position;
//}
//
//Emitter::~Emitter(void)
//{
//}
//
//CircleEmitter::CircleEmitter(const D3DXVECTOR2 &position, int lineNum, float startAngle, float radius) : Emitter(position)
//{
//	m_lineNum		= lineNum;
//	m_startAngle	= startAngle;
//	m_radius		= radius;
//}
//
//void CircleEmitter::Shoot(BULLET_SHAPE bulletShape, int bulletIndex, float speed, int delay)
//{
//	float angle = m_startAngle;
//	float delta = 2 * D3DX_PI / m_lineNum;
//	for (int i = 0; i < m_lineNum; i ++)
//	{
//		D3DXVECTOR2	direction(cosf(angle),sinf(angle));
//		Bullet* pBullet = &BulletFactory::GetBullet(m_position + m_radius *direction, bulletShape, bulletIndex);
//		pBullet->motionInfos.push_back(new MotionInfo(delay, new LineTrack(direction, speed, 0, delay), true));
//		pBullet->SetRotationAngle(angle);
//		gm.AddBullet(pBullet);
//		angle += delta;
//	}
//}
void Emitter::Circle(const D3DXVECTOR2 &position, int lineNum, float startAngle, float radius, BULLET_SHAPE bulletShape, int bulletIndex, float speed, int delay)
{
	float angle = startAngle;
	float delta = 2 * D3DX_PI / lineNum;
	for (int i = 0; i < lineNum; i ++)
	{
		D3DXVECTOR2	direction(cosf(angle),sinf(angle));
		Bullet* pBullet = &BulletFactory::GetBullet(position + 10 * direction, bulletShape, bulletIndex);

		pBullet->motionInfos.push_back(new MotionInfo(1, new StaticTrack(1, position + radius *direction)));
		int frame = delay > 1 ? delay : 2;
		pBullet->motionInfos.push_back(new MotionInfo(frame, new LineTrack(direction, speed, 0, (float)frame), true));
		pBullet->SetRotationAngle(angle);
		gm.AddBullet(pBullet);
		angle += delta;
	}
}