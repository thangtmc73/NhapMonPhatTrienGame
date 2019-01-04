#ifndef __SPEAR_KNIGHT_H__
#define __SPEAR_KNIGHT_H__

#include "Enemy.h"

class CSpearKnight : public CEnemy
{
public:
	CSpearKnight(float, float, int);
	virtual void afterCollisionWithWeapon(RBaseObject *collided, CollisionInfo info);
	~CSpearKnight();
};

#endif // !__SPEAR_KNIGHT_H__