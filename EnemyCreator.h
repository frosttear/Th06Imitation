//--------------------------------------------------------------------------------------
//File: EnemyCreator.h
//
//Desc: used to load/save enemies creation info from/into files, And add enemies
//to game according current frame passed by the GameManager
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once
#include "Enemy.h"
#include "Boss.h"
#include <vector>
#define MAX_FRAME	65535
using namespace std;

class EnemyCreator
{
public:
	static EnemyCreator&	GetInstance(){ static EnemyCreator instance; return instance;}
							~EnemyCreator();
	//--------------------------------------------------------------------------------------
	//Load/Save Enemy From/Into file
	//--------------------------------------------------------------------------------------
	void					LoadEnemy(const string filename);
	void					SaveEnemy(const string filename);
	//--------------------------------------------------------------------------------------
	//Add Enemy to the game
	//--------------------------------------------------------------------------------------
	void					CreateEnemy();
	void					CreateEnemyOfStage(int stage);
	void					CreateBossOfStage(int stage);
	void					ClearEnemy(void);

private:
							EnemyCreator();
	unsigned int			m_currentFrame;
	//Enemies is saved in this vector while sorted by create-frame 
	vector<Enemy*>			m_enemies[MAX_FRAME];
	//vector<vector<Enemy *>> m_enemies;
	vector<Boss *>			m_bosses;
};
static EnemyCreator& ec = EnemyCreator::GetInstance();