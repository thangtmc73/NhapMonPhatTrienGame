#ifndef __PANTHER_H__
#define __PANTHER_H__

#include "Enemy.h"

class CPanther : public CEnemy
{
public:
	CPanther(float, float, int);
	void setState(int);
	void update(int a_deltatime);
	void afterCollisionWithWeapon();
	virtual void processWhenCollidingWithGround(RObject * collided, CollisionInfo info, int deltaTime);

	~CPanther();
private:
	void updateStateAfterCollidingGround();

	bool groundCollidedFlag;
	void ChangeDirection();
	bool isInAttackingSimonRange();
	void UpdateVx();
};

#endif // !__PANTHER_H__
