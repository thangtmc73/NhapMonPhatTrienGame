#include "ObjectManager.h"
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
#include "Grid.h"
#include "BossBat.h"
#include <algorithm>
#include <vector>

CObjectManager* CObjectManager::_instance = NULL;

CObjectManager * CObjectManager::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new CObjectManager();
	}
	return _instance;
}

void CObjectManager::AddObject(int a_index, RBaseObject * a_newObject)
{
	if (a_newObject == NULL)
	{
		return;
	}
	_listOfAllObjects[a_index] = a_newObject;
	_listOfAllObjects[a_index]->setIndex(a_index);
}

void CObjectManager::SetInitialGridInfo(int a_mapWidth, int a_mapHeight, int a_cellWidth, int a_cellHeight)
{
	_grid->SetInitialInfo(a_mapWidth, a_mapHeight, a_cellWidth, a_cellHeight);
}

void CObjectManager::CalculateGameObjectInCell()
{
	for (std::map<int, RBaseObject*>::iterator it = _listOfAllObjects.begin(); it != _listOfAllObjects.end(); ++it)
	{
		_grid->Retrieve(it->second, it->first);
	}
}

void CObjectManager::GetObjectsFromFile(char * a_filePath)
{
	FILE *pFile = fopen(a_filePath, "r");

	if (pFile == NULL)
	{
		printf("Can't open file!");
	}
	CSimon *simon = (CSimon*)_listOfAllObjects[0];
	GRect simonBox = simon->getTopLeftBoundingBox();

	int index = 1;
	int n_objects, n_grounds, type, x, y, column, row, leftDirection;
	fscanf(pFile, "%d %d", &n_grounds, &n_objects);
	for (int i = 0; i < n_grounds; i++)
	{
		fscanf(pFile, "%d %d %d %d %d", &x, &y, &type, &column, &row);
		switch (type)
		{
		case eTypeObject::GROUND_1:
		case eTypeObject::GROUND_2:
		case eTypeObject::GROUND_3:
			_listOfAllObjects[index] = new CBrick(x, y, type, column, row);
			break;
		case eTypeObject::STAIR_1:
		case eTypeObject::STAIR_2:
			_listOfAllObjects[index] = new CStair(x, y, type, column, row);
			GRect collidedBox = _listOfAllObjects[index]->getTopLeftBoundingBox();
			if (IsAABBCheck(simonBox, collidedBox))
			{
				simon->AfterCollidingWithStair(column);
				simon->SetTwoBricksFromStair(_listOfAllObjects[index]);
			}

			break;
		}
		_listOfAllObjects[index]->setIndex(index);
		++index;
	}

	for (int i = 0; i < n_objects; i++)
	{
		fscanf(pFile, "%d %d %d %d", &type, &x, &y, &leftDirection);
		switch (type)
		{
		case eTypeObject::BigCandleWithLargeHeart:
		case eTypeObject::BigCandleWithUpgradeWhip:
		case eTypeObject::BigCandleWithDagger:
			// _listOfStaticObjects[id] = new CBigCandle(type, x, y);
			// _listOfStaticObjects[id]->SetIndex(id);
			_listOfAllObjects[index] = new CBigCandle(type, x, y);
			_listOfAllObjects[index]->setIndex(index);
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
			// _listOfStaticObjects[id] = new CLittleCandle(type, x, y);
			// _listOfStaticObjects[id]->SetIndex(id);
			_listOfAllObjects[index] = new CLittleCandle(type, x, y);
			_listOfAllObjects[index]->setIndex(index);
			break;
		case eTypeObject::HiddenSwitchScene:
		case eTypeObject::HiddenPassableGate:
			// _listOfStaticObjects[id] = new CHiddenObject(type, x, y);
			// _listOfStaticObjects[id]->SetIndex(id);
			_listOfAllObjects[index] = new CHiddenObject(type, x, y);
			_listOfAllObjects[index]->setIndex(index);
			break;
		case eTypeObject::EnemySpearKnight:
			// _listOfDynamicObjects[id] = new CSpearKnight(x, y);
			// _listOfDynamicObjects[id]->SetIndex(id);
			//_listOfAllObjects[index] = new CSpearKnight(x, y, leftDirection);
			//_listOfAllObjects[index]->setIndex(index);
			break;
		case eTypeObject::EnemyPanther:
			// _listOfDynamicObjects[id] = new CSpearKnight(x, y);
			// _listOfDynamicObjects[id]->SetIndex(id);
			_listOfAllObjects[index] = new CPanther(x, y, leftDirection);
			_listOfAllObjects[index]->setIndex(index);
			break;
		case eTypeObject::EnemeyGhoul:
			// _listOfDynamicObjects[id] = new CGhoul(x, y);
			// _listOfDynamicObjects[id]->SetIndex(id);
			_listOfAllObjects[index] = new CGhoul(x, y, leftDirection);
			_listOfAllObjects[index]->setIndex(index);
			break;
		case eTypeObject::EnemyFishMan:
			_listOfAllObjects[index] = new CFishman(x, y, leftDirection);
			_listOfAllObjects[index]->setIndex(index);
			break;
		case eTypeObject::EnemyMedusa:
			//_listOfAllObjects[index] = new CMedusaHead(x, y, leftDirection);
			//_listOfAllObjects[index]->setIndex(index);
			break;
		case eTypeObject::Gate:
			_listOfAllObjects[index] = new CGate(x, y);
			_listOfAllObjects[index]->setIndex(index);
			break;
		case eTypeObject::BossLv1:
			_listOfAllObjects[index] = new CBossBat(x, y, leftDirection);
			_listOfAllObjects[index]->setIndex(index);
			break;
		default:
			break;
		}
		++index;
	}

	fclose(pFile);
}

