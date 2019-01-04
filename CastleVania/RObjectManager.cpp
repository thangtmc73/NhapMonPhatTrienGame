#include "RObjectManager.h"
#include "DynamicObject.h"
#include "StaticObject.h"
#include "GCamera.h"
#include "Global.h"
#include "BigCandle.h"
#include "LittleCandle.h"
#include "SpearKnight.h"
#include "HiddenObject.h"
#include "Stair.h"
#include "Brick.h"
#include "ObjectConfig.h"
#include "Ghoul.h"
#include "Fishman.h"
#include "MedusaHead.h"
#include "Simon.h"
#include "Panther.h"
#include "GSystem.h"
#include "Utils.h"
#include "Gate.h"
#include "RGrid.h"
#include "BossBat.h"
#include "Bat.h"
#include "RTiledBG.h"
#include <algorithm>
#include <vector>
#include "Log.h"
#include "TinyXML/tinyxml.h"

RObjectManager* RObjectManager::_instance = NULL;

RObjectManager * RObjectManager::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new RObjectManager();
	}
	return _instance;
}

void RObjectManager::addObject(int a_index, RObject * a_newObject)
{
	if (a_newObject == NULL)
	{
		return;
	}
	_listOfAllObjects[a_index] = a_newObject;
	_listOfAllObjects[a_index]->setIndex(a_index);
	_deptObject[_listOfAllObjects[a_index]->getZIndex()].push_back(_listOfAllObjects[a_index]);
}

void RObjectManager::setInitialGridInfo(int a_mapWidth, int a_mapHeight, int a_cellWidth, int a_cellHeight)
{
	_grid->setInitialInfo(a_mapWidth, a_mapHeight, a_cellWidth, a_cellHeight);
}

void RObjectManager::calculateGameObjectInCell()
{
	CSimon *simon = getSimon();
	for (std::map<int, RObject*>::iterator it = _listOfAllObjects.begin(); it != _listOfAllObjects.end(); ++it)
	{
		if (it->second != simon) _grid->retrieve(it->second);
	}
}

void RObjectManager::loadObjectsFromFile(const char * a_filePath)
{
	TiXmlDocument doc(a_filePath);
	bool success = doc.LoadFile();
	if (success)
	{
		//TiXmlElement* root = doc.FirstChildElement();
		TiXmlElement* root = doc.RootElement();
		for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
		{
			const char *value = elem->Value();
			std::string nodeName = value;
			if (nodeName == "items") {
				loadItemObjectsFromXml(elem);
			}
			if (nodeName == "texture_background") {
				_textureBackground = elem->FirstChild()->Value();
				_bgInfo.frameHeight = 32;
				_bgInfo.frameWidth = 32;
				for (TiXmlAttribute* attribute = elem->FirstAttribute(); attribute != NULL; attribute = attribute->Next())
				{
					std::string name = attribute->Name();
					if (name == "cols") {
						_bgInfo.numCols = atoi(attribute->Value());
						continue;
					}
					if (name == "rows") {
						_bgInfo.numRows = atoi(attribute->Value());
						int a = atoi(elem->Value());
						continue;
					}
					if (name == "numTiles") {
						_bgInfo.numFrames = atoi(attribute->Value());
						continue;
					}
				}
			}
		}
	}
	else
	{
		doc.ErrorDesc();
		return;
	}
}

void RObjectManager::drawAllObjects()
{
	for (std::map<int, std::vector<RObject*>>::iterator it = _deptObject.begin(); it != _deptObject.end(); it++) {
		for (std::vector<RObject*>::iterator object = it->second.begin(); object != it->second.end(); ++object) {
			if (!(*object)->isDestroyed()) {
				(*object)->draw();
				++_numberObjectDrawn;
			}
		}
	}
}

