#include "LittleCandle.h"
#include "RObjectManager.h"
#include "LargeHeart.h"
#include "SmallHeart.h"
#include "WhiteMoneyBag.h"
#include "PurpleMoneyBag.h"
#include "Axe.h"
#include "Cross.h"
#include "Utils.h"
#include "Resources.h"

CLittleCandle::CLittleCandle(int a_type, float a_x, float a_y) : CStaticObject()
{
	_boundingBox.position.x = a_x;
	_boundingBox.position.y = a_y;
	_objectName = "clittlecandle";
	loadResource();
	_animations = new RAnimation*[1];
	_animations[0] = new RAnimation(_sprite, 0, 1, 0, 100);
	_type = (eTypeObject)a_type;
	_groupType = eGroupTypeObject::STATIC_ITEM;
}

CLittleCandle::~CLittleCandle()
{
}

void CLittleCandle::afterCollisionWithWeapon(RObject *collided, CollisionInfo info)
{
	//_drawable = false;

	switch (_type)
	{
	case eTypeObject::LittleCandleWithLargeHeart:
		RObjectManager::GetInstance()->addObject(_index + 10000, new CLargeHeart(_boundingBox.position.x, _boundingBox.position.y + 20));
		break;
	case eTypeObject::LittleCandleStopWatch:
	case eTypeObject::LittleCandleWithAxe:
		RObjectManager::GetInstance()->addObject(_index + 10000, new CAxe(_boundingBox.position.x, _boundingBox.position.y));
		break;
	case eTypeObject::LittleCandleWithGoldPotion:
	case eTypeObject::LittleCandleWithHolyCross:
		RObjectManager::GetInstance()->addObject(_index + 10000, new CCross(_boundingBox.position.x, _boundingBox.position.y));
		break;
	case eTypeObject::LittleCandleWithHolyWater:
	case eTypeObject::LittleCandleWithPurpleMoneyBag:
		RObjectManager::GetInstance()->addObject(_index + 10000, new CPurpleMoneyBag(_boundingBox.position.x, _boundingBox.position.y));
		break;
	case eTypeObject::LittleCandleWithSmallHeart:

		RObjectManager::GetInstance()->addObject(_index + 10000, new CSmallHeart(_boundingBox.position.x, _boundingBox.position.y));
		break;
	case eTypeObject::LittleCandleWithWhiteMoneyBag:
		RObjectManager::GetInstance()->addObject(_index + 10000, new CWhiteMoneyBag(_boundingBox.position.x, _boundingBox.position.y));
		break;
	}
	_destroyed = true;
}