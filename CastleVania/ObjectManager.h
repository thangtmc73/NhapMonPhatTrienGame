#ifndef __OBJECT_MANAGER_H__
#define __OBJECT_MANAGER_H__

#include <map>
#include <vector>
#include "DynamicObject.h"
#include "StaticObject.h"

class CSimon;
class CGrid;

class CObjectManager
{
public:
	static CObjectManager *GetInstance();
	void AddObject(int a_index, RBaseObject* a_newObject);
	void SetInitialGridInfo(int a_mapWidth, int a_mapHeight, int a_cellWidth, int a_cellHeight);
	void CalculateGameObjectInCell();
	void GetObjectsFromFile(char* a_filePath);
	void GetStaticQuadTreeFromFile(char *a_filePath);
	void drawAllObjects();
	void drawAllObjectsWithCameraAndGrid(GCamera *a_camera);
	void drawAllObjectsWithCamera(GCamera *a_camera);
	void RemoveObjectWithIndex(int);
	void CollidingWith(RBaseObject *a_object);
	void UpdateAllObjects(int a_deltaTime);
	void CollideEachOther(int a_deltaTime);
	void CollideEachOtherInGrid(int a_delta_time);
	void CheckViewportWithGrid(GCamera *a_camera);
	void UpdateGameObjectsInGrid(int a_deltaTime);
	void SetNeedToGetStair(bool a_true);
	void Clear();
	void spawnFishmen(GPoint2D positionSimon, long dt);
	~CObjectManager();
private:
	bool _needToGetStair;
	unsigned int _numberSpawn;
	CObjectManager();
	static CObjectManager *_instance;
	//CQuadTree *_quadTree;
	std::map<int, RBaseObject*> _listOfAllObjects;
	std::vector<int> _listObjectsInGrid;
	CGrid *_grid;
	long _timeSpwan;
	//std::map<int, CStaticObject*> _listOfStaticObjects;
	//std::map<int, CDynamicObject*> _listOfDynamicObjects;
	//std::map<int, CBaseObject*> _listOfGroundObjects;
	//std::vector<int> _listObjectDisplay;

};
#endif //!__OBJECT_MANAGER_H__