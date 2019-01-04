#ifndef __RGRID_H__
#define __RGRID_H__

#include <vector>
#include <set>

class RObject;
struct GRect;

class RGrid {
public:
	RGrid();
	~RGrid();
	void setInitialInfo(int a_mapWidth, int a_mapHeight, int a_cellWidth, int a_cellHeight);
	void clearData();
	void clear();
	std::set<RObject*> getListGameObjectUpdate(GRect rect);
	void retrieve(RObject *obj);
	void clearNonBackgroundObject();
private:
	int _cellWidth;
	int _gridCols;
	int _indexTopLeftX, _indexTopLeftY, _indexRightBottomX, _indexRightBottomY;
	std::vector<RObject*>* _grid;
	std::vector<RObject*>* _backgroundObject;
	GRect *_gridRect;
};

#endif //!__GRID_H__