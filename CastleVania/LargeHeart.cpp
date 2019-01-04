#include "LargeHeart.h"
#include "Global.h"
#include "InfoManager.h"
#include "Utils.h"
#include "Resources.h"

CLargeHeart::CLargeHeart(float a_x, float a_y) : CDynamicObject()
{
	_boundingBox.position.x = a_x;
	_boundingBox.position.y = a_y;
	_objectName = "clargeheart";
	loadResource();
	_animations = new RAnimation*[1];
	_animations[0] = new RAnimation(_sprite, 0, 0, 0, 0);
	_type = eTypeObject::LargeHeart;
	_groupType = eGroupTypeObject::DYNAMIC_ITEM;
	_zIndex = 1;
}

CLargeHeart::~CLargeHeart()
{
}

void CLargeHeart::actionCollidingSimon()
{
	CInfoManager::GetInstance()->ChangeNumberOfHearts(Resources::getInstance()->getIntegerConstWithName("large-heart-number-hearts-increase"));
	_destroyed = true;
}
