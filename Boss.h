//--------------------------------------------------------------------------------------
//File: Boss.h
//
//Desc: describes special enemy:boss ,which has several phases
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once
#include "Enemy.h"

#include <vector>
using namespace std;
//Boss state decide how to update the boss 
enum BOSS_STATE {BOSS_STATE_INIT, BOSS_STATE_NORMAL, BOSS_STATE_DIE};
//Boss action state decide how to render the boss
enum BOSSACTION_STATE { BOSSACTION_SPELLSHOOT, BOSSACTION_MOVERIGHT, BOSSACTION_MOVELEFT, BOSSACTION_NORMAL};


class SpellCard;

//BossPhase 
struct BossPhase
{
	BossPhase(int minHp, int maxHp, SpellCard *pSpellCard = NULL, int countdown = 0, int loopFrame = 0);
	~BossPhase();
	int						minHp;
	int						maxHp;
	int						countdown;
	int						loopFrame;
	SpellCard*				pSpellCard;
	vector<MotionInfo *>	motionInfos;
};

class Boss : public Enemy
{
public:
									Boss(void);
									Boss(unsigned int id, string name);
	virtual							~Boss(void);
	void							Set(unsigned int hp, D3DXVECTOR2 position);
	virtual void					Shoot(void)		= 0;
	virtual void					Update(void);
	//InitState:moves boss to the init position,while keep the boss invincible. 
	virtual void					InitStateUpdate(void)	= 0;
	virtual void					NormalStateUpdate(void);
	virtual void					DieStateUpdate(void)	= 0;
	virtual void					OnDying(void);
	virtual void					OnChangePhase(void);
	virtual void					OnWipped(void)	= 0;
	virtual void					Render(ID3DXSprite *pSprite)	= 0;
	void							RenderHpbar(void);
	virtual void					OnHit(GameObject *pObject);
	void							ChangeActionState(BOSSACTION_STATE actionState);
	virtual	void					SetBossSprite(BOSSACTION_STATE actionState) = 0;
	virtual int						GetCurrentShootMode(void) = 0;

protected:
	unsigned int					m_id;
	BOSS_STATE						m_state;
	BOSSACTION_STATE				m_actionState;
	unsigned int					m_maxHp;
	vector<BossPhase*>				m_phases;
	unsigned int					m_phaseIndex;
	int								m_countdown;
	int								m_shootMode;
	int								m_loopCount;		//record motion loop times during one phase
	int								m_remainHpNum;
	LPDIRECT3DTEXTURE9				m_normalBackground;
	LPDIRECT3DTEXTURE9				m_spellBackground;
};

class Boss01	: public Boss
{
public:
							Boss01(void);
	void					Shoot(void);
	void					InitStateUpdate(void);
	void					NormalStateUpdate(void);
	void					DieStateUpdate(void);
	void					Render(ID3DXSprite * pSprite);
	void					OnWipped(void);
	void					OnDying(void);
	void					SetBossSprite(BOSSACTION_STATE actionState);
	int						GetCurrentShootMode(void);
};