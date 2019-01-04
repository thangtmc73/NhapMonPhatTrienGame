#ifndef __ROBJECT_MANAGER_H__
#define __ROBJECT_MANAGER_H__

#include <map>
#include <vector>
#include <set>
#include "RObject.h"

class CSimon;
class RGrid;
class TiXmlElement;
struct SpriteSheetInfo;

class RObjectManager
{
public:
	static RObjectManager *GetInstance();
	void addObject(int a_index, RObject* a_newObject);
	void setInitialGridInfo(int a_mapWidth, int a_mapHeight, int a_cellWidth, int a_cellHeight);
	void calculateGameObjectInCell();
	void loadObjectsFromFile(const char *a_filePath);
	void drawAllObjects();
	void drawAllObjectsWithCameraAndGrid(GCamera *a_camera);
	void drawAllObjectsWithCamera(GCamera *a_camera);
	void removeObjectWithIndex(int);
	void collidingWith(RObject *a_object, int a_deltaTime);
	void updateAllObjects(float a_deltaTime);
	void collideEachOther(int a_delta_time);
	void collideEachOtherInGrid(int a_delta_time);
	void checkViewportWithGrid(GCamera *a_camera);
	void updateGameObjectsInGrid(float a_deltaTime);
	void setNeedToGetStair(bool a_true);
	void clear();
	void spawnFishmen(GPoint2D positionSimon, float dt);
	CSimon* getSimon();
	void killAllEnemy();

	int getNumberGameObjectDrawn();
	int getNumberGameObjectUpdate();
	~RObjectManager();
private:
	void loadItemObjectsFromXml(TiXmlElement * node);
	void processBackgroundItemFromFile(int index, std::string textureName, TiXmlElement * node);
	void processGroundItemFromFile(int index, TiXmlElement * node);
	void processObjectItemFromFile(int index, TiXmlElement * node);
	std::map<int, std::vector<RObject*>> _deptObject;

	bool _needToGetStair;
	unsigned int _numberSpawn;
	int _numberSpawnEachTime;
	RObjectManager();
	static RObjectManager *_instance;
	std::map<int, RObject*> _listOfAllObjects;
	std::set<RObject*> _listObjectsInGrid;
	RGrid *_grid;
	long _timeSpwan;
	std::string _textureBackground;
	SpriteSheetInfo _bgInfo;
	int _indexSimon;
	int _numberObjectDrawn;
	int _numberObjectUpdate;

};
#endif //!__ROBJECT_MANAGER_H__