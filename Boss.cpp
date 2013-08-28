//--------------------------------------------------------------------------------------
//File: Boss.cpp
//
//Desc: 
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#include "Boss.h"
#include "SpellCard.h"
#include "Player.h"
#include "Bullet.h"
#include "GameManager.h"
#include "Item.h"
#include "Effect.h"
#include "Emitter.h"
//--------------------------------------------------------------------------------------
//BossPhase Struct,describes infos of a boss phase
//--------------------------------------------------------------------------------------
BossPhase::BossPhase(int minHp, int maxHp, SpellCard *pSpellCard, int countdown, int loopFrame)
{
	this->minHp		= minHp;
	this->maxHp		= maxHp;
	if (pSpellCard != NULL)
	{
		this->countdown		= pSpellCard->GetCountdown();
		this->loopFrame		= pSpellCard->GetLoopFrame();
	}else
	{
		this->countdown		= countdown;
		this->loopFrame		= loopFrame;
	}
	this->pSpellCard= pSpellCard;
}
BossPhase::~BossPhase()
{
	for (int i = (unsigned int)motionInfos.size() - 1; i >= 0; --i)
	{
		MotionInfo* pInfo = motionInfos[i];
		motionInfos.pop_back();
		SAFE_DELETE(pInfo);
	}
	SAFE_DELETE(pSpellCard);
}
//--------------------------------------------------------------------------------------
//Class Boss 
//--------------------------------------------------------------------------------------
Boss::Boss() : Enemy(TEXTURE_STG1BOSS)
{
	m_maxHp			= 0;
	m_state			= BOSS_STATE_INIT;
	m_actionState	= BOSSACTION_NORMAL;
	m_isInvincible  = false;
	m_shootMode		= 0;
	m_loopCount		= 0;
	m_shootFrame	= 0;
	m_remainHpNum   = 0;
	m_normalBackground	= gm.GetBackground();
}

Boss::Boss(unsigned int id, std::string name) : Enemy(TEXTURE_STG1BOSS)
{
	m_id				= id;
	m_name				= name;
	m_state				= BOSS_STATE_INIT;
	m_actionState		= BOSSACTION_NORMAL;
	m_maxHp				= 0;
	m_isInvincible		= false;
	m_shootMode			= 0;
	m_loopCount			= 0;
	m_shootFrame		= 0;
	m_score				= 100000;
	m_remainHpNum		= 0;
	m_v					= 1;
	m_normalBackground	= gm.GetBackground();
}

Boss::~Boss()
{
	//clear phase
	for (unsigned int i = 0; i < m_phases.size(); ++i)
	{
		SAFE_DELETE(m_phases[i]);
	}
}
void Boss::Set(unsigned int hp, D3DXVECTOR2 position)
{
	m_hp			= hp;
	m_maxHp			= hp;
	m_position		= position;
}

void Boss::NormalStateUpdate(void)
{
	//decide how to move and shoot
	if (m_phases[m_phaseIndex]->pSpellCard != NULL)
	{
		m_phases[m_phaseIndex]->pSpellCard->Update();
	}
	GameObject::Update();
	if (m_elapsedFrame > m_phases[m_phaseIndex]->loopFrame)
	{
		m_elapsedFrame = 0;
		motionIndex  = 0;
		++m_loopCount;
	}
	m_countdown --;
	if (m_countdown == 0)//force to change phase
	{
		OnChangePhase();
	}
}
void Boss::Update()
{
	switch (m_state)
	{
	case BOSS_STATE_INIT:
		InitStateUpdate();
		break;
	case BOSS_STATE_NORMAL:
		NormalStateUpdate();
		Shoot();
		break;
	case BOSS_STATE_DIE:
		DieStateUpdate();
		break;
	default:
		break;
	}

	//Set Action State to decide which action should be rendered
	if (m_pMotionInfo != NULL)
	{
		D3DXVECTOR2 nextPosition = m_pMotionInfo->pTrack->GetAbsolutePosition(m_elapsedFrame + 1);
		if (nextPosition.x > m_position.x)
		{
			ChangeActionState(BOSSACTION_MOVERIGHT);
		}else
		{
			if (nextPosition.x < m_position.x)
			{
				ChangeActionState(BOSSACTION_MOVELEFT);
			}else
			{
				ChangeActionState(BOSSACTION_NORMAL);
			}
		}

	}else
	{
		ChangeActionState(BOSSACTION_NORMAL);
	}
}

