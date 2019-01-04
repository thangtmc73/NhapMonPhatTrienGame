#include "DynamicObject.h"
#include "GSystem.h"
#include "InfoManager.h"
#include "RObjectManager.h"
#include "Utils.h"
#include "Resources.h"

CDynamicObject::CDynamicObject() : RBaseObject()
{
	_collidingWithAnyGround = false;
	_boundingBox.vy = 0;
	_dead = false;
	_numberShot = 0;
}

CDynamicObject::~CDynamicObject() {}

void CDynamicObject::setState(int a_state) {}

void CDynamicObject::draw()
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

void CDynamicObject::update(int a_deltaTime)
{
	_listColliding.clear();
	this->runAnimation(a_deltaTime);
	RObjectManager::GetInstance()->collidingWith(this, a_deltaTime);
	_boundingBox.position.x += _boundingBox.vx * a_deltaTime;
	_boundingBox.position.y += _boundingBox.vy * a_deltaTime;
	_boundingBox.vy -= Resources::getInstance()->getFloatConstWithName("gravity") * a_deltaTime;
}

void CDynamicObject::AfterCollidingWithStair(bool a_leftDirectionStair)
{
}

void CDynamicObject::SetBrickNearestStair(GRect a_rect)
{
}

void CDynamicObject::SetLeftDirection(bool a_left)
{
	_leftDirection = a_left;
}

void CDynamicObject::SetTwoBricksFromStair(RBaseObject *a_ground)
{
}

void CDynamicObject::setVxWithLeftDirection(float vx_right)
{
	if (_leftDirection) {
		_boundingBox.vx = -vx_right;
	}
	else {
		_boundingBox.vx = vx_right;
	}
}

bool CDynamicObject::isLeftDirection()
{
	return _leftDirection;
}

int CDynamicObject::getTimeBetweenTwoShot()
{
	return _timeBetweenTwoShot;
}

void CDynamicObject::updateTimeToShot(int a_deltaTime)
{
	_timeLastShot += a_deltaTime;
	if (_timeLastShot > _timeBetweenTwoShot) {
		_timeLastShot = 0;
	}
}

bool CDynamicObject::isTimeToShot()
{
	return _timeLastShot == 0;
}

bool CDynamicObject::IsDead()
{
	return _dead;
}