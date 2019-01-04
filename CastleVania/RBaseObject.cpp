#include "RBaseObject.h"
#include "GCamera.h"
#include "Global.h"
#include "Utils.h"
#include "Resources.h"
#include "RSprite.h"

RBaseObject::RBaseObject()
{
	_boundingBox.position.x = _boundingBox.position.y = 0;
	_sprite = NULL;
	_destroyed = false;
	_state = 0;
}

RBaseObject::~RBaseObject()
{
	//delete SPRITE;
	if (_sprite != NULL)
	{
		delete _sprite;
	}
}

bool RBaseObject::isCollidingWith(RObject * object)
{
	return _listColliding.find(object) != _listColliding.end();
}

void RBaseObject::setCollidingWith(RObject * object)
{
	_listColliding.insert(object);
}

bool RBaseObject::isOverlappingWith(RObject * object)
{
	return _listOverlapping.find(object) != _listOverlapping.end();
}

void RBaseObject::setOverlappingWith(RObject * object)
{
	_listOverlapping.insert(object);
}

void RBaseObject::CollideWith(RBaseObject * a_collided)
{
}

bool RBaseObject::isLeftDirection()
{
	return false;
}

GRect RBaseObject::GetFirstBrick()
{
	return GRect(0, 0, 0, 0, 0, 0);
}

GRect RBaseObject::GetSecondBrick()
{
	return GRect(0, 0, 0, 0, 0, 0);
}

void RBaseObject::draw()
{
	_sprite->draw(_boundingBox.position.x, _boundingBox.position.y);
}

void RBaseObject::drawWithCamera(GCamera *a_camera)
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

void RBaseObject::runAnimation(int a_deltaTime)
{
	if (_animations != NULL) {
		_animations[_state]->update(a_deltaTime);
	}
}

void RBaseObject::update(int a_deltaTime)
{
	_listColliding.clear();
	this->runAnimation(a_deltaTime);
}

int RBaseObject::getState() {
	return _state;
}

void RBaseObject::setState(int state) {
	if (_state != state) {
		_state = state;
	}
}

void RBaseObject::loadResource()
{
	ObjectResourceObject object = Resources::getInstance()->getObjectResourceInfo(_objectName);
	_sprite = new RSprite(Resources::getInstance()->getTextureWithName(object.textureName));
	_sprite->setSpriteSheetInfo(object.spriteSheet);
	_boundingBox.height = object.boundingBoxHeight;
	_boundingBox.width = object.boundingBoxWidth;
}

GRect RBaseObject::getBoundingBox()
{
	return GRect(_boundingBox);
}

GPoint2D RBaseObject::getTopLeftPoint()
{
	return GPoint2D(_boundingBox.position.x - _boundingBox.width / 2, _boundingBox.position.y + _boundingBox.height / 2);
}

GRect RBaseObject::getTopLeftBoundingBox()
{
	GRect boundingbox = getBoundingBox();
	boundingbox.position = this->getTopLeftPoint();
	return boundingbox;
}

void RBaseObject::afterCollision(RObject * collided, CollisionInfo info, int deltaTime)
{
	processWhenCollidingWithGround(collided, info, deltaTime);
	eGroupTypeObject groupType = collided->getGroupType();
	switch (groupType) {
	case eGroupTypeObject::MAIN:
		this->actionCollidingSimon();
		break;
	case eGroupTypeObject::ENEMY:
		this->actionCollidingEnemy();
		break;
	}
}

void RBaseObject::processWhenCollidingWithGround(RObject * collided, CollisionInfo info, int deltaTime)
{
	if (collided->getGroupType() == eGroupTypeObject::GROUND) {
		if (collided->isNormalGroundObject()) {
			switch (info.direction) {
			case eDirection::TOP:
				_boundingBox.position.x += info.collisionTime * deltaTime * _boundingBox.vx;
				_boundingBox.position.y += (info.collisionTime * deltaTime * _boundingBox.vy + 1);
				_boundingBox.vy = 0;
				break;
			case eDirection::LEFT:
				_boundingBox.position.x += info.collisionTime * deltaTime * _boundingBox.vx;
				_boundingBox.position.y += info.collisionTime * deltaTime * _boundingBox.vy;
				_boundingBox.vx = 0;
				break;
			case eDirection::RIGHT:
				_boundingBox.position.x += info.collisionTime * deltaTime * _boundingBox.vx;
				_boundingBox.position.y += info.collisionTime * deltaTime * _boundingBox.vy;
				_boundingBox.vx = 0;
				break;
			default:
				break;
			}

		}
	}
}

void RBaseObject::actionCollidingSimon()
{
}

void RBaseObject::actionCollidingEnemy()
{
}

void RBaseObject::afterCollisionWithWeapon(RObject *collided, CollisionInfo info) { }

bool RBaseObject::isCollindingWith(RBaseObject * a_collided)
{
	return false;
}
