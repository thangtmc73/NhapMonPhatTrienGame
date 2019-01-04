#include "Panther.h"
#include "ObjectConfig.h"
#include "InfoManager.h"
#include "Resources.h"
#include "RObjectManager.h"

CPanther::CPanther(float a_x, float a_y, int a_leftDirection) : CEnemy(a_x, a_y, a_leftDirection)
{
	_objectName = "cpanther";
	loadResource();
	_animations = new RAnimation*[4];
	_animations[PantherState::PANTHER_RUNNING] = new RAnimation(_sprite, 1, 2, 1, 100);
	_animations[PantherState::PANTHER_JUMPING] = new RAnimation(_sprite, 3, 3, 3, 0);
	_animations[PantherState::SITTING_DOWN] = new RAnimation(_sprite, 0, 0, 0, 0);
	_animations[PantherState::PANTHER_FALLING] = new RAnimation(_sprite, 3, 3, 3, 0);
	setState(PantherState::SITTING_DOWN);
	_state = PantherState::SITTING_DOWN;
	_type = eTypeObject::EnemyPanther;
	_timesCollidingToDie = 1;
	_ratioBetweenStrongAndWeakWhip = 1;

	// groundCollidedFlag = true update leftDirection
	groundCollidedFlag = true;
}

void CPanther::setState(int a_state)
{
	if (_state == a_state || (_state != a_state && (a_state >= PantherState::TOTAL_PANTHER_STATES || a_state < 0)))
	{
		return;
	}
	_state = a_state;
	switch (_state)
	{
	case PantherState::SITTING_DOWN:
		break;
	case PantherState::PANTHER_JUMPING:
		break;
	case PantherState::PANTHER_RUNNING:
		break;
	case PantherState::PANTHER_FALLING:
		break;
	}
}

void CPanther::update(int a_deltaTime)
{
	_listColliding.clear();
	this->runAnimation(a_deltaTime);
	if (isInAttackingSimonRange()) {
		if (_state == PantherState::SITTING_DOWN) {
			setState(PantherState::PANTHER_RUNNING);
			UpdateVx();
		}
		else if (_state == PantherState::PANTHER_JUMPING && _boundingBox.vy < 0) {
			setState(PantherState::PANTHER_FALLING);
		}
	}
	else if (_state == PantherState::PANTHER_JUMPING && _boundingBox.vy < 0) {
		setState(PantherState::PANTHER_FALLING);
	}
	RObjectManager::GetInstance()->collidingWith(this, a_deltaTime);
	if (_state == PantherState::PANTHER_RUNNING && _boundingBox.vy != 0) {
		_boundingBox.vy = Resources::getInstance()->getFloatConstWithName("panther-jump-vy");
		UpdateVx();
		setState(PantherState::PANTHER_JUMPING);
	}
	_boundingBox.position.x += _boundingBox.vx * a_deltaTime;
	_boundingBox.position.y += _boundingBox.vy * a_deltaTime;
	_boundingBox.vy -= Resources::getInstance()->getFloatConstWithName("gravity") * a_deltaTime;
}


void CPanther::afterCollisionWithWeapon()
{
	CInfoManager::GetInstance()->ChangeScore(200);
}

void CPanther::processWhenCollidingWithGround(RObject * collided, CollisionInfo info, int deltaTime)
{
	if (collided->getGroupType() == eGroupTypeObject::GROUND) {
		if (collided->isNormalGroundObject()) {
			switch (info.direction) {
			case eDirection::TOP:
				_boundingBox.position.x += info.collisionTime * deltaTime * _boundingBox.vx;
				_boundingBox.position.y += (info.collisionTime * deltaTime * _boundingBox.vy + 1);
				_boundingBox.vy = 0;
				updateStateAfterCollidingGround();
				break;
			case eDirection::LEFT:
				_boundingBox.position.x += info.collisionTime * deltaTime * _boundingBox.vx;
				_boundingBox.position.y += info.collisionTime * deltaTime * _boundingBox.vy;
				_boundingBox.vx = -_boundingBox.vx;

				_boundingBox.position.x += (1 - info.collisionTime) * deltaTime * _boundingBox.vx;
				_leftDirection = !_leftDirection;
				break;
			case eDirection::RIGHT:
				_boundingBox.position.x += info.collisionTime * deltaTime * _boundingBox.vx;
				_boundingBox.position.y += info.collisionTime * deltaTime * _boundingBox.vy;
				_boundingBox.vx = -_boundingBox.vx;
				_boundingBox.position.x += (1 - info.collisionTime) * deltaTime * _boundingBox.vx;

				_leftDirection = !_leftDirection;

				break;
			default:
				break;
			}
		}
	}
}

CPanther::~CPanther()
{
}

void CPanther::updateStateAfterCollidingGround()
{
	if (_state == PantherState::PANTHER_FALLING) {
		setState(PantherState::PANTHER_RUNNING);
		ChangeDirection();
		UpdateVx();
	}
}

void CPanther::ChangeDirection()
{
	GPoint2D simonPosition = CInfoManager::GetInstance()->GetCurrentPosition("simon");
	float distance = _boundingBox.position.x - simonPosition.x;
	if (distance < 0.0f)
	{
		_leftDirection = false;
	}
	else if (distance > 0.0f)
	{
		_leftDirection = true;
	}
}

bool CPanther::isInAttackingSimonRange()
{
	GPoint2D simonPosition = CInfoManager::GetInstance()->GetCurrentPosition("simon");
	float distance = _boundingBox.position.x - simonPosition.x;
	float attackingSimonRange = Resources::getInstance()->getFloatConstWithName("panther-distance-near-simon");
	if (distance < attackingSimonRange && distance > -attackingSimonRange)
	{
		return true;
	}
	return false;
}

void CPanther::UpdateVx()
{
	float vx = Resources::getInstance()->getFloatConstWithName("panther-vx");
	setVxWithLeftDirection(vx);
}