void RObjectManager::drawAllObjectsWithCameraAndGrid(GCamera * a_camera)
{
	if (a_camera == NULL)
	{
		drawAllObjectsWithCamera(a_camera);
		return;
	}

	_numberObjectDrawn = 0;
	for (std::map<int, std::vector<RObject*>>::iterator it = _deptObject.begin(); it != _deptObject.end(); it++) {
		for (std::vector<RObject*>::iterator itDept = it->second.begin(); itDept != it->second.end(); ++itDept) {
			if (std::find(_listObjectsInGrid.begin(), _listObjectsInGrid.end(), (*itDept)) == _listObjectsInGrid.end()) continue;

			if (!(*itDept)->isDestroyed()) {
				(*itDept)->drawWithCamera(a_camera);
				++_numberObjectDrawn;
			}
		}
	}

}

void RObjectManager::drawAllObjectsWithCamera(GCamera *a_camera)
{
	if (a_camera == NULL)
	{
		drawAllObjects();
		return;
	}

	_numberObjectDrawn = 0;

	for (std::map<int, std::vector<RObject*>>::iterator it = _deptObject.begin(); it != _deptObject.end(); it++) {
		for (std::vector<RObject*>::iterator itDept = it->second.begin(); itDept != it->second.end(); ++itDept) {
			if (!(*itDept)->isDestroyed()) {
				(*itDept)->drawWithCamera(a_camera);
				++_numberObjectDrawn;
			}
		}
	}

}

void RObjectManager::removeObjectWithIndex(int a_index)
{
	_listOfAllObjects.erase(a_index);
}

void RObjectManager::collidingWith(RObject *a_object, int a_deltaTime)
{
	eGroupTypeObject groupTypeObject = a_object->getGroupType();
	CSimon *simon;
	for (std::map<int, RObject*>::iterator it = _listOfAllObjects.begin(); it != _listOfAllObjects.end(); it++)
	{
		RObject *collided = it->second;
		eGroupTypeObject groupTypeOther = collided->getGroupType();
		if (it->second->isCollidingWith(a_object)) continue;

		if (groupTypeObject == groupTypeOther || a_object->isDestroyed() || it->second->isDestroyed() || groupTypeOther == eGroupTypeObject::BACKGROUND)
		{
			continue;
		}

		if (groupTypeObject == eGroupTypeObject::MAIN) {
			simon = (CSimon*)a_object;
			if (simon->IsWhipAttackable())
			{
				CollisionInfo collisionWhip = IsCollide(it->second, simon->GetWhip(), a_deltaTime);
				if (collisionWhip.collisionTime < 1 || IsAABBCheck(it->second->getTopLeftBoundingBox(), simon->GetWhip()->getTopLeftBoundingBox()))
				{
					it->second->afterCollisionWithWeapon(it->second, collisionWhip);
				}
			}
		}

		CollisionInfo info = IsCollide(a_object, it->second, a_deltaTime);
		if (info.collisionTime < 1) {
			a_object->afterCollision(it->second, info, a_deltaTime);
			it->second->afterCollision(a_object, info, a_deltaTime);
			a_object->setCollidingWith(it->second);
			it->second->setCollidingWith(a_object);
		}
		if (IsAABBCheck(it->second->getTopLeftBoundingBox(), a_object->getTopLeftBoundingBox())) {
			a_object->setOverlappingWith(it->second);
			a_object->onOverlapping(it->second);
			it->second->setOverlappingWith(a_object);
			it->second->onOverlapping(a_object);

		}
	}
}

void RObjectManager::updateAllObjects(float a_deltaTime)
{
	for (std::map<int, RObject*>::iterator it = _listOfAllObjects.begin(); it != _listOfAllObjects.end();)
	{
		auto k = it++;
		k->second->update(a_deltaTime);
	}
}

