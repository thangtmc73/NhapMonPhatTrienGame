#ifndef __GHOST_H__
#define __GHOST_H__

#include "Enemy.h"

class CGhost : public CEnemy
{
public:
	CGhost(float, float, int);
	virtual void afterCollisionWithWeapon(RBaseObject *collided, CollisionInfo info);
	~CGhost();
};
#endif // !__GHOST_H__