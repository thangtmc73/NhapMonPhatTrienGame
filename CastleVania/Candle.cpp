#include "Candle.h"

CCandle::CCandle(int a_x, int a_y) : CStaticObject()
{
	_boundingBox.position.x = a_x;
	_boundingBox.position.y = a_y;
	SPRITE = new GTexture("candle.png", 2, 1, 2);
	_boundingBox.height = SPRITE->FrameHeight = 64;
	_boundingBox.height = SPRITE->FrameWidth = 32;
	_sprite->_start = 0;
	_sprite->_end = 1;
	_sprite->_index = 0;
	_sprite->_timeAni = 100;
	//GetFromFile("state1map1GO.txt", _objectArray, _objectArrayWidth, _objectArrayHeight);
}

CCandle::~CCandle()
{
}