void RObjectManager::collideEachOther(int a_delta_time)
{
	std::map<int, CStaticObject*>::iterator it_tempt;
	bool collidingWithStair = false;
	CSimon *simon = NULL;

	for (std::map<int, RObject*>::iterator colliding = _listOfAllObjects.begin(); colliding != _listOfAllObjects.end(); colliding++)
	{
		if (colliding->second->isBackgroundObject() || colliding->second->isDestroyed()) {
			continue;
		}
		eGroupTypeObject collidingType = colliding->second->getGroupType();
		if (collidingType == eGroupTypeObject::GROUND ||
			collidingType == eGroupTypeObject::STATIC_ITEM)
		{
			continue;
		}

		for (std::map<int, RObject*>::iterator collided = _listOfAllObjects.begin(); collided != _listOfAllObjects.end(); collided++)
		{
			if (collided->second->isBackgroundObject() || collided->second->isDestroyed()) {
				continue;
			}
			if (collidingType == eGroupTypeObject::MAIN) {
				simon = (CSimon*)colliding->second;
			}
			eGroupTypeObject collidedType = collided->second->getGroupType();
			if (collidingType == collidedType || collidedType == eGroupTypeObject::MAIN ||
				(collidedType == eGroupTypeObject::ENEMY && collidingType == eGroupTypeObject::DYNAMIC_ITEM) ||
				(collidingType == eGroupTypeObject::ENEMY &&
				(collidedType == eGroupTypeObject::STATIC_ITEM || collidedType == eGroupTypeObject::DYNAMIC_ITEM)))
			{
				continue;
			}
			
			if (collidingType == eGroupTypeObject::MAIN)
			{
				CSimon* simon = (CSimon*)colliding->second;
				if (simon->IsWhipAttackable())
				{
					CollisionInfo collisionWhip = IsCollide(collided->second, simon->GetWhip(), a_delta_time);
					if (collisionWhip.collisionTime < 1 || IsAABBCheck(collided->second->getTopLeftBoundingBox(), simon->GetWhip()->getTopLeftBoundingBox()))
					{
						collided->second->afterCollisionWithWeapon(simon->GetWhip(), collisionWhip);
					}
				}
			}
			if (colliding->second->getType() == eTypeObject::EnemyFishMan && (collided->second->getIndex() == 1))
			{
				int a = 0;
			}

			CollisionInfo collision = IsCollide(colliding->second, collided->second, a_delta_time);
			if (colliding->second->getIndex() == 11132 && collidedType == eGroupTypeObject::GROUND && collision.direction != eDirection::NONE) {
				int a = 0;
			}
			if (collision.collisionTime < 1)
			{
				if (colliding->second->getType() == eTypeObject::EnemyFishMan)
				{
					int a = 0;
				}
				colliding->second->afterCollision(collided->second, collision, a_delta_time);
				collided->second->afterCollision(colliding->second, collision, a_delta_time);
				if (collidingType == eGroupTypeObject::MAIN
					&& collided->second->isStairObject()) {
					collidingWithStair = true;
				}
				if (collision.direction == eDirection::LEFT && (collided->second->isNormalGroundObject())) {
					int a = 0;
				}
			}
			else {
				if (collidingType == eGroupTypeObject::MAIN
					&& collidedType == eGroupTypeObject::GROUND
					&& IsColliding(colliding->second, collided->second)) {
					if (collided->second->getType() == eTypeObject::STAIR_1 || collided->second->getType() == eTypeObject::STAIR_2) {
						collidingWithStair = true;
					}
					else if (collided->second->isNormalGroundObject()) {
						int a = 0;
					}
				}
			}
			//colliding->second->
		}
	}
	if (collidingWithStair) {
		int a = 0;
	}
	simon->setSteppable(collidingWithStair);
}

