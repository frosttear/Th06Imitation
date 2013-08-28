//--------------------------------------------------------------------------------------
//File: MotionTrack.h
//
//Desc: Help objects to move around a certain track 
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once
#include <d3dx9.h>
//struct D3DXVECTOR2;
class  GameObject;
class MotionTrack
{
public:
							MotionTrack(const D3DXVECTOR2 &direction, float speed, float t0 , const D3DXVECTOR2 &offset = NULL_POSITION);
	//Move object to the position in the track at t time
	void					Move(GameObject * pObject, float t);
	virtual D3DXVECTOR2		GetRelativePosition(float t) const = 0;
	D3DXVECTOR2				GetAbsolutePosition(float t) const{ return GetRelativePosition(t) + m_offset;}
	void					SetDirection(const D3DXVECTOR2 &direction)	{ m_direction = direction; FormatDirection();}
	D3DXVECTOR2				GetDirection()	const	{ return m_direction;	}	
	float					GetT0()			const	{ return m_t0;			}
	void					SetT0(float t0)			{ m_t0 = t0;}
	void					SetOffset(const D3DXVECTOR2 &offset)	{ m_offset = offset;}
	D3DXVECTOR2				GetOffset()		const	{ return m_offset;		}	
protected:
	//Format the direction vector (x,y) to a standard direction: (x / length, y / length)
	void					FormatDirection();
	float					m_t0;				//the init time
	D3DXVECTOR2				m_direction;		//the init direction
	float					m_speed;			//the init speed
	D3DXVECTOR2				m_offset;			//the offset to (0,0)
};

class StaticTrack : public MotionTrack
{
public:
					StaticTrack(float t0, const D3DXVECTOR2 &offset = NULL_POSITION);
	// void			Move(GameObject * pObject, int t);
	 D3DXVECTOR2	GetRelativePosition(float t)	const;

};

class LineTrack   : public MotionTrack
{
public:
					LineTrack(const D3DXVECTOR2 &direction, float speed, float accelerator, float t0, const D3DXVECTOR2 &offset = NULL_POSITION);
	 D3DXVECTOR2	GetRelativePosition(float t) const;
	float			GetAccelerator() const	{ return m_accelerator;}
private:
	float			m_accelerator;
};

class CircleTrack  : public MotionTrack
{
public:
					CircleTrack(float theta0, float r0, float speed, float t0 , bool bIsClockwise = true, const D3DXVECTOR2 &offset = NULL_POSITION);
	D3DXVECTOR2		GetRelativePosition(float t) const;
	void			SetTheta0(float theta0)	{ m_theta0 = theta0;}
	float			GetTheta0()		const	{ return m_theta0;	}	
	float			GetR0()			const	{ return m_r0;		}	

private:
	float			m_theta0;			//init direction, expressed in degree
	float			m_r0;				
	bool			m_bIsClockwise;		
};	

class SinTrack	: public MotionTrack
{
public:
					SinTrack(float amplitude, float theta0, float speed, float t0, const D3DXVECTOR2 &offset = NULL_POSITION);
	D3DXVECTOR2		GetRelativePosition(float t)	const;
	void			SetTheta0(float theta0)	{ m_theta0 = theta0;}
	float			GetTheta0()		const	{ return m_theta0;	}	

private:
	float			m_amplitude;
	float			m_theta0;
};