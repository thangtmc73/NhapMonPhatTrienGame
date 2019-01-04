#ifndef __MEDUSA_HEAD_H__
#define __MEDUSA_HEAD_H__

#include "Enemy.h"

class CMedusaHead : public CEnemy
{
public:
	CMedusaHead(int, int, int);
	void AfterCollision(RBaseObject *collided, CollisionInfo info);
	void AfterCollisionWithWeapon();
	void update(int a_deltaTime);
	~CMedusaHead();
private:
	int _startY;
};
#endif // !__MEDUSA_HEAD_H__