void RObjectManager::collideEachOtherInGrid(int a_deltaTime)
{
	std::map<int, CStaticObject*>::iterator it_tempt;

	for (std::set<RObject*>::iterator colliding = _listObjectsInGrid.begin(); colliding != _listObjectsInGrid.end(); colliding++)
	{
		RObject* collidingObject = *colliding;
		eGroupTypeObject collidingType = collidingObject->getGroupType();
		if (collidingType == eGroupTypeObject::GROUND ||
			collidingType == eGroupTypeObject::STATIC_ITEM)
		{
			continue;
		}
		for (std::set<RObject*>::iterator collided = _listObjectsInGrid.begin(); collided != _listObjectsInGrid.end(); collided++)
		{
			RObject* collidedObject = *collided;
			eGroupTypeObject collidedType = collidedObject->getGroupType();
			if (collidingType == collidedType || collidedType == eGroupTypeObject::MAIN ||
				(collidedType == eGroupTypeObject::ENEMY && collidingType == eGroupTypeObject::DYNAMIC_ITEM) ||
				(collidingType == eGroupTypeObject::ENEMY &&
				(collidedType == eGroupTypeObject::STATIC_ITEM || collidedType == eGroupTypeObject::DYNAMIC_ITEM)))
			{
				continue;
			}
			if (collidingType == eGroupTypeObject::MAIN)
			{
				CSimon* simon = (CSimon*)collidingObject;
				if (simon->IsWhipAttackable())
				{
					CollisionInfo collisionWhip = IsCollide(collidedObject, simon->GetWhip(), a_deltaTime);
					if (collisionWhip.collisionTime < 1 || IsAABBCheck(collidedObject->getBoundingBox(), simon->GetWhip()->getBoundingBox()))
					{
						collidedObject->afterCollisionWithWeapon(collidingObject, collisionWhip);
					}
				}
			}
			CollisionInfo collision = IsCollide(collidingObject, collidedObject, a_deltaTime);
			if (collision.collisionTime < 1)
			{
				collidingObject->afterCollision(collidedObject, collision, a_deltaTime);
				collidedObject->afterCollision(collidingObject, collision, a_deltaTime);
			}
			//colliding->second->
		}
	}
}

void RObjectManager::checkViewportWithGrid(GCamera * a_camera)
{
	_grid->clearNonBackgroundObject();
	for (std::map<int, RObject*>::iterator it = _listOfAllObjects.begin(); it != _listOfAllObjects.end(); ++it)
	{
		if (it->second->isDestroyed() || it->second->isBackgroundObject()) continue;
		_grid->retrieve(it->second);
	}
	GRect viewport = GRect(a_camera->viewport.x, a_camera->viewport.y, a_camera->_minSize, a_camera->viewport.y, 0, 0);
	_listObjectsInGrid = _grid->getListGameObjectUpdate(viewport);
	CSimon *simon = getSimon();
	if (simon != NULL) _listObjectsInGrid.insert(getSimon());
}

void RObjectManager::updateGameObjectsInGrid(float a_deltaTime)
{
	_numberObjectUpdate = 0;
	//for (auto t = _listObjectsInGrid.begin(); t != _listObjectsInGrid.end();)
	//{
	//	(*t)->update(a_deltaTime);
	//	_numberObjectUpdate++;
	//	t++;

	//}

	for (auto t = _listObjectsInGrid.begin(); t != _listObjectsInGrid.end(); ++t)
	{
		(*t)->update(a_deltaTime);
		++_numberObjectUpdate;
	}
	//for (auto t = _listObjectsInGrid.begin(); t != _listObjectsInGrid.end(); ++t)
	//{
	//	int a = _listObjectsInGrid.size();
	//	if ((*t)->isDestroyed())
	//	{
	//		delete *t;
	//		_listOfAllObjects.erase((*t)->getIndex());
	//		_listObjectsInGrid.erase(t--);
	//	}
	//	else {
	//		(*t)->update(a_deltaTime);
	//		++_numberObjectUpdate;
	//	}
	//}
	//_grid->clearData();
}

void RObjectManager::setNeedToGetStair(bool a_true)
{
	_needToGetStair = a_true;
}

