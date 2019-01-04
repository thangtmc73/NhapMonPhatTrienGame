#include "Grid.h"
#include "RBaseObject.h"
#include "Utils.h"

CGrid::CGrid()
{
	_grid = NULL;
}

CGrid::~CGrid()
{
	if (_grid != NULL)
	{
		for (int i = 0; i < _gridCols; i++)
		{
			_grid[i].clear();
		}
		delete[] _gridRect;
		delete[] _grid;
		_grid = NULL;
	}
}

void CGrid::SetInitialInfo(int a_mapWidth, int a_mapHeight, int a_cellWidth, int a_cellHeight)
{
	if (_grid == NULL)
	{
		_cellWidth = a_cellWidth;
		int rowDiv = a_mapHeight % a_cellHeight;
		int colDiv = a_mapWidth % a_cellWidth;
		_gridCols = colDiv == 0 ? (int)(a_mapWidth / a_cellWidth) : (int)((a_mapWidth / a_cellWidth) + 1);
		_grid = new std::vector<int>[_gridCols];
		_gridRect = new GRect[_gridCols];
		for (int i = 0; i < _gridCols; i++)
		{
			_gridRect[i].width = a_cellWidth;
			_gridRect[i].height = a_cellHeight;
			_gridRect[i].position.x = i * a_cellWidth;
			_gridRect[i].position.y = a_cellHeight;
		}
	}
}

void CGrid::ClearData()
{
	for (int i = 0; i < _gridCols; i++)
	{
		_grid[i].clear();
	}
}

void CGrid::Clear()
{
	if (_grid != NULL)
	{
		for (int i = 0; i < _gridCols; i++)
		{
			_grid[i].clear();
		}
		delete[] _gridRect;
		delete[] _grid;
		_grid = NULL;
	}
}

std::vector<int> CGrid::GetListGameObjectUpdate(GRect rect)
{
	int indexTopLeftCol = (int)(rect.position.x / _cellWidth);
	int indexRightBottomCol = (int)((rect.position.x + rect.width) / _cellWidth);
	if (indexRightBottomCol == _gridCols)
	{
		indexRightBottomCol = _gridCols -1 ;
	}
	std::vector<int> listObject;
	for (int i = indexTopLeftCol; i <= indexRightBottomCol; i++)
	{
		for (unsigned int j = 0; j < _grid[i].size(); j++)
		{
			if (std::find(listObject.begin(), listObject.end(), _grid[i].at(j)) == listObject.end())
			{
				listObject.push_back(_grid[i].at(j));
			}
		}
		
	}
	return listObject;
}

void CGrid::Retrieve(RBaseObject * obj, int index)
{
	GRect boundingBox = obj->getBoundingBox();
	boundingBox.position = obj->getTopLeftPoint();
	int indexTopLeftCol = (int)(boundingBox.position.x / _cellWidth);
	int indexRightBottomCol = (int)((boundingBox.position.x + boundingBox.width) / _cellWidth);
	if (indexRightBottomCol == _gridCols)
	{
		indexRightBottomCol = _gridCols - 1;
	}
	for (int i = indexTopLeftCol; i <= indexRightBottomCol; i++)
	{
		_grid[i].push_back(index);
	}
}
