//--------------------------------------------------------------------------------------
//File: EnemyCreator.cpp
//
//Desc: 
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#include "EnemyCreator.h"
#include "GameManager.h"
#include <fstream>
#include "Stage1Enemy.h"
#include "MotionTrack.h"
using namespace std;
//--------------------------------------------------------------------------------------
//DESC:Constructor
//--------------------------------------------------------------------------------------
EnemyCreator::EnemyCreator()
{
	m_currentFrame = 0;
}
EnemyCreator::~EnemyCreator()
{
	ClearEnemy();
}
//--------------------------------------------------------------------------------------
//DESC:
//--------------------------------------------------------------------------------------
void EnemyCreator::CreateEnemy()
{
	for (unsigned int i = 0 ; i < (unsigned int)m_enemies[m_currentFrame].size(); i ++)
	{
		gm.AddEnemy(m_enemies[m_currentFrame][i]);
	}	
	++m_currentFrame;
	//if (m_enemies.size() > 0 && m_index < m_enemies.size() && m_enemies[m_index].size() >0)
	//{
	//	//reach the end of list
	//	if (m_index >= m_enemies.size()) 
	//		return;
	//	//not equal,return
	//	if (m_enemies[m_index][0]->GetCreateFrame() != currentFrame)
	//		return;
	//	//Add all enemies with the currentFrame	
	//	
	//	m_index ++;
	//}

}

