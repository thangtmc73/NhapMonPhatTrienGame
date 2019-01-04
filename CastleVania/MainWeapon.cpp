#include "MainWeapon.h"

CMainWeapon::CMainWeapon(float a_x, float a_y, bool a_leftDirection)
{
	_boundingBox.position.x = a_x;
	_boundingBox.position.y = a_y;
	_leftDirection = a_leftDirection;
	_groupType = eGroupTypeObject::WEAPON_MAIN;
}

void CMainWeapon::afterCollision(RBaseObject * collided, CollisionInfo info, int deltaTime)
{

}

void CMainWeapon::update(int a_deltaTime)
{
	_boundingBox.position.x += _boundingBox.vx * a_deltaTime;
	_boundingBox.position.y += _boundingBox.vy * a_deltaTime;
}

void CMainWeapon::draw()
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
