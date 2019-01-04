#ifndef __PHANTOM_BAT_H__
#define __PHANTOM_BAT_H__

#include "Enemy.h"

class CPhantomBat : public CEnemy
{
public:
	CPhantomBat(int, int);
	virtual void AfterCollisionWithSimon();
	virtual void AfterCollisionWithWeapon();
	~CPhantomBat();
};
#endif // !__PHANTOM_BAT_H__