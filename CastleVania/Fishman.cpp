#include "Fishman.h"
#include "ObjectManager.h"
#include "Utils.h"
#include "Log.h"
#include "Resources.h"

CFishman::CFishman(float a_x, float a_y, int a_leftDirection) : CEnemy(a_x, a_y, a_leftDirection)
{
	_boundingBox.position.x = a_x;
	_boundingBox.position.y = a_y;
	_objectName = "cfishman";
	loadResource();

	_animations = new RAnimation*[3];
	_animations[FishmanState::FISHMAN_DOWN] = new RAnimation(_sprite, 2, 2, 2, 0);
	_animations[FishmanState::FISHMAN_JUMPING] = new RAnimation(_sprite, 2, 2, 2, 0);
	_animations[FishmanState::FISHMAN_RUNNING] = new RAnimation(_sprite, 1, 2, 1, 100);
	_timesCollidingToDie = 1;
	_ratioBetweenStrongAndWeakWhip = 1;
	_boundingBox.vx = 0;
	_boundingBox.vy = 0;
	_type = eTypeObject::EnemyFishMan;
	setState(FishmanState::FISHMAN_JUMPING);
}
bool CFishman::canStopJumping()
{
	if (!_passedGroundToStop) {
		return false;
	}
	GPoint2D fishman = this->getTopLeftPoint();
	if (fishman.y > _positionTopLeftGround.y + 40) {
		_boundingBox.position.y = _positionTopLeftGround.y + 36;
		return true;
	}
	return false;
}
void CFishman::setState(int a_state)
{
	_state = a_state;
	switch (_state)
	{
	case FishmanState::FISHMAN_DOWN://int (=2)
		//_sprite->_start = 2;
		//_sprite->_index = 2;
		//_sprite->_end = 2;
		//_sprite->_timeAni = 100;
		//_boundingBox.vy = FISH_MAN_JUMP_VY;
		_boundingBox.vx = 0;
		break;
	case FishmanState::FISHMAN_JUMPING://int (=1)
		//_sprite->_start = 2;
		//_sprite->_index = 2;
		//_sprite->_end = 2;
		//_sprite->_timeAni = 100;
		_boundingBox.vy = 0.4;
		_boundingBox.vx = 0;
		break;
	case FishmanState::FISHMAN_RUNNING://int (=0)
		//_sprite->_start = 1;
		//_sprite->_index = 1;
		//_sprite->_end = 2;
		//_sprite->_timeAni = 100;
		_boundingBox.vy = 0;
		if (isLeftDirection())
		{
			_boundingBox.vx = -0.1;
		}
		else
		{
			//_boundingBox.vx = FISH_MAN_NORMAL_VX;
		}
		_boundingBox.vy = 0;
		break;
	}
}

void CFishman::update(int a_deltaTime)
{
	_listColliding.clear();
	this->runAnimation(a_deltaTime);
	_boundingBox.vy -= Resources::getInstance()->getFloatConstWithName("gravity") * a_deltaTime;
	if (_state == FishmanState::FISHMAN_JUMPING) {
		if (canStopJumping()) {
			setState(FishmanState::FISHMAN_RUNNING);
		}
		_boundingBox.position.x += _boundingBox.vx * a_deltaTime;
		_boundingBox.position.y += _boundingBox.vy * a_deltaTime;
		return;
	}
	if (_collidingWithAnyGround) {
		_boundingBox.vy = 0;
	}
	float vx = Resources::getInstance()->getFloatConstWithName("fishman-vx");
	setVxWithLeftDirection(vx);


	_boundingBox.position.x += _boundingBox.vx * a_deltaTime;
	_boundingBox.position.y += _boundingBox.vy * a_deltaTime;
}

void CFishman::processWhenCollidingWithGround(RObject * collided, CollisionInfo info, int deltaTime)
{
	if (collided->getGroupType() == eGroupTypeObject::GROUND) {
		if (collided->isNormalGroundObject()) {
			if (info.direction == eDirection::TOP) {
				_boundingBox.position.x += info.collisionTime * _boundingBox.vx;
				_boundingBox.position.y += ((info.collisionTime * _boundingBox.vy));
				_boundingBox.position.y = collided->getBoundingBox().position.y + collided->getBoundingBox().height / 2 + _boundingBox.height / 2 + 1;
				_collidingWithAnyGround = true;
			}

			if ((info.direction == eDirection::LEFT || info.direction == eDirection::RIGHT)
				&& (collided->isNormalGroundObject())) {
				GRect boundingBoxCollided = collided->getBoundingBox();
			}
			if ((info.direction == eDirection::BOTTOM)
				&& (collided->isNormalGroundObject())) {
				if (!_passedGroundToStop) {
					_positionTopLeftGround = collided->getTopLeftPoint();
					_passedGroundToStop = true;
				}

			}
		}
	}
}

CFishman::~CFishman()
{
}
