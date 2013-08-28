//--------------------------------------------------------------------------------------
//File: Stage1Enemy.h
//
//Desc: Include enemies in stage 1
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once
#include "Enemy.h"

class Enemy_01_01	:	public Enemy
{
public:
			Enemy_01_01(D3DXVECTOR2 &position, int actionMode = 1, int startShootFrame = 20);
	void	Update();
	void	Shoot();
	void	OnWipped();
};

class Enemy_01_02	:	public Enemy
{
public :
			Enemy_01_02(D3DXVECTOR2 &position,int actionMode = 1, int startShootFrame = 30);
	void	Update();
	void	Shoot();
	void	OnWipped();

};