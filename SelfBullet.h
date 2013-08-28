//--------------------------------------------------------------------------------------
//File: SelfBullet.h
//
//Desc: defines the bullets belong to player
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#include "Bullet.h"

class GameObject;
//--------------------------------------------------------------------------------------
//Linear bullet, Primary Weapon Of Reimu
//--------------------------------------------------------------------------------------
class SelfBullet01 : public Bullet
{
public:

					SelfBullet01(const D3DXVECTOR2 &position, float directionX = 0, float directionY = -1);
	void			Update();
	//void			Render(ID3DXSprite* pSprite);
	bool			Collision(GameObject * pObject);
	void			OnWipped();
};
//--------------------------------------------------------------------------------------
//Track bullet, Secondary Weapon  Of Reimu
//--------------------------------------------------------------------------------------
class SelfBullet02	: public Bullet
{
public:
					SelfBullet02(const D3DXVECTOR2 &position, float directionX = -1, float directionY = -1);
	void			Update();
	//void			Render(ID3DXSprite* pSprite);
	void			OnWipped();
	bool			Collision(GameObject * pObject);
private:
	GameObject*		m_target;
};