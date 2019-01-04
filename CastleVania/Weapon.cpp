#include "Weapon.h"
#include "InfoManager.h"
#include "RObjectManager.h"
#include "Resources.h"

CWeapon::CWeapon()
{
}

CWeapon::CWeapon(float a_x, float a_y) : RBaseObject()
{
	_boundingBox.position.x = a_x;
	_boundingBox.position.y = a_y;
}

void CWeapon::draw()
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

void CWeapon::SetLeft(bool a_left)
{
	_leftDirection = a_left;
}

void CWeapon::update(int a_deltaTime)
{
	_listColliding.clear();
	this->runAnimation(a_deltaTime);
	_boundingBox.vy -= Resources::getInstance()->getFloatConstWithName("gravity") * a_deltaTime;
	_boundingBox.position.x += _boundingBox.vx * a_deltaTime;
	_boundingBox.position.y += _boundingBox.vy * a_deltaTime;
	//_collidingWithAnyGround = false;
}

CWeapon::~CWeapon
()
{
}