void RObjectManager::clear()
{
	for (std::map<int, RObject*>::iterator it = _listOfAllObjects.begin(); it != _listOfAllObjects.end(); it++)
	{
		delete(it->second);
		_listOfAllObjects[it->first] = NULL;
	}
	for (std::map<int, std::vector<RObject*>>::iterator it = _deptObject.begin(); it != _deptObject.end(); it++) {
		it->second.clear();
	}
	_deptObject.clear();
	_listObjectsInGrid.clear();
	_listOfAllObjects.clear();

	_grid->clear();
	_needToGetStair = false;
	_numberSpawn = 0;
	_indexSimon = -1;
}

void RObjectManager::spawnFishmen(GPoint2D positionSimon, float dt)
{
	_timeSpwan += dt;
	if (_timeSpwan > 3000) {
		++_numberSpawn;
		_timeSpwan = 0;
		_listOfAllObjects[_numberSpawn * 1000 + 1] = new CFishman(positionSimon.x - 100, 0, 0);
		_listOfAllObjects[_numberSpawn * 1000 + 2] = new CFishman(positionSimon.x + 100, 0, 1);
	}
}

CSimon * RObjectManager::getSimon()
{
	if (_indexSimon == -1) {
		return NULL;
	}
	return (CSimon*)_listOfAllObjects[_indexSimon];
}

void RObjectManager::killAllEnemy()
{
	for (std::map<int, RObject*>::iterator it = _listOfAllObjects.begin(); it != _listOfAllObjects.end(); ++it)
	{
		if (it->second->getGroupType() == eGroupTypeObject::ENEMY) it->second->setDestroyed(true);
	}
}

int RObjectManager::getNumberGameObjectDrawn()
{
	return _numberObjectDrawn;
}

int RObjectManager::getNumberGameObjectUpdate()
{
	return _numberObjectUpdate;
}


RObjectManager::RObjectManager()
{
	_indexSimon = -1;
	_grid = new RGrid();
	_needToGetStair = false;
	_numberSpawn = 0;
	_numberObjectDrawn = 0;
	_numberObjectUpdate = 0;
}

RObjectManager::~RObjectManager()
{
	clear();
	delete _grid;
}

void RObjectManager::loadItemObjectsFromXml(TiXmlElement * node)
{
	int index = 0;
	for (TiXmlElement* elem = node->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		if (index == 1121) {
			int a = 0;
		}
		const char *value = elem->Value();
		std::string nodeName = value;
		if (nodeName == "background") {
			processBackgroundItemFromFile(index, _textureBackground, elem);
		}
		if (nodeName == "ground") {
			processGroundItemFromFile(index, elem);
		}
		if (nodeName == "object") {
			processObjectItemFromFile(index, elem);
		}
		index++;
	}
}

void RObjectManager::processBackgroundItemFromFile(int a_index, std::string textureName, TiXmlElement * node)
{
	int x, y, index, zIndex = -1;
	for (TiXmlAttribute* elem = node->FirstAttribute(); elem != NULL; elem = elem->Next())
	{
		std::string name = elem->Name();
		if (name == "x") {
			x = atoi(elem->Value());
			continue;
		}
		if (name == "y") {
			y = atoi(elem->Value());
			continue;
		}
		if (name == "index") {
			index = atoi(elem->Value());
			continue;
		}
		if (name == "zIndex") {
			zIndex = atoi(elem->Value());
			continue;
		}
	}
	if (zIndex == -1) {
		zIndex = 0;
	}
	_listOfAllObjects[a_index] = new RTiledBG(x, y, textureName, _bgInfo, index, zIndex);
	_listOfAllObjects[a_index]->setIndex(a_index);
	if (zIndex > 0) {
		_listOfAllObjects[a_index]->setZIndex(zIndex);
		_deptObject[zIndex].push_back(_listOfAllObjects[a_index]);
	}
	else {
		_listOfAllObjects[a_index]->setZIndex(0);
		_deptObject[0].push_back(_listOfAllObjects[a_index]);
	}
	
}

