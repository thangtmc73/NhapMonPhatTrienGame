#include "Brick.h"
#include "Resources.h"

CBrick::CBrick(float a_x, float a_y, int a_type, int a_column, int a_row)
{
	SpriteSheetInfo info;
	info.numCols = 1;
	info.numRows = 1;
	info.numFrames = 1;
	
	_boundingBox.position.x = a_x;
	_boundingBox.position.y = a_y;

	_type = (eTypeObject)a_type;

	switch ((eTypeObject)_type)
	{
	case eTypeObject::GROUND_1:
		_sprite = new RSprite(Resources::getInstance()->getTextureWithName("cbrick_1"));
		info.frameHeight = 32;
		info.frameWidth = 32;
		_sprite->setSpriteSheetInfo(info);
		break;
	case eTypeObject::GROUND_2:
		_sprite = new RSprite(Resources::getInstance()->getTextureWithName("cbrick_2"));
		info.frameHeight = 32;
		info.frameWidth = 32;
		_sprite->setSpriteSheetInfo(info);
		break;
	case eTypeObject::GROUND_3:
		_sprite = new RSprite(Resources::getInstance()->getTextureWithName("cbrick_3"));
		info.frameHeight = 16;
		info.frameWidth = 16;
		_sprite->setSpriteSheetInfo(info);
		break;
	}
	_boundingBox.width = (float) a_column * (info.frameWidth + 1);
	_boundingBox.height = (float) a_row * info.frameHeight;

	_numberOfTilesWidth = a_column;
	_numberOfTilesHeight = a_row;
	_groupType = eGroupTypeObject::GROUND;
}

GPoint2D CBrick::getTopLeftPoint()
{
	SpriteSheetInfo info = _sprite->getSpriteSheetInfo();
	GPoint2D position = _boundingBox.position;
	position.x -= info.frameWidth / 2;
	position.y += info.frameHeight / 2;
	return position;
}

void CBrick::draw()
{
	float x = _boundingBox.position.x;
	SpriteSheetInfo info = _sprite->getSpriteSheetInfo();
	int y;

	for (int i = 0; i < _numberOfTilesWidth; i++)
	{
		y = _boundingBox.position.y;
		for (int j = 0; j < _numberOfTilesHeight; j++)
		{
			_sprite->draw(x, y);
			y += info.frameHeight;
		}
		x += info.frameWidth;
	}
}

void CBrick::drawWithCamera(GCamera *a_camera)
{
	D3DXVECTOR2 pos = a_camera->Transform(_boundingBox.position.x, _boundingBox.position.y);
	int x = _boundingBox.position.x;
	int y = _boundingBox.position.y;
	_boundingBox.position.x = pos.x;
	_boundingBox.position.y = pos.y;
	//draw();
	//if (_boundingBox.width < a_camera->GetMinSize())
	//{
		_boundingBox.position.x = pos.x;
		_boundingBox.position.y = pos.y;
		draw();
		_boundingBox.position.x = x;
		_boundingBox.position.y = y;
	//}
	/*else
	{
		int number_tiles_drawn;
		int x_camera = a_camera->viewport.x;
		int delta_x;
		int number_tiles_passed = (x_camera - _boundingBox.position.x + 16) / 32;
		if (number_tiles_passed < 0)
		{
			number_tiles_passed = 0;
			number_tiles_drawn = _numberOfTilesWidth;
			delta_x = _boundingBox.position.x - x_camera - 16;
		}
		else {
			number_tiles_drawn = a_camera->GetMinSize() / 32;
			delta_x = number_tiles_passed * 32 - a_camera->viewport.x;
		}
		if (number_tiles_drawn >= _numberOfTilesWidth - number_tiles_passed)
		{
			number_tiles_drawn = _numberOfTilesWidth - number_tiles_passed;
		}
		else
		{
			number_tiles_drawn++;
		}
		
		
		int x = delta_x - 16;
		if (x > 2 && _boundingBox.position.x == 16) {
			int a = 0;
		}
		int y = pos.y;
		for (int i = 0; i < number_tiles_drawn; i++)
		{
			y = pos.y;
			for (int j = 0; j < _numberOfTilesHeight; j++)
			{
				_sprite->draw(x, y);
				y -= 32;
			}
			x += 32;
		}
	}*/
	_boundingBox.position.x = x;
	_boundingBox.position.y = y;
}