void CObjectManager::GetStaticQuadTreeFromFile(char * a_filePath)
{
	//_quadTree->GetFromFile(a_filePath);
}

void CObjectManager::drawAllObjects()
{
	for (std::map<int, RBaseObject*>::iterator it = _listOfAllObjects.begin(); it != _listOfAllObjects.end(); ++it)
	{
		it->second->draw();
	}
}

void CObjectManager::drawAllObjectsWithCameraAndGrid(GCamera * a_camera)
{
	if (a_camera == NULL)
	{
		drawAllObjects();
		return;
	}

	for (auto t = _listObjectsInGrid.begin(); t != _listObjectsInGrid.end(); ++t)
	{
		_listOfAllObjects[*t]->drawWithCamera(a_camera);
	}
}

void CObjectManager::drawAllObjectsWithCamera(GCamera *a_camera)
{
	if (a_camera == NULL)
	{
		drawAllObjects();
		return;
	}

	for (std::map<int, RBaseObject*>::iterator it = _listOfAllObjects.begin(); it != _listOfAllObjects.end(); ++it)
	{
		it->second->drawWithCamera(a_camera);
	}
}

void CObjectManager::RemoveObjectWithIndex(int a_index)
{
	_listOfAllObjects.erase(a_index);
}

void CObjectManager::CollidingWith(RBaseObject *a_object)
{
	eGroupTypeObject groupTypeObject = a_object->getGroupType();
	for (std::map<int, RBaseObject*>::iterator it = _listOfAllObjects.begin(); it != _listOfAllObjects.end(); it++)
	{
		eGroupTypeObject groupTypeOther = it->second->getGroupType();
		if (groupTypeObject == groupTypeOther || a_object->isDestroyed())
		{
			continue;
		}
	}
}

