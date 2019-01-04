#include "Enemy.h"
#include "InfoManager.h"
#include "RObjectManager.h"
#include "Utils.h"
#include "Panther.h"
#include "Resources.h"
#include "Log.h"

CEnemy::CEnemy(float a_x, float a_y, int a_leftDirection) : CDynamicObject()
{
	_boundingBox.position.x = a_x;
	_boundingBox.position.y = a_y;
	_colliding = 0;
	_groupType = eGroupTypeObject::ENEMY;
	if (a_leftDirection != 0) {
		_leftDirection = true;
	}
	else {
		_leftDirection = false;
	}
}

void CEnemy::draw()
{
	if (!_leftDirection)
	{
		_sprite->drawFlipX(_boundingBox.position.x, _boundingBox.position.y);
	}
	else
	{
		_sprite->draw(_boundingBox.position.x, _boundingBox.position.y);
		
	}
}

void CEnemy::afterCollisionWithWeapon(RObject *collided, CollisionInfo info)
{
}

void CEnemy::actionCollidingSimon()
{
	
}

void CEnemy::processWhenCollidingWithGround(RObject * collided, CollisionInfo info, int deltaTime)
{
	if (collided->getGroupType() == eGroupTypeObject::GROUND) {
		if (collided->isNormalGroundObject()) {
			switch (info.direction) {
			case eDirection::TOP:
				_boundingBox.position.x += info.collisionTime * deltaTime * _boundingBox.vx;
				_boundingBox.position.y += (info.collisionTime * deltaTime * _boundingBox.vy + 1);
				_boundingBox.vy = 0;
				break;
			case eDirection::LEFT:
				_boundingBox.position.x += info.collisionTime * deltaTime * _boundingBox.vx;
				_boundingBox.position.y += info.collisionTime * deltaTime * _boundingBox.vy;
				_boundingBox.vx = -_boundingBox.vx;

				_boundingBox.position.x += (1 - info.collisionTime) * deltaTime * _boundingBox.vx;
				_leftDirection = !_leftDirection;
				break;
			case eDirection::RIGHT:
				_boundingBox.position.x += info.collisionTime * deltaTime * _boundingBox.vx;
				_boundingBox.position.y += info.collisionTime * deltaTime * _boundingBox.vy;
				_boundingBox.vx = -_boundingBox.vx;
				_boundingBox.position.x += (1 - info.collisionTime) * deltaTime * _boundingBox.vx;

				_leftDirection = !_leftDirection;

				break;
			default:
				break;
			}
		}
	}
}

void CEnemy::update(int a_deltaTime)
{
	_listColliding.clear();
	_boundingBox.vy -= (Resources::getInstance()->getFloatConstWithName("gravity") * a_deltaTime);

	this->runAnimation(a_deltaTime);
	float vx = Resources::getInstance()->getFloatConstWithName("enemy-default-vx");
	setVxWithLeftDirection(vx);
	RObjectManager::GetInstance()->collidingWith(this, a_deltaTime);

	_boundingBox.position.x += _boundingBox.vx * a_deltaTime;
	_boundingBox.position.y += _boundingBox.vy * a_deltaTime;
}

CEnemy::~CEnemy()
{
}
