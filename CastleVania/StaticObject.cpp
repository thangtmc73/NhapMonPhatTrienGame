#include "StaticObject.h"
#include "Utils.h"
#include "RObjectManager.h"
CStaticObject::CStaticObject() : RBaseObject() { }

CStaticObject::~CStaticObject() {}

void CStaticObject::update(int a_deltaTime)
{
	_listColliding.clear();
	this->runAnimation(a_deltaTime);
	RObjectManager::GetInstance()->collidingWith(this, a_deltaTime);
}
