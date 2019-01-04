#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "DynamicObject.h"

class CEnemy : public CDynamicObject
{
public:
	CEnemy(float a_x, float a_y, int a_leftDirection = true);
	void draw();
	virtual void update(int a_deltaTime);
	virtual void afterCollisionWithWeapon(RObject *collided, CollisionInfo info);
	virtual void actionCollidingSimon();
	virtual void processWhenCollidingWithGround(RObject * collided, CollisionInfo info, int deltaTime);

	~CEnemy();
protected:
	float _timesCollidingToDie;
	float _ratioBetweenStrongAndWeakWhip;
	int _colliding;
	int _score;
	int _damagedValue;
};
#endif // !__ENEMY_H__