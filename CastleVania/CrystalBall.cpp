#include "CrystalBall.h"
#include "Resources.h"

CCrystalBall::CCrystalBall(float a_x, float a_y) : CDynamicObject()
{
	_boundingBox.position.x = a_x;
	_boundingBox.position.y = a_y;
	_sprite = new RSprite(Resources::getInstance()->getTextureWithName("ccrystalball"));
	SpriteSheetInfo info;
	info.numCols = 2;
	info.numRows = 1;
	info.numFrames = 2;
	info.frameHeight = 32;
	info.frameWidth = 28;
	_sprite->setSpriteSheetInfo(info);
	_boundingBox.height = 32;
	_boundingBox.width = 28;
	_animations = new RAnimation*[1];
	_animations[0] = new RAnimation(_sprite, 0, 1, 0, 100);
}

CCrystalBall::~CCrystalBall()
{
}
