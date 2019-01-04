#include "Stair.h"
#include "ObjectConfig.h"
#include "Utils.h"
#include "Resources.h"

CStair::CStair(float a_x, float a_y, int a_type, int a_left, int a_numberStep)
{
	_startDraw.x = a_x;
	_startDraw.y = a_y;
	SpriteSheetInfo infoTopBrick;
	infoTopBrick.numCols = 1;
	infoTopBrick.numRows = 1;
	infoTopBrick.numFrames = 1;
	infoTopBrick.frameHeight = 32;
	infoTopBrick.frameWidth = 32;
	_boundingBox.position.x = a_x;
	_boundingBox.position.y = a_y;
	
	_leftDirection = a_left;
	_type = (eTypeObject)a_type;
	_numberOfBricks = a_numberStep;

	switch (a_type)
	{
	case eTypeObject::STAIR_1:
		_topBrick = new RSprite(Resources::getInstance()->getTextureWithName("cstair_1"));
		_topBrick->setSpriteSheetInfo(infoTopBrick);
		_sprite = new RSprite(Resources::getInstance()->getTextureWithName("cstair_1"));
		_sprite->setSpriteSheetInfo(infoTopBrick);
		break;
	case eTypeObject::STAIR_2:
		_topBrick = new RSprite(Resources::getInstance()->getTextureWithName("cstair_2"));
		_topBrick->setSpriteSheetInfo(infoTopBrick);
		_sprite = new RSprite(Resources::getInstance()->getTextureWithName("cstair_1"));
		_sprite->setSpriteSheetInfo(infoTopBrick);
		break;
	}
	_boundingBox.width = (a_numberStep + 1) * infoTopBrick.frameWidth;
	_boundingBox.height = (a_numberStep + 1) * infoTopBrick.frameHeight;
	if (isLeftDirection())
	{
		_boundingBox.position.x = a_x + 32 - _boundingBox.width / 2;
	}
	else
	{
		_boundingBox.position.x = a_x - 16 + _boundingBox.width / 2;
	}
	_boundingBox.position.y = a_y - 16 + _boundingBox.height / 2;
	_firstBrick.position.y = a_y;
	_firstBrick.width = 32;
	_firstBrick.height = 32;

	_secondBrick.position.y = a_y + (a_numberStep) * 32;
	if (isLeftDirection())
	{
		_firstBrick.position.x = a_x;
		_secondBrick.position.x = a_x - (a_numberStep * 32);
	}
	else
	{
		_firstBrick.position.x = a_x;
		_secondBrick.position.x = a_x + (a_numberStep * 32);
	}
	_secondBrick.width = 32;
	_secondBrick.height = 32;
	_groupType = eGroupTypeObject::GROUND;
}

void CStair::draw()
{
	int x = _startDraw.x;
	int y = _startDraw.y;


	for (int i = 0; i < _numberOfBricks; i++)
	{
		if (_leftDirection == 0)
		{
			if (i != _numberOfBricks - 1)
			{
				_sprite->draw(x, y);
			}
			else
			{
				_topBrick->draw(x, y);
			}
			x += 32;
		}
		else
		{
			if (i != _numberOfBricks - 1)
			{
				_sprite->drawFlipX(x, y);
			}
			else
			{
				_topBrick->drawFlipX(x, y);
			}
			x -= 32;
		}
		y -= 32;
	}
	//_brick->draw(_firstBrick.position.x, _firstBrick.position.y);
	//_brick->draw(_secondBrick.position.x, _secondBrick.position.y);
}

void CStair::drawWithCamera(GCamera *a_camera)
{
	if (a_camera == NULL)
	{
		return;
	}

	int x = _startDraw.x;
	int y = _startDraw.y;
	D3DXVECTOR2 pos = a_camera->Transform(_startDraw.x, _startDraw.y);
	_startDraw.x = pos.x;
	_startDraw.y = pos.y;
	draw();
	_startDraw.x = x;
	_startDraw.y = y;
}

void CStair::GetRectNearestBetweenSimonAndStair(CDynamicObject *a_simon)
{
	GRect box = a_simon->getBoundingBox();
	box.position = a_simon->getTopLeftPoint();
	if (IsAABBCheck(box, _firstBrick))
	{
		a_simon->SetBrickNearestStair(_firstBrick);
		return;
	}
	if (IsAABBCheck(box, _secondBrick))
	{
		a_simon->SetBrickNearestStair(_secondBrick);
		return;
	}
	a_simon->SetBrickNearestStair(GRect(0, 0, -1, -1, 0, 0));
}

void CStair::actionCollidingSimon()
{
	//CSimon * simon = (CSimon*)collided;
	//simon->AfterCollidingWithStair(_leftDirection);
	//simon->SetTwoBricksFromStair(this);
}

GRect CStair::GetFirstBrick()
{
	return _firstBrick;
}

GRect CStair::GetSecondBrick()
{
	return _secondBrick;
}

bool CStair::isLeftDirection()
{
	if (_leftDirection == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
	return _leftDirection;
}
