//--------------------------------------------------------------------------------------
//File: MotionTrack.cpp
//
//Desc: Defines different motion track
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#include "GameObject.h"
#include "MotionTrack.h"
//--------------------------------------------------------------------------------------
//Class MotionTrack,base class
//--------------------------------------------------------------------------------------
MotionTrack::MotionTrack(const D3DXVECTOR2 &direction, float speed, float t0 , const D3DXVECTOR2 &offset)
{
	m_direction = direction;
	m_speed		= speed;
	m_t0		= t0;
	m_offset	= offset;

}

void MotionTrack::FormatDirection()
{
	float x = m_direction.x;
	float y = m_direction.y;
	float length = sqrt(x * x + y * y);
	if (abs(length) > 0.000000001)
	{
		m_direction.x = x / length;
		m_direction.y = y / length;
	}else
	{
		m_direction.x = 0;
		m_direction.y = 0;
	}
}

void MotionTrack::Move(GameObject *pObject, float t)
{
	pObject->SetPosition(GetAbsolutePosition(t));
}

StaticTrack::StaticTrack(float t0, const D3DXVECTOR2 &offset)
			:MotionTrack(D3DXVECTOR2(0, 0), 0, t0, offset)
{
}

D3DXVECTOR2 StaticTrack::GetRelativePosition(float t) const
{
	return D3DXVECTOR2(0, 0);
}
//--------------------------------------------------------------------------------------
//Class LineTrack
//--------------------------------------------------------------------------------------
LineTrack::LineTrack(const D3DXVECTOR2 &direction, float speed, float accelerator, float t0, const D3DXVECTOR2 &offset)
			:MotionTrack(direction, speed, t0, offset)
{
	m_accelerator = accelerator;
	FormatDirection();
}

//--------------------------------------------------------------------------------------
//line: x = offset.x +  direction.x * (speed * t + 0.5 * a * t ^ 2)
//--------------------------------------------------------------------------------------
D3DXVECTOR2 LineTrack::GetRelativePosition(float t) const
{
	int deltaT = t - m_t0;
	float s    = m_speed * deltaT + (float)0.5  * m_accelerator * deltaT * deltaT;
	return (s * m_direction);
}
//--------------------------------------------------------------------------------------
//Class CircleTrack
//--------------------------------------------------------------------------------------
CircleTrack::CircleTrack(float theta0, float r0, float speed, float t0, bool bIsClockwise,const D3DXVECTOR2 &offset)
			:MotionTrack(D3DXVECTOR2(cos(theta0), sin(theta0)), speed, t0, offset)
{
	m_theta0		= theta0;
	m_r0			= r0;
	m_bIsClockwise	= bIsClockwise;
}
//--------------------------------------------------------------------------------------
//circle:x = offset.x + rcos(theta0 + t * v / r), y = offset.y + rsin(theta0 + t * v / r)
//--------------------------------------------------------------------------------------
D3DXVECTOR2 CircleTrack::GetRelativePosition(float t) const
{
	if (m_r0 != 0)
	{
		int   deltaT	= m_bIsClockwise ? t - m_t0 : m_t0 - t;
		float theta		= m_theta0 + m_speed * deltaT / m_r0;
		return D3DXVECTOR2(m_r0 * cos(theta), m_r0  * sin(theta));
	}else
	{
		return m_offset;
	}
}

SinTrack::SinTrack(float amplitude, float theta0, float speed, float t0, const D3DXVECTOR2 &offset)
		:MotionTrack(D3DXVECTOR2(0,0), speed, t0, offset)
{
	m_amplitude = amplitude;
	m_theta0	= theta0;
}

D3DXVECTOR2 SinTrack::GetRelativePosition(float t) const
{
	float x = m_speed * (t - m_t0) + m_theta0;
	return D3DXVECTOR2(x, m_amplitude * sin(x));
}