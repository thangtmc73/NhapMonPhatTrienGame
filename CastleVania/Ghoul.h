#ifndef __GHOUL_H__
#define __GHOUL_H__

#include "Enemy.h"

class CGhoul : public CEnemy
{
public:
	CGhoul(float, float, int);
	virtual void afterCollisionWithWeapon(RObject * collided, CollisionInfo info);
	~CGhoul();
};
#endif // !__GHOUL_H__