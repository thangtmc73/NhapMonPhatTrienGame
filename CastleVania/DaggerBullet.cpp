#include "DaggerBullet.h"
#include "ObjectConfig.h"
#include "Resources.h"

CDaggerBullet::CDaggerBullet(float a_x, float a_y, bool a_leftDirection) : CBullet(a_x, a_y, a_leftDirection)
{
	_objectName = "cdaggerbullet";
	loadResource();
	_leftDirection = a_leftDirection;
	if (!_leftDirection)
	{
		_boundingBox.vx = Resources::getInstance()->getFloatConstWithName("dagger-vx");
	}
	else
	{
		_boundingBox.vx = -Resources::getInstance()->getFloatConstWithName("dagger-vx");
	}
	_groupType = eGroupTypeObject::WEAPON_MAIN;
	_type = eTypeObject::WeaponDagger;
	_boundingBox.vy = 0;
}

void CDaggerBullet::update(int a_deltaTime)
{
	_boundingBox.position.x += _boundingBox.vx * a_deltaTime;
	_boundingBox.position.y += _boundingBox.vy * a_deltaTime;
}

void CDaggerBullet::afterCollision(RBaseObject * collided, CollisionInfo info, int deltaTime)
{
	if (collided->getType() != eTypeObject::Simon) {
		_destroyed = true;

	}
}

void CDaggerBullet::draw()
{
	if (_leftDirection)
	{
		_sprite->draw(_boundingBox.position.x, _boundingBox.position.y);
	}
	else
	{
		_sprite->drawFlipX(_boundingBox.position.x, _boundingBox.position.y);
	}
}