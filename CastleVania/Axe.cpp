#include "Axe.h"
#include "Resources.h"
#include "Utils.h"

CAxe::CAxe(float a_x, float a_y) : CDynamicObject()
{
	_boundingBox.position.x = a_x;
	_boundingBox.position.y = a_y;
	_sprite = new RSprite(Resources::getInstance()->getTextureWithName("caxe"));
	SpriteSheetInfo info;
	info.numCols = 1;
	info.numRows = 1;
	info.numFrames = 1;
	info.frameHeight = 30;
	info.frameWidth = 28;
	_sprite->setSpriteSheetInfo(info);
	_animations = new RAnimation*[1];
	_animations[0] = new RAnimation(_sprite, 0, 0, 0, 0);
	_boundingBox.height = 30;
	_boundingBox.width = 28;
}

CAxe::~CAxe()
{
}

void CAxe::afterCollisionWithWeapon(RBaseObject *collided, CollisionInfo info)
{
}
