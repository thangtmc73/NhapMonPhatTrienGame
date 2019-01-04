#include "RTiledBG.h"
#include "Global.h"
#include <d3d9.h>
#include "Resources.h"

RTiledBG::RTiledBG()
{
}

RTiledBG::RTiledBG(int x, int y, std::string nameTexture, SpriteSheetInfo info, int a_index, int a_zIndex)
{
	_boundingBox.position.x = x;
	_boundingBox.position.y = y;
	_boundingBox.height = 32;
	_boundingBox.width = 32;
	_boundingBox.vx = 0;
	_boundingBox.vy = 0;
	_sprite = new RSprite(Resources::getInstance()->getTextureWithName(nameTexture));
	_sprite->SelectIndex(a_index);
	_sprite->setSpriteSheetInfo(info);
	_zIndex = a_zIndex;
	_groupType = eGroupTypeObject::BACKGROUND;
}

void RTiledBG::draw()
{
	_sprite->draw(_boundingBox.position.x, _boundingBox.position.y);
}

RTiledBG::~RTiledBG()
{
}

