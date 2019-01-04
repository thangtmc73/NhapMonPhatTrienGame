#include "BrickItem.h"
#include "Resources.h"

CBrickItem::CBrickItem(float a_x, float a_y) : CStaticObject()
{
	_boundingBox.position.x = a_x;
	_boundingBox.position.y = a_y;
	_sprite = new RSprite(Resources::getInstance()->getTextureWithName("cbrick_2"));
	SpriteSheetInfo info;
	info.numCols = 2;
	info.numRows = 1;
	info.numFrames = 2;
	info.frameHeight = 32;
	info.frameWidth = 32;
	_sprite->setSpriteSheetInfo(info);
	_boundingBox.height = 32;
	_boundingBox.width = 32;
	_animations = new RAnimation*[1];
	_animations[0] = new RAnimation(_sprite, 0, 0, 0, 0);
}

CBrickItem::~CBrickItem()
{
}

void CBrickItem::afterCollisionWithWeapon(RBaseObject *collided, CollisionInfo info)
{

}
