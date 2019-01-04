#include "BigCandle.h"
#include "WhipUpgrade.h"
#include "Dagger.h"
#include "Utils.h"
#include "Resources.h"
#include "RObjectManager.h"

CBigCandle::CBigCandle(int a_type, float a_x, float a_y) : CStaticObject()
{
	_boundingBox.position.x = a_x;
	_boundingBox.position.y = a_y;
	_sprite = new RSprite(Resources::getInstance()->getTextureWithName("cbigcandle"));
	SpriteSheetInfo info;
	info.numCols = 2;
	info.numRows = 1;
	info.numFrames = 2;
	info.frameHeight = 64;
	info.frameWidth = 32;
	_sprite->setSpriteSheetInfo(info);
	_boundingBox.height = 64;
	_boundingBox.width = 32;
	_animations = new RAnimation*[1];
	_animations[0] = new RAnimation(_sprite, 0, 1, 0, 100);
	_type = (eTypeObject)a_type;
	_groupType = eGroupTypeObject::STATIC_ITEM;
	//GetFromFile("state1map1GO.txt", _objectArray, _objectArrayWidth, _objectArrayHeight);
}

CBigCandle::~CBigCandle()
{
}

void CBigCandle::afterCollisionWithWeapon(RObject *collided, CollisionInfo info)
{
	//_drawable = false;
	switch (_type)
	{
	case eTypeObject::BigCandleWithLargeHeart:
		RObjectManager::GetInstance()->addObject(_index + 1000, new CLargeHeart(_boundingBox.position.x, _boundingBox.position.y));
		break;
	case eTypeObject::BigCandleWithUpgradeWhip:
		RObjectManager::GetInstance()->addObject(_index + 1000, new CWhipUpgrade(_boundingBox.position.x, _boundingBox.position.y));
		break;
	case eTypeObject::BigCandleWithDagger:
		RObjectManager::GetInstance()->addObject(_index + 1000, new CDagger(_boundingBox.position.x, _boundingBox.position.y));
		break;
	}
	_destroyed = true;
}
