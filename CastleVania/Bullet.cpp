#include "Bullet.h"
#include "ObjectConfig.h"

CBullet::CBullet(float a_x, float a_y, bool a_leftDirection)
{
	if (a_leftDirection)
	{
		_boundingBox.position.x = a_x - 30;
	}
	else {
		_boundingBox.position.x = a_x + 30;
	}
	_leftDirection = a_leftDirection;
	_boundingBox.position.y = a_y;
	_destroyable = false;
	_zIndex = 1;
}

void CBullet::draw()
{
	if (_leftDirection)
	{
		_sprite->draw(_boundingBox.position.x, _boundingBox.position.y);
	}
	else
	{
		_sprite->drawFlipX(_boundingBox.position.x, _boundingBox.position.y);
	}
}

bool CBullet::IsDestroyable()
{
	return _destroyable;
}
