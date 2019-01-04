#define _USE_MATH_DEFINES

#include "Bat.h"
#include "InfoManager.h"
#include "Resources.h"

CBat::CBat(float a_x, float a_y, int a_leftDirection ) : CEnemy(a_x, a_y, a_leftDirection)
{
	_objectName = "cbat";
	loadResource();
	_leftDirection = false;
	_animations = new RAnimation*[2];
	_animations[0] = new RAnimation(_sprite, 0, 0, 0, 100);
	_animations[1] = new RAnimation(_sprite, 1, 3, 1, 50);
	_startPoint.x = a_x;
	_startPoint.y = a_y;
	_state = 1;
	_boundingBox.vx = Resources::getInstance()->getFloatConstWithName("red-bat-vx");
	_boundingBox.vy = 0;
	_timesCollidingToDie = 1;
	_ratioBetweenStrongAndWeakWhip = 1;
}

void CBat::afterCollisionWithWeapon(RObject *collided, CollisionInfo info)
{
	CInfoManager::GetInstance()->ChangeScore(3000);
}

void CBat::update(int a_deltaTime)
{
	_listColliding.clear();
	this->runAnimation(a_deltaTime);
	int cycleTime = Resources::getInstance()->getIntegerConstWithName("red-bat-cycle-time");
	float distanceMove = Resources::getInstance()->getFloatConstWithName("red-bat-distance-move");
	_time += a_deltaTime;
	_boundingBox.position.y = _startPoint.y + distanceMove * cos((2 * M_PI / cycleTime) * _time);
	//RObjectManager::GetInstance()->collidingWith(this, a_deltaTime);

	_boundingBox.position.x += _boundingBox.vx * a_deltaTime;
	_boundingBox.position.y += _boundingBox.vy * a_deltaTime;
}

CBat::~CBat()
{
}