#include "Ground.h"

CGround::CGround(float a_x, float a_y, int a_type, int a_width)
{
	/*_boundingBox.position.x = a_x;
	_boundingBox.position.y = a_y;

	
	switch (a_type)
	{
	case 0:
		SPRITE = new GTexture("ground_1.png", 1, 1, 1);
		SPRITE->FrameWidth = 32;
		SPRITE->FrameHeight = 32;
		break;
	case 1:
		break;
	case 3:
		break;
	}
	_boundingBox.width = a_width;
	_boundingBox.height = SPRITE->FrameHeight;

	_numberOfTiles = a_width / SPRITE->FrameWidth + 1;
	_groupType = eGroupTypeObject::GROUND;*/
}

void CGround::draw()
{
	/*int x = _boundingBox.position.x;
	for (int i = 0; i < _numberOfTiles; i++)
	{
		_sprite->draw(x, _boundingBox.position.y);
		x += SPRITE->FrameWidth;
	}*/
}

void CGround::drawWithCamera(int a_x, int a_y, GCamera *a_camera, int a_swidth)
{
	//int x, y;

	//int delta_x, delta_y;
	//int numberOfTiles;
	//
	//int sx = a_camera->viewport.x;
	//int sy = a_camera->viewport.y;

	//delta_x = sx % SPRITE->FrameWidth;
	//delta_y = sy % SPRITE->FrameHeight;
	////_numberOfTiles = (int)(a_swidth / SPRITE->FrameWidth) + 1;

	//a_x -= delta_x;
	//a_y -= delta_y;

	//x = a_x;
	//y = a_y;
	//D3DXVECTOR2 pos = a_camera->Transform(x, y);
	//for (int i = 0; i < _numberOfTiles; i++)
	//{
	//	_sprite->draw(pos.x, pos.y);
	//	pos.x += SPRITE->FrameWidth;
	//}
}
