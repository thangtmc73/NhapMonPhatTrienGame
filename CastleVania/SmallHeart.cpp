#define _USE_MATH_DEFINES

#include "SmallHeart.h"
#include "InfoManager.h"
#include "Global.h"
#include <math.h>
#include "Utils.h"
#include "Resources.h"
#include "ObjectConfig.h"
#include "RObjectManager.h"

CSmallHeart::CSmallHeart(float a_x, float a_y) : CDynamicObject()
{
	_startPoint.x = _boundingBox.position.x = a_x;
	_startPoint.y = _boundingBox.position.y = a_y;
	_objectName = "csmallheart";
	loadResource();
	_type = eTypeObject::SmallHeart;
	_groupType = eGroupTypeObject::DYNAMIC_ITEM;
	_time = 0;
}

CSmallHeart::~CSmallHeart()
{
}
void CSmallHeart::update(int a_deltaTime)
{
	_listColliding.clear();
	this->runAnimation(a_deltaTime);
	RObjectManager::GetInstance()->collidingWith(this, a_deltaTime);
	int cycleTime = Resources::getInstance()->getIntegerConstWithName("small-heart-cycle-time");
	float distanceMove = Resources::getInstance()->getFloatConstWithName("small-heart-distance-move");

	if (_boundingBox.vy != 0) {
		_time += a_deltaTime;
		_boundingBox.position.x = _startPoint.x + distanceMove * cos((2 * M_PI / cycleTime) * _time);
	}
	_boundingBox.position.x += _boundingBox.vx * a_deltaTime;
	_boundingBox.position.y += _boundingBox.vy * a_deltaTime;
	_boundingBox.vy -= Resources::getInstance()->getFloatConstWithName("gravity") * a_deltaTime;
}

void CSmallHeart::actionCollidingSimon()
{
	CInfoManager::GetInstance()->ChangeNumberOfHearts(Resources::getInstance()->getIntegerConstWithName("small-heart-number-hearts-increase"));
	_destroyed = true;
}