void CObjectManager::UpdateAllObjects(int a_deltaTime)
{
	for (std::map<int, RBaseObject*>::iterator it = _listOfAllObjects.begin(); it != _listOfAllObjects.end();)
	{
		auto k = it++;
		k->second->update(a_deltaTime);
	}
	std::map<int, RBaseObject*>::iterator it = _listOfAllObjects.begin();
	while (it != _listOfAllObjects.end()) {
		// Check if key's first character is F
		if (it->second->isDestroyed()) {
			// erase() function returns the iterator of the next
			// to last deleted element.
			delete it->second;
			it = _listOfAllObjects.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void CObjectManager::CollideEachOther(int deltaTime)
{
	std::map<int, CStaticObject*>::iterator it_tempt;
	bool collidingWithStair = false;
	CSimon *simon = NULL;

	for (std::map<int, RBaseObject*>::iterator colliding = _listOfAllObjects.begin(); colliding != _listOfAllObjects.end(); colliding++)
	{
		eGroupTypeObject collidingType = colliding->second->getGroupType();
		if (collidingType == eGroupTypeObject::GROUND ||
			collidingType == eGroupTypeObject::STATIC_ITEM)
		{
			continue;
		}

		for (std::map<int, RBaseObject*>::iterator collided = _listOfAllObjects.begin(); collided != _listOfAllObjects.end(); collided++)
		{
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
					CollisionInfo collisionWhip = IsCollide(collided->second, simon->GetWhip(), deltaTime);
					if (collisionWhip.collisionTime < 1 || IsAABBCheck(collided->second->getBoundingBox(), simon->GetWhip()->getBoundingBox()))
					{
						collided->second->afterCollisionWithWeapon(colliding->second, collisionWhip);
					}
				}
			}
			if (colliding->second->getType() == eTypeObject::EnemyFishMan && (collided->second->getIndex() == 1))
			{
				int a = 0;
			}
			CollisionInfo collision = IsCollide(colliding->second, collided->second, deltaTime);
			
			if (collision.collisionTime < 1)
			{
				if (colliding->second->getType() == eTypeObject::EnemyFishMan)
				{
					int a = 0;
				}
				colliding->second->afterCollision(collided->second, collision, deltaTime);
				collided->second->afterCollision(colliding->second, collision, deltaTime);
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
					if (collided->second->isStairObject()) {
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

void CObjectManager::CollideEachOtherInGrid(int deltaTime)
{
	std::map<int, CStaticObject*>::iterator it_tempt;

	for (std::vector<int>::iterator colliding = _listObjectsInGrid.begin(); colliding != _listObjectsInGrid.end(); colliding++)
	{
		RBaseObject* collidingObject = _listOfAllObjects[*colliding];
		eGroupTypeObject collidingType = collidingObject->getGroupType();
		if (collidingType == eGroupTypeObject::GROUND ||
			collidingType == eGroupTypeObject::STATIC_ITEM)
		{
			continue;
		}
		if (collidingType == eGroupTypeObject::ENEMY)
		{

		}
		for (std::vector<int>::iterator collided = _listObjectsInGrid.begin(); collided != _listObjectsInGrid.end(); collided++)
		{
			RBaseObject* collidedObject = _listOfAllObjects[*collided];
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
					CollisionInfo collisionWhip = IsCollide(collidedObject, simon->GetWhip(), deltaTime);
					if (collisionWhip.collisionTime < 1 || IsAABBCheck(collidedObject->getBoundingBox(), simon->GetWhip()->getBoundingBox()))
					{
						collidedObject->afterCollisionWithWeapon(collidingObject, collisionWhip);
					}
				}
			}
			CollisionInfo collision = IsCollide(collidingObject, collidedObject, deltaTime);
			if (collision.collisionTime < 1)
			{
				collidingObject->afterCollision(collidedObject, collision, deltaTime);
				collidedObject->afterCollision(collidingObject, collision, deltaTime);
			}
			//colliding->second->
		}
	}
}

void CObjectManager::CheckViewportWithGrid(GCamera * a_camera)
{
	GRect viewport = GRect(a_camera->viewport.x, a_camera->viewport.y, a_camera->_minSize, a_camera->viewport.y, 0, 0);
	_listObjectsInGrid = _grid->GetListGameObjectUpdate(viewport);
}

void CObjectManager::UpdateGameObjectsInGrid(int a_deltaTime)
{

	for (auto t = _listObjectsInGrid.begin(); t != _listObjectsInGrid.end(); ++t)
	{
		_listOfAllObjects[*t]->update(a_deltaTime);
		if (_listOfAllObjects[*t]->isDestroyed())
		{
			delete _listOfAllObjects[*t];
			_listOfAllObjects.erase(*t);
			_listObjectsInGrid.erase(t--);
		}
	}
	for (auto t = _listObjectsInGrid.begin(); t != _listObjectsInGrid.end(); ++t)
	{
		
	}
	_grid->ClearData();
}

void CObjectManager::SetNeedToGetStair(bool a_true)
{
	_needToGetStair = a_true;
}

void CObjectManager::Clear()
{
	for (std::map<int, RBaseObject*>::iterator it = _listOfAllObjects.begin(); it != _listOfAllObjects.end(); it++)
	{
		delete(it->second);
		_listOfAllObjects[it->first] = NULL;
	}
	_listOfAllObjects.clear();
	_grid->Clear();
	_needToGetStair = false;
	_numberSpawn = 0;
}

void CObjectManager::spawnFishmen(GPoint2D positionSimon, long dt)
{
	_timeSpwan += dt;
	if (_timeSpwan > 3000) {
		++_numberSpawn;
		_timeSpwan = 0;
		_listOfAllObjects[_numberSpawn * 1000 + 1] = new CFishman(positionSimon.x - 100, 0, 0);
		_listOfAllObjects[_numberSpawn * 1000 + 2] = new CFishman(positionSimon.x + 100, 0, 1);
	}
}


CObjectManager::CObjectManager()
{
	_grid = new CGrid();
	_needToGetStair = false;
	_numberSpawn = 0;
	//_quadTree = new CQuadTree();
}

CObjectManager::~CObjectManager()
{
	Clear();
	delete _grid;
	//delete _quadTree;
}
