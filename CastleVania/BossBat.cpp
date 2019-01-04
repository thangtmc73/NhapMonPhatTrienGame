#include "BossBat.h"
#include "InfoManager.h"
#include "Utils.h"
#include <cstdlib>
#include <ctime>
#include "Resources.h"

const int LIMIT_RIGHT = Resources::getInstance()->getIntegerConstWithName("bat-limit-right");
const int LIMIT_TOP = Resources::getInstance()->getIntegerConstWithName("bat-limit-top");
const int LIMIT_LEFT = Resources::getInstance()->getIntegerConstWithName("bat-limit-left");
const int LIMIT_BOTTOM = Resources::getInstance()->getIntegerConstWithName("bat-limit-bottom");

CBossBat::CBossBat(float a_x, float a_y, int a_leftDirection) : CEnemy(a_x, a_y, a_leftDirection)
{
	_objectName = "cbossbat";
	
	loadResource();
	_leftDirection = false;
	_animations = new RAnimation*[2];
	_animations[0] = new RAnimation(_sprite, 0, 0, 0, 100);
	_animations[1] = new RAnimation(_sprite, 1, 2, 1, 100);
	_state = 0;
	_type = eTypeObject::BossLv1;
	_timesCollidingToDie = 1;
	_ratioBetweenStrongAndWeakWhip = 1;
	_doneAction = true;
	_oldPosition.x = a_x;
	_oldPosition.y = a_y;
	_endPosition.x = a_x;
	_endPosition.y = a_y;
	_initialMove = false;
	_indexAction = eBatPosition::BAT_BOTTOM;
	_refreshTarget = true;
	_time = 0;
}

void CBossBat::update(int dt)
{

	this->runAnimation(dt);
	int timeBetweenActions = Resources::getInstance()->getIntegerConstWithName("bat-time-between-actions");
	if (CInfoManager::GetInstance()->isActiveBoss()) {
		if (!_initialMove) {
			if (_doneAction) {
				_doneAction = false;
				_state = 1;
				_endPosition = GPoint2D(_boundingBox.position.x, _boundingBox.position.y + Resources::getInstance()->getFloatConstWithName("distance-y-bat-initial"));
				_boundingBox.vy = -Resources::getInstance()->getFloatConstWithName("bat-vy");
			}
			else {
				if (checkWhenOutOfTarget()) {
					_initialMove = true;
					refreshTarget();
				}
			}
		}
		else {
			if (_doneAction) {
				_time += dt;
				if (_time < timeBetweenActions) {
					_boundingBox.vx = 0;
					_boundingBox.vy = 0;
				}
				else {
					_time = 0;
					_doneAction = false;
					int oldAction = _indexAction;
					_indexAction = rand() % 5;
					if (_indexAction == oldAction || _indexAction == eBatPosition::BAT_REFRESH) {
						refreshTarget();
						updateNewAction();
					}
					chooseTarget();
				}
			}
			else {
				if (checkWhenOutOfTarget()) {
					_doneAction = true;
				}
			}
		}
	}
	_boundingBox.position.x += _boundingBox.vx * dt;
	_boundingBox.position.y += _boundingBox.vy * dt;

}

void CBossBat::afterCollision(RBaseObject * collided, CollisionInfo info, int deltaTime)
{

}

void CBossBat::afterCollisionWithWeapon(RBaseObject * collided, CollisionInfo info)
{
	
}

void CBossBat::moveToLeftSimon()
{
	//if (_boundingBox.position.x < _boundingBox)
}

bool CBossBat::outOfBox(GPoint2D point)
{
	if (point.x <= LIMIT_LEFT || point.x >= LIMIT_RIGHT) {
		return true;
	}
	if (point.y <= LIMIT_BOTTOM || point.y >= LIMIT_TOP) {
		return true;
	}
	return false;
}

bool CBossBat::checkWhenOutOfTarget()
{
	if ((_indexAction == eBatPosition::BAT_BOTTOM && _boundingBox.position.y <= _endPosition.y)
	|| (_indexAction == eBatPosition::BAT_TOP && _boundingBox.position.y >= _endPosition.y)
	|| (_indexAction == eBatPosition::BAT_LEFT && _boundingBox.position.x <= _endPosition.x)
	|| (_indexAction == eBatPosition::BAT_RIGHT && _boundingBox.position.x >= _endPosition.x)) {
		_boundingBox.vx = 0;
		_boundingBox.vy = 0;
		_boundingBox.position.y = _endPosition.y;
		_doneAction = true;
		return true;
	}
	return false;
}

void CBossBat::updateNewAction()
{
	for (int i = 1; i <= 4; i++) {
		if (i != _indexAction) {
			_indexAction = i;
			return;
		}
	}
}

void CBossBat::chooseTarget()
{
	int oldAction = _indexAction;
	int timeDoAction = Resources::getInstance()->getIntegerConstWithName("bat-time-action");

		switch (_indexAction) {
		case eBatPosition::BAT_LEFT:
			_endPosition = _leftPosition;
			break;
		case eBatPosition::BAT_RIGHT:
			_endPosition = _rightPosition;
			break;
		case eBatPosition::BAT_BOTTOM:
			_endPosition = _bottomPosition;
			break;
		case eBatPosition::BAT_TOP:
			_endPosition = _topPosition;
			break;
		}
		_boundingBox.vx = (float)(_endPosition.x - _boundingBox.position.x) / timeDoAction;
		_boundingBox.vy = (float)(_endPosition.y - _boundingBox.position.y) / timeDoAction;

}

