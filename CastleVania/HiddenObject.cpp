#include "HiddenObject.h"
#include "InfoManager.h"
#include "ObjectConfig.h"
#include "Utils.h"

CHiddenObject::CHiddenObject(int a_type, float a_x, float a_y)
{
	_boundingBox.position.x = a_x;
	_boundingBox.position.y = a_y;
	_objectName = "chiddenobject";
	loadResource();
	_type = (eTypeObject)a_type;
	_groupType = eGroupTypeObject::STATIC_ITEM;
}

CHiddenObject::~CHiddenObject()
{
}

void CHiddenObject::actionCollidingSimon()
{
	switch (_type)
	{
	case eTypeObject::HiddenSwitchScene:
		CInfoManager::GetInstance()->StopClock();
		CInfoManager::GetInstance()->SwitchScene(true);
		CInfoManager::GetInstance()->SetNewPosition("gate", _boundingBox.position);

		break;
	case eTypeObject::HiddenPassableGate:
		CInfoManager::GetInstance()->StopClock();
		//CInfoManager::GetInstance()->SwitchScene(true);
		//CInfoManager::GetInstance()->SetNewPosition("gate", _boundingBox.position);
		//CInfoManager::GetInstance()->SetMoveableCameraBeforeGate(true);
		//CInfoManager::GetInstance()->SetMoveableCameraAfterGate(false);
		break;
	case eTypeObject::HiddenSpawnFishman:
		break;
	case eTypeObject::HiddenStopCamera:
		CInfoManager::GetInstance()->setStopCamera(true);
		break;
	case eTypeObject::HiddenStopSimonAfterGate:
		CInfoManager::GetInstance()->SetMoveableCameraAfterGate(true);
		break;
	case eTypeObject::HiddenBossBatActive:
		CInfoManager::GetInstance()->activeBoss();
		break;
	}
}

void CHiddenObject::onOverlapping(RObject * collided)
{
	switch (collided->getType())
	{
	case eTypeObject::HiddenBossBatActive:
		CInfoManager::GetInstance()->activeBoss();
		break;
	}
}

void CHiddenObject::draw(){ }
