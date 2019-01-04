#ifndef __BAT_H__
#define __BAT_H__

#include "Enemy.h"

class CBat : public CEnemy
{
public:
	CBat(float, float, int);
	virtual void afterCollisionWithWeapon(RObject *collided, CollisionInfo info);
	virtual void update(int a_deltaTime);

	~CBat();
private:
	int _time;
	GPoint2D _startPoint;
};
#endif // !__BAT_H__