#include "MedusaHead.h"
#include "Utils.h"

CMedusaHead::CMedusaHead(int a_x, int a_y, int a_leftDirection) : CEnemy(a_x, a_y, a_leftDirection) {
	//SPRITE = new GTexture("medusahead.png", 2, 1, 2);
	//_boundingBox.height = SPRITE->FrameHeight = 32;
	//_boundingBox.width = SPRITE->FrameWidth = 32;
	//_sprite->_start = 0;
	//_sprite->_end = 1;
	//_sprite->_index = 0;
	//_sprite->_timeAni = 100;
	//_type = eTypeObject::EnemyMedusa;
	//_timesCollidingToDie = 1;
	//_ratioBetweenStrongAndWeakWhip = 1;
	//_leftDirection = false;
	//_startY = a_y;
}

void CMedusaHead::AfterCollision(RBaseObject * collided, CollisionInfo info) {
}

void CMedusaHead::AfterCollisionWithWeapon() {
}

void CMedusaHead::update(int a_deltaTime) {
	if (_leftDirection) {
		_boundingBox.vx = -SIMON_NORMAL_VX;
	}
	else {
		_boundingBox.vx = SIMON_NORMAL_VX;
	}
	_boundingBox.position.x += (a_deltaTime * _boundingBox.vx);
	_boundingBox.position.y = 50 * sin((_boundingBox.position.x) * 0.125) + _startY;
}

CMedusaHead::~CMedusaHead() { }