GPoint2D CBossBat::validatePosition(GPoint2D point)
{
	if (point.x <= LIMIT_LEFT) {
		point.x = LIMIT_LEFT;
	}
	if (point.x >= LIMIT_RIGHT) {
		point.x = LIMIT_RIGHT;
	}
	if (point.y >= LIMIT_TOP) {
		point.y = LIMIT_TOP;
	}
	if (point.y <= LIMIT_BOTTOM) {
		point.y = LIMIT_BOTTOM;
	}
	return point;
}

CBossBat::~CBossBat()
{
}

void CBossBat::PrepareForAction()
{
	GPoint2D simonPos = CInfoManager::GetInstance()->GetCurrentPosition("simon");
	float distanceX = abs(_boundingBox.position.x - simonPos.x);
	if (outOfBox(_endPosition)) {
		int a = 0;
	}
	float distanceY = abs(_boundingBox.position.y - simonPos.y);
	_doneAction = false;
	switch (_typeAction)
	{
	case 0:
		_endPosition.x = simonPos.x;
		_endPosition.y = simonPos.y;
		break;
	case 1:
		_endPosition.x = (_boundingBox.position.x - simonPos.x) * 2 + _boundingBox.position.x;
		_endPosition.y = simonPos.y + rand() * distanceY;
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	}
}

void CBossBat::refreshTarget()
{
	GPoint2D simonPos = CInfoManager::GetInstance()->GetCurrentPosition("simon");
	float distanceChooseTarget = Resources::getInstance()->getFloatConstWithName("distance-choose-target");
	if (_boundingBox.position.x < simonPos.x) {
		if (simonPos.x - _boundingBox.position.x >= distanceChooseTarget) {
			_leftPosition = _boundingBox.position;
			_rightPosition = _boundingBox.position;
			_rightPosition.x += ((simonPos.x - _leftPosition.x) * 2);
			_bottomPosition = simonPos;
			_topPosition = simonPos;
			_topPosition.y += ((_boundingBox.position.y - simonPos.y) * 2);
			float height = _topPosition.y - _bottomPosition.y;
			if (height < Resources::getInstance()->getFloatConstWithName("bat-default-y") && height >= 0) {
				_topPosition.y = _bottomPosition.y + Resources::getInstance()->getFloatConstWithName("bat-default-y");
			}
		}
		else {
			_bottomPosition = simonPos;
			_topPosition = _boundingBox.position;
			GPoint2D center;
			center.x = (_bottomPosition.x + _topPosition.x) / 2;
			center.y = (_bottomPosition.y + _topPosition.y) / 2;

			_leftPosition.y = center.y;
			_leftPosition.x = center.x - distanceChooseTarget;
			_rightPosition.y = center.y;
			_rightPosition.x = _leftPosition.x + distanceChooseTarget * 2;
			float height = _topPosition.y - _bottomPosition.y;
			if (height < Resources::getInstance()->getFloatConstWithName("bat-default-y") && height >= 0) {
				_topPosition.y = _bottomPosition.y + Resources::getInstance()->getFloatConstWithName("bat-default-y");
			}
		}
	}
	else {
		if (simonPos.x - _boundingBox.position.x <= -distanceChooseTarget) {
			_leftPosition = _boundingBox.position;
			_rightPosition = _boundingBox.position;
			_leftPosition.x -= ((_rightPosition.x - simonPos.x) * 2);
			_bottomPosition = simonPos;
			_topPosition = simonPos;
			_topPosition.y += ((_boundingBox.position.y - simonPos.y) * 2);
			if (_topPosition.y - _bottomPosition.y < Resources::getInstance()->getFloatConstWithName("bat-default-y")) {
				_topPosition.y = _bottomPosition.y + Resources::getInstance()->getFloatConstWithName("bat-default-y");
			}
		}
		else {
			_bottomPosition = simonPos;
			_topPosition = _boundingBox.position;
			GPoint2D center;
			center.x = (_bottomPosition.x + _topPosition.x) / 2;
			center.y = (_bottomPosition.y + _topPosition.y) / 2;


			_leftPosition.y = center.y;
			_leftPosition.x = center.x - distanceChooseTarget;
			_rightPosition.y = center.y;
			_rightPosition.x = _leftPosition.x + distanceChooseTarget * 2;
			if (_topPosition.y - _bottomPosition.y < Resources::getInstance()->getFloatConstWithName("bat-default-y")) {
				_topPosition.y = _bottomPosition.y + Resources::getInstance()->getFloatConstWithName("bat-default-y");
			}
		}
	}

	_leftPosition = validatePosition(_leftPosition);
	_topPosition = validatePosition(_topPosition);
	_rightPosition = validatePosition(_rightPosition);
	_bottomPosition = validatePosition(_bottomPosition);
}
