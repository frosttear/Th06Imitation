//--------------------------------------------------------------------------------------
//File: Collision.h
//
//Desc: help to check collistion
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once
#include <windows.h>
#include <d3dx9.h>

struct CollisionInfo
{
};

struct CollisionRect : CollisionInfo
{
	RECT rect;
};

struct CollisionCircle : CollisionInfo
{
	CollisionCircle(float radius)
	{
		this->radius = radius;
	}
	float		 radius;
	//D3DXVECTOR2  center;
};

struct CollisionEllipse : CollisionInfo
{
	CollisionEllipse(float majorAxis, float minorAxis)
	{
		this->majorAxis = majorAxis;
		this->minorAxis = minorAxis;
	}
	float		majorAxis;
	float		minorAxis;
	//D3DXVECTOR2  center;
};

struct CollisionTriangle : CollisionInfo
{
	D3DXVECTOR2  p1;
	D3DXVECTOR2  p2;
	D3DXVECTOR2  p3;
};

class Collision
{
public:
	//--------------------------------------------------------------------------------------
	//Check collision between two rects without rotation
	//--------------------------------------------------------------------------------------
	static bool CollisionRect(const RECT * pRect1, const RECT * pRect2);
	//--------------------------------------------------------------------------------------
	//Check collision between circle and rect
	//--------------------------------------------------------------------------------------
	static bool CollisionCircleRect(const RECT * pRect, float radius, const D3DXVECTOR2 * pCenter);
	//--------------------------------------------------------------------------------------
	//Check collision between circles
	//--------------------------------------------------------------------------------------
	static bool CollisionCircle(float radius1, const D3DXVECTOR2 * pCenter1,
											 float radius2, const D3DXVECTOR2 * pCenter2);
	static bool CollisionCircleEllipse(float radius, const D3DXVECTOR2 * pCircleCenter, 
													float a, float b, const D3DXVECTOR2 * pEllipseCenter, float rotation);

};