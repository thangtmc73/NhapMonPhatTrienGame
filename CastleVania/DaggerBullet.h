#ifndef __DAGGER_BULLET_H__
#define __DAGGER_BULLET_H__

#include "Bullet.h"

class CDaggerBullet : public CBullet
{
public:
	CDaggerBullet(float, float, bool a_leftDirection = true);
	virtual void update(int a_deltaTime);
	virtual void afterCollision(RBaseObject *collided, CollisionInfo info, int deltaTime);

	void draw();
private:
};

#endif // !__DAGGER_BULLET_H__ 