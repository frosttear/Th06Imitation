//--------------------------------------------------------------------------------------
//File: SpellCard.h
//
//Desc: The Special Attack Mode Of Boss
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once
#include "Boss.h"
#include <string>
using namespace std;
class SpellCard
{
public:
					SpellCard(unsigned int id, string name, Boss *pBoss,unsigned int score, int countdown = 30 * 60);
					~SpellCard();
	virtual void	InitBoss(void)		= 0;
	virtual void	Update(void)		= 0;
	virtual void	Shoot(void)			= 0;
	virtual void	OnComplete(void)	= 0;
	string			GetName() const		 { return m_name;}
	unsigned int	GetID()	  const		 { return m_id;}
	void			SetDesc(string desc) { m_desc = desc;}
	void			SetBoss(Boss *pBoss) { m_pBoss = pBoss;}
	vector<MotionInfo*>& GetMotionInfos(){ return m_motionInfos;}
	int			    GetCountdown() const { return m_countdown;}
	int				GetLoopFrame() const { return m_loopFrame;}
protected:
	unsigned int		m_id;
	int					m_elapsedFrame;
	unsigned int		m_score;
	int					m_countdown;	
	int					m_loopFrame;
	string				m_name;
	string				m_desc;
	Boss *				m_pBoss;
	vector<MotionInfo*> m_motionInfos;
	bool				m_bIsPerfect;
};

class SpellCard01 : public SpellCard
{
public:
					SpellCard01(Boss *pBoss);
		void		InitBoss(void);
		void		Update(void);
		void		Shoot(void);
		void		OnComplete(void);
};

class SpellCard02 : public SpellCard
{
public:
					SpellCard02(Boss *pBoss);
		void		InitBoss(void);
		void		Update(void);
		void		Shoot(void);
		void		OnComplete(void);
};