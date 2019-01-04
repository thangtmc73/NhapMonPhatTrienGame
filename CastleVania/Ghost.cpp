#include "Ghost.h"
#include "InfoManager.h"
#include "Resources.h"

CGhost::CGhost(float a_x, float a_y, int a_leftDirection) : CEnemy(a_x, a_y, a_leftDirection)
{
	_objectName = "cghost";
	loadResource();
	_leftDirection = false;
	_animations = new RAnimation*[1];
	_animations[0] = new RAnimation(_sprite, 0, 1, 0, 100);
	_timesCollidingToDie = 3;
	_ratioBetweenStrongAndWeakWhip = 1.5;
}

void CGhost::afterCollisionWithWeapon(RBaseObject *collided, CollisionInfo info)
{
	CInfoManager::GetInstance()->ChangeScore(300);
}

CGhost::~CGhost()
{
}