void Boss::OnChangePhase()
{
	if (m_phaseIndex + 1 < m_phases.size())
	{
		if (m_phases[m_phaseIndex]->minHp == 0)
			m_remainHpNum--;
		++m_phaseIndex;
		m_hp			= m_phases[m_phaseIndex]->maxHp;
		m_countdown		= m_phases[m_phaseIndex]->countdown;
		m_state			= BOSS_STATE_INIT;
		m_elapsedFrame	= 0;
		m_isInvincible	= true;
		if (m_phases[m_phaseIndex]->pSpellCard != NULL)
			gm.SetBackground(m_spellBackground);
		else
			gm.SetBackground(m_normalBackground);
		}
	else
	{
		OnDying();
	}
	dsMgr.playSound(rm.GetSoundBuffer(SOUND_ENEP_01));

	//TODO:Add codes to Change All Bullets to Star Item,and then auoto fly to player.
	gm.ChangeBulletsToStars();
	
}

//--------------------------------------------------------------------------------------
//Render boss hp bar
//--------------------------------------------------------------------------------------
void Boss::RenderHpbar()
{
	ID3DXSprite * pSprite = dxMgr.GetSprite();
	RECT rect;
	D3DXMATRIX transMatrix;
	D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,NULL,NULL, 0.0f, &D3DXVECTOR2(ACTIVE_RECT_LEFT, ACTIVE_RECT_TOP));
	pSprite->SetTransform(&transMatrix);
	SetRect(&rect, 0, 144, 48, 160);	//enemy text
	pSprite->Draw(rm.GetTexture(TEXTURE_FRONT), &rect,NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	gm.RenderNumber(m_remainHpNum, 2, &D3DXVECTOR2(ACTIVE_RECT_LEFT + 48 , ACTIVE_RECT_TOP));
	SetRect(&rect, 48, 148, 49, 152);	//hp bar img
	unsigned int i = 0;
	for (i = 0 ; i < m_hp *  (ACTIVE_RECT_WIDTH - 128) / m_maxHp; i ++)
	{
		D3DXMatrixTransformation2D(&transMatrix, NULL, 0.0f,NULL,NULL, 0.0f, &D3DXVECTOR2(ACTIVE_RECT_LEFT + 48 + 32 + (float)i, ACTIVE_RECT_TOP + 8));
		pSprite->SetTransform(&transMatrix);
		pSprite->Draw(rm.GetTexture(TEXTURE_FRONT), &rect,NULL,NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	D3DCOLOR color = m_countdown <= 10 * 60 ? D3DCOLOR_ARGB(255, 255, 0, 0):D3DCOLOR_ARGB(255, 255, 255, 255);
	gm.RenderNumber(m_countdown / 60, 2, &D3DXVECTOR2(ACTIVE_RECT_RIGHT - 48 , ACTIVE_RECT_TOP),color);
}

void Boss::OnHit(GameObject * pObject)
{
	if (typeid(*pObject).name() != typeid(Player).name() && !m_isInvincible)
	{
		Bullet* pBullet = (Bullet*) pObject;
		m_hp	-= pBullet->GetPower();
		if (m_hp <= m_phases[m_phaseIndex]->minHp)
		{
			OnChangePhase();
		}
		gm.AddScore(100);
	}
}

void Boss::OnDying()
{
	gm.SetBackground(m_normalBackground);
	m_state		   = BOSS_STATE_DIE;
	ChangeActionState(BOSSACTION_NORMAL);
	m_elapsedFrame = 0;
	gm.AddObject(new EffectWhiteCircle(GetCenter()));

}

void Boss::ChangeActionState(BOSSACTION_STATE actionState)
{
	if (m_actionState != actionState)
	{
		m_actionState = actionState;
		SetBossSprite(actionState);
	}
}

//--------------------------------------------------------------------------------------
//Class Boss01
//
//This is a test boss.It has 4 phases indexed from 0 to 3, while phase 1 and phase 3 is 
//controlled by Spell Card 01 and 02.
//
//
//--------------------------------------------------------------------------------------
Boss01::Boss01()	: Boss(1, "Boss1")
{
	m_position.x	= ACTIVE_RECT_CENTER_X;
	m_position.y	= ACTIVE_RECT_TOP;
	m_textureType	= TEXTURE_STG1BOSS;
	SetBossSprite(m_actionState);
	m_hp			= 250;
	m_maxHp			= 250;
	m_v				= 3;
	m_remainHpNum   = 1;
	//Set phase0
	BossPhase *pPhase = new BossPhase(100, 250, NULL, 24 * 60, 720);
	pPhase->motionInfos.push_back(new MotionInfo(0, new StaticTrack(0,  D3DXVECTOR2(ACTIVE_RECT_CENTER_X + 100, ACTIVE_RECT_TOP + 150)), false));
	pPhase->motionInfos.push_back(new MotionInfo(120, new LineTrack(D3DXVECTOR2(-sqrt(3.0f), -1), m_v, 0, 120), true));
	pPhase->motionInfos.push_back(new MotionInfo(180, new StaticTrack(180), true));
	pPhase->motionInfos.push_back(new MotionInfo(300, new LineTrack(D3DXVECTOR2(-sqrt(3.0f), 1), m_v, 0, 300), true));
	pPhase->motionInfos.push_back(new MotionInfo(360, new StaticTrack(360), true));
	pPhase->motionInfos.push_back(new MotionInfo(480, new LineTrack(D3DXVECTOR2(sqrt(3.0f), -1), m_v, 0, 480), true));
	pPhase->motionInfos.push_back(new MotionInfo(540, new StaticTrack(540), true));
	pPhase->motionInfos.push_back(new MotionInfo(660, new LineTrack(D3DXVECTOR2(sqrt(3.0f), 1), m_v, 0, 660), true));
	pPhase->motionInfos.push_back(new MotionInfo(720, new StaticTrack(720), true));
	m_phases.push_back(pPhase);

	//Set phase1  -- Spell Card 01
	pPhase = new BossPhase(0, 100, new SpellCard01(this));
	m_phases.push_back(pPhase);
	
	//Set phase2 
	pPhase = new BossPhase(150, 250, NULL, 20 * 60, 120);
	pPhase->motionInfos.push_back(new MotionInfo(0, new LineTrack(D3DXVECTOR2(-1, 0), m_v, 0, 0, D3DXVECTOR2(ACTIVE_RECT_CENTER_X - 50, ACTIVE_RECT_TOP + 150)), false));
	pPhase->motionInfos.push_back(new MotionInfo(60, new LineTrack(D3DXVECTOR2(1, 0), m_v, 0, 60), true));
	pPhase->motionInfos.push_back(new MotionInfo(120, new StaticTrack(120), true));
	m_phases.push_back(pPhase);

	//Set phase3
	pPhase = new BossPhase(0, 150, new SpellCard02(this));
	//pPhase->motionInfos = m_spellCards[1]->GetMotionInfos();
	m_phases.push_back(pPhase);
	m_phaseIndex = 0;
	m_countdown	 = m_phases[0]->countdown;

	m_spellBackground = rm.GetTexture(TEXTURE_EFF_01);
}

//--------------------------------------------------------------------------------------
//When phase changes, move boss to the right init position
//--------------------------------------------------------------------------------------
void Boss01::InitStateUpdate(void)
{
	if (m_elapsedFrame == 0)
	{
		motionInfos.clear();
		
		D3DXVECTOR2 transportVector; //the init position of current phase 
		MotionInfo *pInfo = NULL;
		int			t	  = 0;
		if (m_phases[m_phaseIndex]->pSpellCard == NULL)
		{
			pInfo = m_phases[m_phaseIndex]->motionInfos[0];
		}
		else
		{
			pInfo =  m_phases[m_phaseIndex]->pSpellCard->GetMotionInfos()[0];
		}
		
		transportVector  = pInfo->pTrack->GetAbsolutePosition(0) - m_position;
		
		
		t = (int) (sqrt(transportVector.x * transportVector.x + transportVector.y * transportVector.y) / m_v);
		motionInfos.push_back(new MotionInfo(0, new LineTrack(transportVector, m_v, 0, 0), true));
		motionInfos.push_back(new MotionInfo(t, new StaticTrack(t), true));
		motionIndex = 0;
	}
	if (m_elapsedFrame == motionInfos[1]->keyFrame) //it shows boss has been moved to the right position
	{
		ClearMotionInfo();
		if (m_phases[m_phaseIndex]->pSpellCard != NULL)
		{
			motionInfos = m_phases[m_phaseIndex]->pSpellCard->GetMotionInfos();
		}
		else
		{
			motionInfos = m_phases[m_phaseIndex]->motionInfos;
		}
		motionIndex		= 0;
		m_pMotionInfo   = motionInfos[0];
		m_elapsedFrame	= 0;
		m_isInvincible	= false;
		m_state			= BOSS_STATE_NORMAL;

	}else
	{
		GameObject::Update();
	}
	
}

void Boss01::NormalStateUpdate(void)
{
	Boss::NormalStateUpdate();
}

void Boss01::DieStateUpdate()
{
	GameObject::Update();
	if (!m_bIsValid)
	{
		gm.OnStageClear();
	}
}

void Boss01::Render(ID3DXSprite * pSprite)
{
	if (m_state != BOSS_STATE_DIE)
	{
		Boss::RenderHpbar();
	}
	D3DXMATRIX transMatrix;
	D3DXVECTOR2 centerVector(m_width / 2.0f , m_height / 2.0f);
	if (m_actionState == BOSSACTION_MOVELEFT)
	{
		D3DXMATRIX rotMatrix;
		D3DXMatrixRotationY(&rotMatrix, D3DXToRadian(180));
		D3DXMatrixTransformation2D(&transMatrix, &centerVector, 0.0f, &m_scaleMatrix,NULL, 0.0f, &D3DXVECTOR2(m_position.x +  m_width, m_position.y));
		D3DXMatrixMultiply(&transMatrix,&rotMatrix,&transMatrix);	
	}else
	{
		D3DXMatrixTransformation2D(&transMatrix, &centerVector, 0.0f,&m_scaleMatrix, NULL, 0.0f, &m_position);
	}
	pSprite->SetTransform(&transMatrix);
	m_pSprite->Render(pSprite, rm.GetTexture(m_textureType), m_color);
	
}
void Boss01::OnWipped()
{
	Enemy::OnWipped();
}

void Boss01::OnDying()
{
	Boss::OnDying();
	motionInfos.clear();
	motionInfos.push_back(new MotionInfo(m_elapsedFrame + 1, 
		new LineTrack(D3DXVECTOR2(0, -1), 4, 0, m_elapsedFrame + 1, NULL_POSITION), true));
	motionIndex = 0;
	m_shootMode = 0;
	m_isInvincible = true;
	gm.AddScore(m_score);
	for (int i = 0; i < 4; i ++)
	{
		gm.AddItem(&ItemFactory::GetItem(ITEM_TYPE_POWER,
			D3DXVECTOR2(ACTIVE_RECT_CENTER_X - i * 30.0f, m_position.y)));
	}
	gm.AddItem(&ItemFactory::GetItem(ITEM_TYPE_BIGPOWER, D3DXVECTOR2(ACTIVE_RECT_CENTER_X - 5 * 30, m_position.y)));
}
//--------------------------------------------------------------------------------------
//Called after normal update.
//--------------------------------------------------------------------------------------
void Boss01::Shoot(void)
{
	int shootInterval = 0;		
	float theta = 0;			//init bullet direction 
	int shootCount = 0;			//
	int bulletIndex = 0;		
	switch (GetCurrentShootMode())
	{
	case 1:
	//射击模式1:向外射出放射状子弹。第一次只射出蓝色子弹，第二次进入该模式后，额外射出红色子弹。
		shootInterval = 2;
		shootCount	  = m_shootFrame / shootInterval ;
		if (m_shootFrame % shootInterval == 0 && shootCount < 3 * (1 + m_loopCount))
		{
			dsMgr.playSound(rm.GetSoundBuffer(SOUND_POWER_1));
			if (shootCount < 3)
			{
				bulletIndex = 5;
				theta		= 0;
			}
			else
			{
				bulletIndex = 1;
				theta		= D3DX_PI * (1.0f / 36);
			}
			Emitter::Circle(this->GetCenter(), 16, theta, 5, BULLET_SHAPE_SOLIDCIRCLE, bulletIndex, 3 - shootCount * 0.2f, 0);
		}
		m_shootFrame ++;
		break;
	case 2:
	//射击模式2:射出5圈五彩米粒弹,起始呈圆形放射状排列，当排列完成后，向外沿半径方向向外射出
		shootInterval = 10;
		shootCount	  = m_shootFrame / shootInterval;
		if (m_shootFrame % shootInterval == 0 && shootCount < 5)
		{
			theta = -D3DX_PI * (1.0f / 36) * shootCount;
			dsMgr.playSound(rm.GetSoundBuffer(SOUND_TAN_01));
			int bulletIndex = shootCount;
			float radius = 20 + shootCount * 10.0f;		
			int   delay  = (5 - shootCount) * shootInterval;
			Emitter::Circle(this->GetCenter(), 12, theta, radius, BULLET_SHAPE_LITTLE_CIRCLE, bulletIndex, 3, delay);
		}
		m_shootFrame ++;
		break;
	case 3:
	//射击模式3:类似1，放射状射出黄色和绿色弹
		shootInterval = 2;
		shootCount	  = m_shootFrame / shootInterval;
		if (m_shootFrame % shootInterval == 0 && (shootCount < 3 || shootCount > 15 && shootCount < 19))
		{
			dsMgr.playSound(rm.GetSoundBuffer(SOUND_POWER_1));

			float speed = 3;
			if (shootCount < 3)
			{
				bulletIndex = 13;
				theta		= 0;
				speed		-= shootCount * 0.2f;

			}else
			{
				bulletIndex = 8;
				theta		= D3DX_PI * (1.0f / 36);
				speed		-= (shootCount - 15) * 0.2f;
			}
			Emitter::Circle(this->GetCenter(), 16, theta, 5, BULLET_SHAPE_SOLIDCIRCLE, bulletIndex, speed, 0);
		}
		m_shootFrame ++;
		break;
	case 0:	// do not shoot
	default:
		m_shootFrame = 0;
		break;
	}
}

void Boss01::SetBossSprite(BOSSACTION_STATE actionState)
{
	RECT srcRect;
	switch (actionState)
	{
	case BOSSACTION_NORMAL:
		SetRect(&srcRect, 0, 0, 128, 48);
		SetSprite(srcRect, 4, 8,32, 48 ,false);
		break;
	case BOSSACTION_MOVELEFT:
	case BOSSACTION_MOVERIGHT:
		SetRect(&srcRect, 0, 48, 96, 96);
		SetSprite(srcRect, 3, 8,32, 48 ,false);
		break;
	case BOSSACTION_SPELLSHOOT:
		SetRect(&srcRect, 224, 0, 256, 48);
		SetSprite(srcRect, 1, 0,32, 48 ,false);
		break;
	}
}
//--------------------------------------------------------------------------------------
//Shoot Mode is decided by current phase and current elapsedFrame.
//
//--------------------------------------------------------------------------------------
int Boss01::GetCurrentShootMode()
{
	switch (m_phaseIndex)
	{
	case 0:
		if (m_elapsedFrame < 120)
			return 1;
		if ((m_elapsedFrame > 180 && m_elapsedFrame < 300)
			|| (m_elapsedFrame > 540  && m_elapsedFrame < 660))
			return 2;
		if (m_elapsedFrame > 360 && m_elapsedFrame < 480)
			return 3;
		return 0;
		break;
	case 1:
		return 0;
		break;
	case 2:
		return 0;
		break;
	case 3:
		return 0;
		break;
	default:
		return 0;
	}
}