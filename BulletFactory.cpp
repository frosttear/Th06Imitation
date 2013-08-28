//--------------------------------------------------------------------------------------
//File: BulletFactory.cpp
//
//Desc: Define bullet factory class
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#include "BulletFactory.h"
#include "GameConstants.h"

Bullet& BulletFactory::GetBullet(D3DXVECTOR2 position, BULLET_SHAPE shape, int index)
{
	Bullet * pBullet = new Bullet();
	pBullet->SetPosition(position);
	RECT rect;
	int width  = 16;
	int height = 16;	
	switch (shape)
	{
	case BULLET_SHAPE_LASER:
		SetRect(&rect, index * 16, 16, (index + 1) * 16, 32);
		pBullet->SetCollisionType(COLLISION_RECT);
		pBullet->SetCollisionInfo(new CollisionRect());
		pBullet->SetInitRect(rect);
		pBullet->SetWippedRect(rect);
		pBullet->SetSrcRect(rect);
		break;
	case BULLET_SHAPE_CIRCLE:
		SetRect(&rect, index * 16, 32, (index + 1) * 16, 48);
		pBullet->SetSrcRect(rect);
		pBullet->SetCollisionType(COLLISION_CIRCLE);
		pBullet->SetCollisionInfo(new CollisionCircle(6));
		SetInitAndWippedRectOfSmallBullet(pBullet, index);
		break;
	case BULLET_SHAPE_SOLIDCIRCLE:
		SetRect(&rect, index * 16, 48, (index + 1) * 16, 64);
		pBullet->SetSrcRect(rect);
		pBullet->SetCollisionType(COLLISION_CIRCLE);
		pBullet->SetCollisionInfo(new CollisionCircle(7));
		SetInitAndWippedRectOfSmallBullet(pBullet, index);
		break;
	case BULLET_SHAPE_DIAMOND:
		SetRect(&rect, index * 16, 64, (index + 1) * 16, 80);
		pBullet->SetSrcRect(rect);
		pBullet->SetCollisionType(COLLISION_ELLIPSE);
		pBullet->SetCollisionInfo(new CollisionEllipse(4, 8));
		SetInitAndWippedRectOfSmallBullet(pBullet, index);
		break;
	case BULLET_SHAPE_LITTLE_KNIFE:
		SetRect(&rect, index * 16, 80, (index + 1) * 16, 96);
		pBullet->SetSrcRect(rect);
		pBullet->SetCollisionType(COLLISION_TRIANGLE);
		pBullet->SetCollisionInfo(new CollisionTriangle());
		SetInitAndWippedRectOfSmallBullet(pBullet, index);
		break;
	case BULLET_SHAPE_3D_DIAMOND:
		SetRect(&rect, index * 16, 96, (index + 1) * 16, 112);
		pBullet->SetSrcRect(rect);
		pBullet->SetCollisionType(COLLISION_ELLIPSE);
		pBullet->SetCollisionInfo(new CollisionEllipse(4, 8));
		SetInitAndWippedRectOfSmallBullet(pBullet, index);
		break;
	case BULLET_SHAPE_LIGHT_CIRCLE:
		width	= 32;
		height  = 32;
		SetRect(&rect, index * 32, 128, (index + 1) * 32, 160);
		pBullet->SetSrcRect(rect);
		pBullet->SetCollisionType(COLLISION_CIRCLE);
		pBullet->SetCollisionInfo(new CollisionCircle(14));
		SetInitAndWippedRectOfLargeBullet(pBullet, index);
		break;
	case BULLET_SHAPE_KNIFE:
		width	= 32;
		height  = 32;
		SetRect(&rect, index * 32, 160, (index + 1) * 32, 192);
		pBullet->SetSrcRect(rect);
		pBullet->SetCollisionType(COLLISION_RECT);
		pBullet->SetCollisionInfo(new CollisionRect());
		SetInitAndWippedRectOfLargeBullet(pBullet, index);
		break;
	case BULLET_SHAPE_FLAME:
		width	= 32;
		height  = 32;
		SetRect(&rect, 0, 192, (index + 1) * width, 232);
		pBullet->SetSrcRect(rect);
		pBullet->SetCollisionType(COLLISION_RECT);
		pBullet->SetCollisionInfo(new CollisionRect());
		pBullet->SetInitRect(rect);
		pBullet->SetWippedRect(rect);
		pBullet->SetSrcRect(rect);
		break;
	case BULLET_SHAPE_LITTLE_CIRCLE:
		width  = 8;
		height = 8;
		if (index < 8)
			SetRect(&rect, 128 + index * 8, 208, 128 + (index + 1)* 8, 216);
		else
			SetRect(&rect, 128 + (index - 8) * 8, 216, 128 + (index - 7) * 8, 224);
		pBullet->SetSrcRect(rect);
		pBullet->SetCollisionType(COLLISION_CIRCLE);
		pBullet->SetCollisionInfo(new CollisionCircle(4));
		SetInitAndWippedRectOfSmallBullet(pBullet, index);
		break;
	}
	return *pBullet;
}

RECT& BulletFactory::GetInitRect(RECT *pRect, int index)
{
	SetRect(pRect, index * 32, 224, (index + 1) * 32, 256);
	return *pRect;
}

RECT& BulletFactory::GetWippedRect(RECT *pRect, int index)
{
	SetRect(pRect, 144 + index * 16,112, 144 + (index + 1) * 16, 128);
	return *pRect;
}

void BulletFactory::SetInitAndWippedRectOfSmallBullet(Bullet * pBullet, int index)
{
	int initIndex	= 0;
	int wippedIndex = 0;
	switch (index)
	{
	case 0:
		initIndex	= 0;
		wippedIndex = 0;
		break;
	case 1:
	case 2:
		initIndex	= 1;
		wippedIndex = 1;
		break;
	case 3:
	case 4:
		initIndex	= 2;
		wippedIndex = 1;
		break;
	case 5:
	case 6:
		initIndex	= 3;
		wippedIndex = 2;
		break;
	case 7:
	case 8:
		initIndex	= 4;
		wippedIndex = 2;
		break;
	case 9:
	case 10:
	case 11:
		initIndex	= 5;
		wippedIndex = 3;
		break;
	case 12:
	case 13:
	case 14:
		initIndex	= 6;
		wippedIndex = 4;
		break;
	case 15:
		initIndex	= 7;
		wippedIndex = 0;
		break;
	default:
		break;
	}
	RECT rect;
	pBullet->SetInitRect(GetInitRect(&rect, initIndex)); 
	pBullet->SetWippedRect(GetWippedRect(&rect, wippedIndex));
}

void BulletFactory::SetInitAndWippedRectOfLargeBullet(Bullet * pBullet, int index)
{
	int initIndex	= 0;
	int wippedIndex	= 0;
	if (index >=0 && index <= 7)
		initIndex = index;
	else
		return;
	switch (index)
	{
	case 0:
		wippedIndex = 0;
		break;
	case 1:
	case 2:
		wippedIndex = 1;
		break;
	case 3:
	case 4:
		wippedIndex = 2;
		break;
	case 5:
		wippedIndex = 3;
		break;
	case 6:
		wippedIndex = 4;
		break;
	case 7:
		wippedIndex = 5;
		break;
	default:
		break;
	}
	RECT rect;
	pBullet->SetInitRect(GetInitRect(&rect, initIndex)); 
	pBullet->SetWippedRect(GetWippedRect(&rect, wippedIndex));
}