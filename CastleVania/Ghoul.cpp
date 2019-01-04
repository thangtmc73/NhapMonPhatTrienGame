#include "Ghoul.h"
#include "InfoManager.h"
#include "ObjectManager.h"
#include "Utils.h"
#include "Log.h"
#include "Resources.h"

CGhoul::CGhoul(float a_x, float a_y, int a_leftDirection) : CEnemy(a_x, a_y, a_leftDirection)
{
	_objectName = "cghoul";
	loadResource();
	_animations = new RAnimation*[1];
	_animations[0] = new RAnimation(_sprite, 0, 1, 0, 100);
	_type = eTypeObject::EnemeyGhoul;
	_timesCollidingToDie = 1;
	_ratioBetweenStrongAndWeakWhip = 1;
	_state = 0;
	_score = 100;
}

void CGhoul::afterCollisionWithWeapon(RObject * collided, CollisionInfo info)
{
	if (_colliding == 0)
	{
		_colliding = 1;
		CInfoManager::GetInstance()->ChangeScore(_score);
		if (CInfoManager::GetInstance()->getStatusWhip() == 0)
		{
			--_timesCollidingToDie;
		}
		else
		{
			_timesCollidingToDie -= _ratioBetweenStrongAndWeakWhip;
		}
		if (_timesCollidingToDie <= 0)
		{
			_dead = true;
			_destroyed = true;
		}
	}
}

CGhoul::~CGhoul()
{
}