void EnemyCreator::CreateBossOfStage(int stage)
{
	switch (stage)
	{
	case 1:
		if (m_currentFrame ==  700)
		{
			gm.AddEnemy(new Boss01());
		}
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	default:
		break;
	}
	
//	enemies.push_back(pBoss);
	//m_enemies.push_back(enemies);

}
//--------------------------------------------------------------------------------------
//DESC:Save ememy infos into filename
//--------------------------------------------------------------------------------------
void	EnemyCreator::SaveEnemy(const string filename)
{
	ofstream fout(filename.c_str(),ios_base::binary);
	//for (unsigned int i = 0 ; i < (unsigned int)m_enemies.size(); i ++)
	//{
	//	for (unsigned int j = 0; j < (unsigned int)m_enemies[i].size(); j ++)
	//	{
	//		fout.write((char *)(m_enemies[i][j]), sizeof (*m_enemies[i][j]));
	//	}
	//}
	for (unsigned int i = 0 ; i < MAX_FRAME; i ++)
	{
		for (unsigned int j = 0; j < (unsigned int)m_enemies[i].size(); j ++)
		{
			fout.write((char *)(m_enemies[i][j]), sizeof (*m_enemies[i][j]));
		}
	}
	fout.close();
	
}
//--------------------------------------------------------------------------------------
//DESC:Load enemy infos from filename
//--------------------------------------------------------------------------------------
void	EnemyCreator::LoadEnemy(const string filename)
{
	ifstream fin(filename.c_str(), ios_base::binary);
	ClearEnemy();
//	m_enemies.clear();
	
	//vector<Enemy *> enemies;
	Enemy * pEnemy = NULL;
	//int currentFrame = 0;
	while(!fin.eof())
	{
		pEnemy = new Enemy(TEXTURE_STG1ENM);
		fin.read((char*)(pEnemy), sizeof(*pEnemy));
	//	if (currentFrame == 0)
		//	currentFrame = pEnemy->GetCreateFrame();
		//if (currentFrame != pEnemy->GetCreateFrame())		
	//	{
		m_enemies[pEnemy->GetCreateFrame()].push_back(pEnemy);
			//m_enemies.push_back(enemies);
			//enemies.clear();
		//	currentFrame = pEnemy->GetCreateFrame();
	//	}
	//	enemies.push_back(pEnemy);
		
		
	}
	fin.close();
//	enemies.clear();
	pEnemy = NULL;
		
}
//--------------------------------------------------------------------------------------
//Create Enemy infos
//--------------------------------------------------------------------------------------
void	EnemyCreator::CreateEnemyOfStage(int stage)
{
	
	int i = 0;
	//vector<Enemy *> enemies;
	
	ClearEnemy();
	int n = 10;
	int interval	= 15;
	float posXLeft	= ACTIVE_RECT_LEFT;
	float posXRight = ACTIVE_RECT_RIGHT - 32;
	float radius	= 160;//ACTIVE_RECT_WIDTH * 0.333f * sqrtf(3.0f);
	D3DXVECTOR2 originLeft(ACTIVE_RECT_LEFT + 36, ACTIVE_RECT_TOP + 100);//ACTIVE_RECT_TOP + 100);//ACTIVE_RECT_TOP + 50);
	D3DXVECTOR2 originRight(ACTIVE_RECT_RIGHT - 68, ACTIVE_RECT_TOP + 100);
	float theta		= D3DX_PI * 0.5f;
	float deltaX	= 16;//160.0f / n;//ACTIVE_RECT_WIDTH * 0.5f / n;//radius * 0.5 * sqrtf(3.0f) / n;//ACTIVE_RECT_WIDTH * 0.5f / n;
	for (i = 200 ; i < 200 + interval * n; i += interval)
	{
		posXLeft	+=  deltaX;
		posXRight	-=	deltaX;
		//Left 
		Enemy_01_01 *pEnemy = new Enemy_01_01(D3DXVECTOR2(posXLeft ,ACTIVE_RECT_TOP), 0, 240);
		pEnemy->SetCreateFrame(i);
		float speed = 2;
		pEnemy->motionInfos.push_back(new MotionInfo(0, new LineTrack(D3DXVECTOR2(0, 1), speed, 0, 0), true));
		theta =  acosf((posXLeft - originLeft.x) / radius); //atanf(y / (posX - origin.x));
		float y	  =  radius * sinf(theta);
		float frame = (originLeft.y + y - ACTIVE_RECT_TOP) / speed;
		pEnemy->motionInfos.push_back(new MotionInfo((int)frame, new CircleTrack(theta, radius, speed, frame, true, originLeft)));
		m_enemies[i].push_back(pEnemy);
		//Right
		pEnemy = new Enemy_01_01(D3DXVECTOR2(posXRight ,ACTIVE_RECT_TOP), 0, 240);
		pEnemy->SetCreateFrame(i);
		pEnemy->motionInfos.push_back(new MotionInfo(0, new LineTrack(D3DXVECTOR2(0, 1), speed, 0, 0), true));
		pEnemy->motionInfos.push_back(new MotionInfo((int)frame, new CircleTrack(D3DX_PI - theta, radius, speed, frame, false, originRight)));
		m_enemies[i].push_back(pEnemy);
		
	}

	for (i = 500 ; i < 650; i += 40)
	{
		//enemies.clear();
		Enemy_01_02* pEnemy = new Enemy_01_02(D3DXVECTOR2(ACTIVE_RECT_LEFT  + 1.5f * ( i - 350 ),ACTIVE_RECT_TOP), 1);
		pEnemy->SetCreateFrame(i);
		pEnemy->SetBonusItemType(ITEM_TYPE_POWER);

		m_enemies[i].push_back(pEnemy);
		pEnemy = new Enemy_01_02(D3DXVECTOR2(ACTIVE_RECT_CENTER_X  + 1.5f * (i - 350),ACTIVE_RECT_TOP), 2);
		pEnemy->SetCreateFrame(i + 20);
		pEnemy->SetBonusItemType(ITEM_TYPE_POWER);
		m_enemies[i].push_back(pEnemy);
	}

	//for (i = 180 ; i < 230 ; i += 10)
	//{
	//	//enemies.clear();
	//	Enemy_01_01 * pEnemy = new Enemy_01_01(D3DXVECTOR2(ACTIVE_RECT_CENTER_X - 100,ACTIVE_RECT_TOP), 1, i - 160);
	//	pEnemy->SetCreateFrame(i);
	//	m_enemies[i].push_back(pEnemy);//enemies.push_back(pEnemy);
	//	pEnemy = new Enemy_01_01(D3DXVECTOR2(ACTIVE_RECT_CENTER_X - 100 + 32,ACTIVE_RECT_TOP), 2, i - 160);
	//	pEnemy->SetCreateFrame(i);
	//	m_enemies[i].push_back(pEnemy);//enemies.push_back(pEnemy);
	////	m_enemies.push_back(enemies);
	//}
	//for (i = 230 ; i < 371; i += 40)
	//{
	//	//enemies.clear();
	//	Enemy_01_02* pEnemy = new Enemy_01_02(D3DXVECTOR2(ACTIVE_RECT_LEFT + 100 + 1.5f * ( i - 230 ),ACTIVE_RECT_TOP), 1);
	//	pEnemy->SetCreateFrame(i);
	//	pEnemy->SetBonusItemType(ITEM_TYPE_POWER);

	//	m_enemies[i].push_back(pEnemy);//enemies.push_back(pEnemy);
	//	pEnemy = new Enemy_01_02(D3DXVECTOR2(ACTIVE_RECT_LEFT  + 200 + 1.5f * (i - 230),ACTIVE_RECT_TOP), 2);
	//	pEnemy->SetCreateFrame(i);
	//	//enemies.push_back(pEnemy);
	//	m_enemies[i].push_back(pEnemy);//m_enemies.push_back(enemies);
	//}
	

	SaveEnemy("stg1.std");
	
}

void	EnemyCreator::ClearEnemy()
{
	for (unsigned int i = 0; i < m_currentFrame ; i ++)
	{
		m_enemies[i].clear();
	}
	for (unsigned int i = m_currentFrame ; i < MAX_FRAME; i ++)
	{
		for (unsigned int j = 0; j  < m_enemies[i].size() ; j ++)
		{
			if (m_enemies[i][j] != NULL) 
			{
				delete m_enemies[i][j];
				m_enemies[i][j] = NULL;
			}
		}
		m_enemies[i].clear();
	}
	m_currentFrame = 0;
}