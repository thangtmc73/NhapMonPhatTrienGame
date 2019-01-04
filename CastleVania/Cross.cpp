#include "Cross.h"
#include "RObjectManager.h"

CCross::CCross(float a_x, float a_y) : CDynamicObject()
{
	_objectName = "ccross";
	_boundingBox.position.x = a_x;
	_boundingBox.position.y = a_y;
	loadResource();
	_animations = new RAnimation*[1];
	_animations[0] = new RAnimation(_sprite, 0, 0, 0, 100);
}

CCross::~CCross()
{
}

void CCross::afterCollision(RBaseObject * collided, CollisionInfo info, int a_deltaTime)
{
	processWhenCollidingWithGround(collided, info, a_deltaTime);
	switch (collided->getType())
	{
	case eTypeObject::Simon:
		RObjectManager::GetInstance()->killAllEnemy();
		_destroyed = true;
		break;
	}
}
