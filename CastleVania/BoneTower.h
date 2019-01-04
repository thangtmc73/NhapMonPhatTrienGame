#ifndef __BONE_TOWER_H__
#define __BONE_TOWER_H__

#include "Enemy.h"

class CBoneTower : public CEnemy
{
public:
	CBoneTower(int, int, int);
	virtual void AfterCollisionWithSimon(CObjectManager *a_objectManager);
	virtual void AfterCollisionWithWeapon(CObjectManager *a_objectManager);
	~CBoneTower();
};
#endif // !__BONE_TOWER_H__