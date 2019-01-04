#ifndef __GRID_H__
#define __GRID_H__

#include <vector>

class RBaseObject;
struct GRect;

class CGrid {
public:
	CGrid();
	~CGrid();
	void SetInitialInfo(int a_mapWidth, int a_mapHeight, int a_cellWidth, int a_cellHeight);
	void ClearData();
	void Clear();
	std::vector<int> GetListGameObjectUpdate(GRect rect);
	void Retrieve(RBaseObject *obj, int index);
private:
	int _cellWidth;
	int _gridCols;
	int _indexTopLeftX, _indexTopLeftY, _indexRightBottomX, _indexRightBottomY;
	std::vector<int>* _grid;
	GRect *_gridRect;
};

#endif //!__GRID_H__