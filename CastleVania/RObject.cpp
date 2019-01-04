#include "RObject.h"
#include "GCamera.h"
#include "Global.h"
#include "Utils.h"
#include "Resources.h"
#include "RSprite.h"

RObject::RObject()
{
	_boundingBox.position.x = _boundingBox.position.y = 0;
	_sprite = NULL;
	_groupType = eGroupTypeObject::DEFAULT;
	_type = eTypeObject::Default;
}

RObject::~RObject()
{
	//delete SPRITE;
	if (_sprite != NULL)
	{
		delete _sprite;
	}
}

void RObject::CollideWith(RObject * a_collided)
{
}

bool RObject::isLeftDirection()
{
	return false;
}

void RObject::draw()
{
	_sprite->draw(_boundingBox.position.x, _boundingBox.position.y);
}

void RObject::drawWithCamera(GCamera *a_camera)
{
	if (a_camera == NULL)
	{
		return;
	}

	int x = _boundingBox.position.x;
	int y = _boundingBox.position.y;
	D3DXVECTOR2 pos = a_camera->Transform(_boundingBox.position.x, _boundingBox.position.y);
	_boundingBox.position.x = pos.x;
	_boundingBox.position.y = pos.y;
	draw();
	_boundingBox.position.x = x;
	_boundingBox.position.y = y;
}

void RObject::update(int a_deltaTime) { }

bool RObject::isDestroyed()
{
	return _destroyed;
}

void RObject::setDestroyed(bool a_destroyed)
{
	_destroyed = a_destroyed;
}

eGroupTypeObject RObject::getGroupType()
{
	return _groupType;
}

bool RObject::isCollidingWith(RObject * object)
{
	return false;
}

void RObject::setCollidingWith(RObject * object)
{
}

bool RObject::isOverlappingWith(RObject * object)
{
	return false;
}

void RObject::setOverlappingWith(RObject * object)
{
}

bool RObject::isBackgroundObject()
{
	return _groupType == eGroupTypeObject::BACKGROUND;
}

bool RObject::isStairObject()
{
	return _groupType == eGroupTypeObject::GROUND && (_type == eTypeObject::STAIR_1 || _type == eTypeObject::STAIR_2);
}

bool RObject::isNormalGroundObject()
{
	return _groupType == eGroupTypeObject::GROUND && (_type == eTypeObject::GROUND_1 || _type == eTypeObject::GROUND_2 || _type == eTypeObject::GROUND_3);
}

eTypeObject RObject::getType()
{
	return _type;
}

int RObject::getX()
{
	return _boundingBox.position.x;
}

int RObject::getY()
{
	return _boundingBox.position.y;
}

void RObject::setX(int a_x)
{
	_boundingBox.position.x = a_x;
}

void RObject::setY(int a_y)
{
	_boundingBox.position.y = a_y;
}

float RObject::getVX()
{
	return _boundingBox.vx;
}

float RObject::getVY()
{
	return _boundingBox.vy;
}

void RObject::setVX(float a_vx)
{
	_boundingBox.vx = a_vx;
}

void RObject::setVY(float a_vy)
{
	_boundingBox.vy = a_vy;
}

int RObject::getHeight()
{
	return _boundingBox.height;
}

int RObject::getWidth()
{
	return _boundingBox.width;
}

int RObject::getIndex()
{
	return _index;
}

void RObject::setIndex(int index)
{
	_index = index;
}

int RObject::getZIndex()
{
	return _zIndex;
}

void RObject::setZIndex(int index)
{
	_zIndex = index;
}

GRect RObject::getBoundingBox()
{
	return GRect(_boundingBox);
}

GPoint2D RObject::getTopLeftPoint()
{
	return GPoint2D(_boundingBox.position.x - _boundingBox.width / 2, _boundingBox.position.y + _boundingBox.height / 2);
}

GRect RObject::getTopLeftBoundingBox()
{
	GRect boundingbox = getBoundingBox();
	boundingbox.position = this->getTopLeftPoint();
	return boundingbox;
}

void RObject::afterCollision(RObject * collided, CollisionInfo info, int deltaTime)
{
}

void RObject::onOverlapping(RObject * collided)
{
}

void RObject::afterCollisionWithWeapon(RObject *collided, CollisionInfo info) { }