void RObjectManager::processGroundItemFromFile(int a_index, TiXmlElement * node)
{
	float x, y;
	int cols, rows, type, zIndex = -1;
	for (TiXmlAttribute* elem = node->FirstAttribute(); elem != NULL; elem = elem->Next())
	{
		std::string name = elem->Name();
		if (name == "x") {
			x = (float)atoi(elem->Value());
			continue;
		}
		if (name == "y") {
			y = (float)atoi(elem->Value());
			continue;
		}
		if (name == "type") {
			type = atoi(elem->Value());
			continue;
		}

		if (name == "rows") {
			rows = atoi(elem->Value());
			continue;
		}
		if (name == "cols") {
			cols = atoi(elem->Value());
			continue;
		}
		if (name == "zIndex") {
			zIndex = atoi(elem->Value());
			continue;
		}
	}
	if (zIndex == -1) {
		zIndex = 0;
	}
	switch (type)
	{
	case eTypeObject::GROUND_1:
	case eTypeObject::GROUND_2:
	case eTypeObject::GROUND_3:
		_listOfAllObjects[a_index] = new CBrick(x, y, type, cols, rows);
		break;
	case eTypeObject::STAIR_1:
	case eTypeObject::STAIR_2:
		_listOfAllObjects[a_index] = new CStair(x, y, type, cols, rows);
		break;
	}
	_listOfAllObjects[a_index]->setIndex(a_index);
	_listOfAllObjects[a_index]->setZIndex(zIndex);
	_deptObject[zIndex].push_back(_listOfAllObjects[a_index]);
}

