#include "Gate.h"
#include "InfoManager.h"
#include "Utils.h"
#include "Resources.h"

CGate::CGate(float a_x, float a_y) : CStaticObject()
{
	_boundingBox.position.x = a_x;
	_boundingBox.position.y = a_y;
	_objectName = "cgate";
	loadResource();
	_animations = new RAnimation*[1];
	_animations[0] = new RAnimation(_sprite, 0, 2, 0, 100);
	_type = eTypeObject::Gate;
	_groupType = eGroupTypeObject::STATIC_ITEM;
	_startAnimation = false;
	_collided = false;
}

CGate::~CGate()
{
}

void CGate::update(int a_deltaTime)
{
	bool k = true;
	if (CInfoManager::GetInstance()->shouldOpenGate() && _collided)
	{
		_startAnimation = true;
		CInfoManager::GetInstance()->setShouldOpenGate(false);
	}
	if (_startAnimation && _animations[0]->updateOnceTime(a_deltaTime))
	{
		CInfoManager::GetInstance()->SetMovingThroughGate(true);
		//CInfoManager::GetInstance()->SwitchScene(true);
		_startAnimation = false;
	}
}

void CGate::actionCollidingSimon()
{
	if (!_collided)
	{
		CInfoManager::GetInstance()->SetMoveableCameraBeforeGate(true);
		CInfoManager::GetInstance()->SetNewPosition("gate", _boundingBox.position);
		_collided = true;
	}
}
