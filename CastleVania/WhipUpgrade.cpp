#include "WhipUpgrade.h"
#include "InfoManager.h"
#include "Utils.h"
#include "Resources.h"

CWhipUpgrade::CWhipUpgrade(float a_x, float a_y) : CDynamicObject()
{
	_boundingBox.position.x = a_x;
	_boundingBox.position.y = a_y;
	_sprite = new RSprite(Resources::getInstance()->getTextureWithName("cwhipupgrade"));
	SpriteSheetInfo info;
	info.numCols = 1;
	info.numRows = 1;
	info.numFrames = 1;
	info.frameHeight = 32;
	info.frameWidth = 32;
	_sprite->setSpriteSheetInfo(info);
	_boundingBox.width = 32;
	_boundingBox.height = 32;
	_animations = new RAnimation*[1];
	_animations[0] = new RAnimation(_sprite, 0, 0, 0, 0);
	_type = eTypeObject::Whip;
	_groupType = eGroupTypeObject::DYNAMIC_ITEM;
	_zIndex = 1;
}

void CWhipUpgrade::actionCollidingSimon()
{
	_destroyed = true;
}

CWhipUpgrade::~CWhipUpgrade()
{
}