void RObjectManager::processObjectItemFromFile(int a_index, TiXmlElement * node)
{
	int x, y, cols, rows, type, zIndex = -1, leftDirection = 0, other = 0;
	for (TiXmlAttribute* elem = node->FirstAttribute(); elem != NULL; elem = elem->Next())
	{
		std::string name = elem->Name();
		if (name == "x") {
			x = atoi(elem->Value());
			continue;
		}
		if (name == "y") {
			y = atoi(elem->Value());
			continue;
		}
		if (name == "type") {
			type = atoi(elem->Value());
			continue;
		}
		if (name == "left_direction") {
			leftDirection = atoi(elem->Value());
			continue;
		}
		if (name == "zIndex") {
			zIndex = atoi(elem->Value());
			continue;
		}
		if (name == "other") {
			other = atoi(elem->Value());
			continue;
		}
	}
	if (zIndex == -1) {
		zIndex = 0;
	}
	CSimon* simon = NULL;
	switch (type) {
	case eTypeObject::Simon:
		_listOfAllObjects[a_index] = new CSimon(x, y, leftDirection);
		simon = (CSimon*)_listOfAllObjects[a_index];
		simon->SetLeftDirection(leftDirection);
		if (other == SimonState::STEPPING_DOWN) {
			simon->MakeSimonStepDown();
		}
		_listOfAllObjects[a_index]->setIndex(a_index);
		_listOfAllObjects[a_index]->setZIndex(zIndex);
		_deptObject[zIndex].push_back(_listOfAllObjects[a_index]);
		_indexSimon = a_index;
		break;
	case eTypeObject::BigCandleWithLargeHeart:
	case eTypeObject::BigCandleWithUpgradeWhip:
	case eTypeObject::BigCandleWithDagger:
		_listOfAllObjects[a_index] = new CBigCandle(type, x, y);
		_listOfAllObjects[a_index]->setIndex(a_index);
		_listOfAllObjects[a_index]->setZIndex(zIndex);
		_deptObject[zIndex].push_back(_listOfAllObjects[a_index]);
		break;
	case eTypeObject::LittleCandleWithLargeHeart:
	case eTypeObject::LittleCandleStopWatch:
	case eTypeObject::LittleCandleWithAxe:
	case eTypeObject::LittleCandleWithGoldPotion:
	case eTypeObject::LittleCandleWithHolyCross:
	case eTypeObject::LittleCandleWithHolyWater:
	case eTypeObject::LittleCandleWithPurpleMoneyBag:
	case eTypeObject::LittleCandleWithSmallHeart:
	case eTypeObject::LittleCandleWithWhiteMoneyBag:
		_listOfAllObjects[a_index] = new CLittleCandle(type, x, y);
		_listOfAllObjects[a_index]->setIndex(a_index);
		_listOfAllObjects[a_index]->setZIndex(zIndex);
		_deptObject[zIndex].push_back(_listOfAllObjects[a_index]);

		break;
	case eTypeObject::BlueMoneyBag:
		break;
	case eTypeObject::HiddenSwitchScene:
	case eTypeObject::HiddenPassableGate:
	case eTypeObject::HiddenStopCamera:
	case eTypeObject::HiddenStopSimonAfterGate:
	case eTypeObject::HiddenBossBatActive:
	case eTypeObject::HiddenSpawnFishman:
		_listOfAllObjects[a_index] = new CHiddenObject(type, x, y);
		_listOfAllObjects[a_index]->setIndex(a_index);
		_listOfAllObjects[a_index]->setZIndex(zIndex);
		_deptObject[zIndex].push_back(_listOfAllObjects[a_index]);
		break;
	case eTypeObject::EnemyBat:
		_listOfAllObjects[a_index] = new CBat(x, y, leftDirection);
		_listOfAllObjects[a_index]->setIndex(a_index);
		_listOfAllObjects[a_index]->setZIndex(zIndex);
		_deptObject[zIndex].push_back(_listOfAllObjects[a_index]);
		break;
	case eTypeObject::EnemyPanther:
		_listOfAllObjects[a_index] = new CPanther(x, y, leftDirection);
		_listOfAllObjects[a_index]->setIndex(a_index);
		_deptObject[zIndex].push_back(_listOfAllObjects[a_index]);
		_listOfAllObjects[a_index]->setZIndex(zIndex);
		break;
	case eTypeObject::EnemeyGhoul:
		_listOfAllObjects[a_index] = new CGhoul(x, y, leftDirection);
		_listOfAllObjects[a_index]->setIndex(a_index);
		_listOfAllObjects[a_index]->setZIndex(zIndex);
		_deptObject[zIndex].push_back(_listOfAllObjects[a_index]);
		break;
	case eTypeObject::EnemyFishMan:
		_listOfAllObjects[a_index] = new CFishman(x, y, leftDirection);
		_listOfAllObjects[a_index]->setIndex(a_index);
		_listOfAllObjects[a_index]->setZIndex(zIndex);
		_deptObject[zIndex].push_back(_listOfAllObjects[a_index]);
		break;
	case eTypeObject::EnemyMedusa:
		//_listOfAllObjects[a_index] = new CMedusaHead(x, y, leftDirection);
		//_listOfAllObjects[a_index]->setIndex(a_index);
		//_listOfAllObjects[a_index]->setZIndex(zIndex);
		//_deptObject[zIndex].push_back(_listOfAllObjects[a_index]);
		break;
	case eTypeObject::Gate:
		_listOfAllObjects[a_index] = new CGate(x, y);
		_listOfAllObjects[a_index]->setIndex(a_index);
		_listOfAllObjects[a_index]->setZIndex(zIndex);
		_deptObject[zIndex].push_back(_listOfAllObjects[a_index]);
		break;
	case eTypeObject::BossLv1:
		_listOfAllObjects[a_index] = new CBossBat(x, y, leftDirection);
		_listOfAllObjects[a_index]->setIndex(a_index);
		_listOfAllObjects[a_index]->setZIndex(zIndex);
		_deptObject[zIndex].push_back(_listOfAllObjects[a_index]);
		break;
	default:
		break;
	}
}
