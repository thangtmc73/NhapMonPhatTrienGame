#include "MoneyBag.h"
#include "Resources.h"
#include "InfoManager.h"

CMoneyBag::CMoneyBag(float a_x, float a_y) : CDynamicObject()
{
	_boundingBox.position.x = a_x;
	_boundingBox.position.y = a_y;
	_objectName = "cmoneybag";
	loadResource();
}

void CMoneyBag::actionCollidingSimon()
{
	CInfoManager::GetInstance()->ChangeScore(_bonus);
	_destroyed = true;
}

CMoneyBag::~CMoneyBag()
{
}
