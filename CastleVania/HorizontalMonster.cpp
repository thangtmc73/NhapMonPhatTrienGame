#include "HorizontalMonster.h"

CHorizontalMonster::CHorizontalMonster(int a_x, int a_y) : CDynamicObject()
{
	_boundingBox.position.x = a_x;
	_boundingBox.position.y = a_y;
}

void CHorizontalMonster::Draw()
{
	if (!_leftDirection)
	{
		_sprite->DrawFlipX(_boundingBox.position.x, _boundingBox.position.y);
	}
	else
	{
		_sprite->Draw(_boundingBox.position.x, _boundingBox.position.y);
		
	}
}

void CHorizontalMonster::Update(int a_deltaTime)
{
	this->RunAnimation(a_deltaTime);
	if (_boundingBox.position.x + 1 > G_ScreenWidth)
	{
		_boundingBox.position.x = G_ScreenWidth - 1;
		_leftDirection = true;
	}
	if (_boundingBox.position.x < 0)
	{
		_boundingBox.position.x = 0;
		_leftDirection = false;
	}
	if (_leftDirection)
	{
		_boundingBox.position.x -= 1;
	}
	else
	{
		_boundingBox.position.x += 1;
	}
}

CHorizontalMonster::~CHorizontalMonster()
{
}
