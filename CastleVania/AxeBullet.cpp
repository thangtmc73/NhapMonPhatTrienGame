#include "AxeBullet.h"
#include "ObjectConfig.h"
#include "Resources.h"

CAxeBullet::CAxeBullet(float a_x, float a_y, bool a_leftDirection) : CBullet(a_x, a_y, a_leftDirection)
{
	_objectName = "caxebullet";
	loadResource();
	_leftDirection = a_leftDirection;
	float vx = Resources::getInstance()->getFloatConstWithName("axe-vx");
	float vy = Resources::getInstance()->getFloatConstWithName("axe-vy");

	if (!_leftDirection)
	{
		_boundingBox.vx = vx;
	}
	else
	{
		_boundingBox.vx = -vx;
	}
	_animations = new RAnimation*[1];
	_animations[0] = new RAnimation(_sprite, 0, 3, 9, 100);
	_state = 0;
	_boundingBox.vy = vy;
}

void CAxeBullet::update(int a_deltaTime)
{
	_listColliding.clear();
	this->runAnimation(a_deltaTime);
	_boundingBox.position.x += _boundingBox.vx * a_deltaTime;
	_boundingBox.position.y += _boundingBox.vy * a_deltaTime;
	_boundingBox.vy -= Resources::getInstance()->getFloatConstWithName("gravity") * a_deltaTime;
}

void CAxeBullet::draw()
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