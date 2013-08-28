//--------------------------------------------------------------------------------------
//File: BulletFactory.h
//
//Desc: Class Bullet Factory ,abstract class to create a bullet
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once
#include "d3dx9.h"
#include "Bullet.h"
class GameObject;

class BulletFactory
{
public:
		static Bullet&		GetBullet(D3DXVECTOR2 position, BULLET_SHAPE shape, int index);
		static RECT&		GetInitRect(RECT *pRect, int index);
		static RECT&		GetWippedRect(RECT *pRect, int index);
		static void			SetInitAndWippedRectOfSmallBullet(Bullet *pBullet, int index);
		static void			SetInitAndWippedRectOfLargeBullet(Bullet *pBullet, int index);
};