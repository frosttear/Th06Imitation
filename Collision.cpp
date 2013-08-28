//--------------------------------------------------------------------------------------
//File: Collision.cpp
//
//Desc: 
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#include "Collision.h"

//--------------------------------------------------------------------------------------
//DESC:Check intersect between two rects without rotation
//--------------------------------------------------------------------------------------
bool Collision::CollisionRect(const RECT * pRect1, const RECT * pRect2)
{
	if (pRect1->left > pRect2->right)  //rect1 right of rect 2
		return false;
	if (pRect1->right < pRect2->left ) //rect2 right of rect1
		return false;
	if (pRect1->top > pRect2->bottom)
		return false;
	if (pRect1->bottom < pRect2->top)
		return false;
	
	return true;
}
bool Collision::CollisionCircleRect(const RECT * pRect, float radius, const D3DXVECTOR2 * pCenter)
{
	if (pCenter->x >= pRect->left && pCenter->x <= pRect->right && pCenter->y >= pRect->top && pCenter->y <= pRect->bottom)
		return true;
	float dx = min(abs(pCenter->x - pRect->left), abs(pCenter->x - pRect->right));
	float dy = min(abs(pCenter->y - pRect->top), abs(pCenter->y - pRect->bottom));
	if (dx > radius || dy > radius)
		return false;
	return true;

}

bool Collision::CollisionCircle(float radius1, const D3DXVECTOR2 * pCenter1, float radius2, const D3DXVECTOR2 * pCenter2)
{
	return (radius1  + radius2 )* (radius1 + radius2) > 
		(pCenter1->x - pCenter2->x) * (pCenter1->x - pCenter2->x) + (pCenter1->y - pCenter2->y) * (pCenter1->y - pCenter2->y);
}

bool Collision::CollisionCircleEllipse(float radius, const D3DXVECTOR2 * pCircleCenter, 
													float a, float b, const D3DXVECTOR2 * pEllipseCenter, float rotation)
{
	//reduce check range
	if (!CollisionCircle(radius, pCircleCenter, max(a, b), pEllipseCenter))
		return false;
	if (CollisionCircle(radius, pCircleCenter, min(a, b), pEllipseCenter))
		return true;
	
	float powerLength = (pEllipseCenter->x - pCircleCenter->x) * (pEllipseCenter->x - pCircleCenter->x)
						+ (pEllipseCenter->y - pCircleCenter->y) * (pEllipseCenter->y - pCircleCenter->y);
	float sinRotation = sin(rotation);
	float cosRotation = cos(rotation);
	if (powerLength * (b + radius) * (b + radius) *  sinRotation * sinRotation 
		+ powerLength  * (a + radius) * (a + radius) * cosRotation * cosRotation >= (a + radius) * (a + radius) * (b + radius) * (b + radius))
		return false;
	return true;
}
