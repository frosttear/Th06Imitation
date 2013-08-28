//--------------------------------------------------------------------------------------
//File: Emitter.h
//
//Desc: Describes how to shoot bullets
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once
#include <d3dx9.h>
#include "BulletFactory.h"
class Emitter
{
public:
	static void		Circle(const D3DXVECTOR2 &position, int lineNum, float startAngle, float radius, BULLET_SHAPE bulletShape, int bulletIndex, float speed, int delay);
	/*				Emitter(const D3DXVECTOR2 &position = D3DXVECTOR2(0,0));
					~Emitter(void);
	void			SetPosition(const D3DXVECTOR2 &position){m_position = position;}
	D3DXVECTOR2		GetPosition() const {return m_position;}
	virtual void	Shoot(BULLET_SHAPE bulletShape, int bulletIndex, float speed, int delay) = 0;*/
//protected:
//	D3DXVECTOR2		m_position;
};
//--------------------------------------------------------------------------------------
//CircleEmitter: create bullet around the emitter in a circle shape
//--------------------------------------------------------------------------------------
//class CircleEmitter : public Emitter
//{
//public:
//					CircleEmitter(const D3DXVECTOR2 &position, int lineNum, float startAngle, float radius = 0);
//	virtual void	Shoot();
//	void			SetStartAngle(float angle){ m_startAngle = angle;}
//	void			SetRadius(float radius) { m_radius = radius;}
//	void			SetLineNum(int lineNum) { m_lineNum = lineNum;}
//private:
//	int				m_lineNum;
//	float			m_radius;
//	float			m_startAngle;
//};
