//--------------------------------------------------------------------------------------
//File: Item.h
//
//Desc: Item includes power, point, life,bomb etc.Define a factory class to create item.
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once
#include "GameObject.h"
//#define ITEM_TYPE_POWER		0x01
//#define ITEM_TYPE_BIGPOWER	0x02
//#define	ITEM_TYPE_FULLPOWER 0x03
//#define ITEM_TYPE_LIFE		0x04
//#define ITEM_TYPE_STAR		0x05
//#define	ITEM_TYPE_BOMB		0x06
//#define	ITEM_TYPE_POINT		0x07
enum	ITEM_TYPE	{ITEM_TYPE_POWER, ITEM_TYPE_BIGPOWER, ITEM_TYPE_FULLPOWER, ITEM_TYPE_LIFE, ITEM_TYPE_STAR, ITEM_TYPE_BOMB, ITEM_TYPE_POINT};

#define ITEM_MAX_SCORE		10000

class Item : public GameObject
{
public:
	ITEM_TYPE		GetItemType(void) const	{return m_type;}
	int				GetPower(void)	const	{return m_power;}
	int				GetScore(void)	const	{return m_score;}
	int				GetBomb(void)	const	{return m_bomb; }
	int				GetLife(void)	const	{return m_life; }
//	void			SetTarget(GameObject * target) { m_pTarget = target;}
	void			Render(ID3DXSprite * pSprite);
	void			Update(void);
	void			OnWipped(void);

	friend class	ItemFactory;
private:
					Item(const D3DXVECTOR2 &position);
	int				m_score;
	int				m_power;
	int				m_bomb;
	int				m_life;
	ITEM_TYPE		m_type;
	//GameObject*		m_pTarget;
};
//--------------------------------------------------------------------------------------
//Factory class.Encapsulate Item creation.
//--------------------------------------------------------------------------------------
class ItemFactory
{
public:
	static Item&	GetItem(ITEM_TYPE  type, const D3DXVECTOR2 &position);
private:
	static void		SetDefaultMotionInfos(Item *pItem);
};