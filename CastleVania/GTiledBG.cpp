#include "GTiledBG.h"
#include "Global.h"
#include <d3d9.h>

GTiledBG::GTiledBG()
{
	_texture = NULL;
	_mapArray = NULL;
	_mapArrayWidth = 0;
	_mapArrayHeight = 0;
	_tileWidth = 0;
	_tileHeight = 0;
}

void GTiledBG::SetArrayDimensions(int a_width, int a_height)
{
	_mapArrayWidth = a_width;
	_mapArrayHeight = a_height;
}

void GTiledBG::SetTileDimensions(int a_width, int a_height)
{
	_tileWidth = a_width;
	_tileHeight = a_height;
}

void GTiledBG::SetNumberOfTiles(int a_number)
{
	_numberOfTiles = a_number;
}

void GTiledBG::SetNumberColumns(int a_cols)
{
	_numberOfCols = a_cols;
}

void GTiledBG::SetNumberRows(int a_rows)
{
	_numberOfRows = a_rows;
}


void GTiledBG::drawApartOfTheMap(int a_x, int a_y, int a_index_start_width, int a_index_end_width, int a_index_start_height, int a_index_end_height)
{
	if (a_index_start_width > a_index_end_width || a_index_start_height > a_index_end_height
		|| a_index_start_width >= _mapArrayWidth || a_index_end_width >= _mapArrayWidth
		|| a_index_start_height >= _mapArrayHeight || a_index_end_height >= _mapArrayHeight)
	{
		return;
	}

	int x = a_x;
	int y = a_y;

	for (int i = a_index_start_height; i <= a_index_end_height; i++)
	{
		for (int j = a_index_start_width; j <= a_index_end_width; j++)
		{
			this->drawAtIndex(_mapArray[i][j], x, y);
			x += _tileWidth;
		}
		x = a_x;
		y += _tileHeight;
	}
}

GTiledBG::~GTiledBG()
{
	if (_texture != NULL)
	{
		_texture->Release();
	}
	if (_mapArray != NULL)
	{
		for (int i = 0; i < _mapArrayHeight; i++)
		{
			delete[] _mapArray[i];
			_mapArray[i] = NULL;
		}
		delete[] _mapArray;
		_mapArray = NULL;
	}
}


void GTiledBG::drawAtIndex(int a_index, int a_x, int a_y)
{
	if (a_index >= _numberOfTiles || a_index < 0)
	{
		return;
	}
	RECT srect;

	srect.left = (a_index % _numberOfCols)*(_tileWidth);// + 1;
	srect.top = (a_index / _numberOfCols)*(_tileHeight);// + 1;
	srect.right = srect.left + _tileWidth;
	srect.bottom = srect.top + _tileHeight;// + 1;

	D3DXVECTOR3 position((float)a_x, (float)a_y, 0);
	D3DXVECTOR3 center(0, 0, 0);
	position.x = a_x;// -_tileWidth / 2;
	position.y = a_y; -_tileHeight / 2;
	G_SpriteHandler->Draw(
		_texture,
		&srect,
		&center,
		&position,
		0xFFFFFFFF //color
	);
}

void GTiledBG::drawWithCamera(int a_x, int a_y, int a_sx, int a_sy, int a_swidth, int a_sheight)
{
	int x, y;
	
	int delta_x, delta_y;
	int index_min_width, index_min_height;
	int index_max_width, index_max_height;
	/*if (_mapArrayWidth * _numberOfCols < a_swidth || _mapArrayHeight * _numberOfRows < a_sheight)
	{
		drawAllTheMap(a_x, a_y);
		return;
	}*/
	/*if (a_sx > _mapArrayWidth * _numberOfCols - a_swidth)
	{
		a_sx = _mapArrayWidth * _numberOfCols - a_swidth;
	}
	if (a_sy > _mapArrayHeight * _numberOfRows - a_sheight)
	{
		a_sy = _mapArrayHeight * _numberOfRows - a_sheight;
	}*/
	
	index_min_width = (int) (a_sx / _tileWidth);
	index_min_height = (int) (a_sy / _tileHeight);
	delta_x = a_sx % _tileWidth;
	delta_y = a_sy % _tileHeight;
	index_max_width = (int) (a_swidth / _tileWidth) + index_min_width + 1;
	index_max_height = (int)(a_sheight / _tileHeight) + index_min_height + 1;

	if (index_max_height >= _mapArrayHeight)
	{
		index_max_height = _mapArrayHeight - 1;
	}
	if (index_max_width >= _mapArrayWidth)
	{
		index_max_width = _mapArrayWidth - 1;
	}

	a_x -= delta_x;
	a_y -= delta_y;

	x = a_x;
	y = a_y;

	for (int i = index_min_height; i <= index_max_height; i++)
	{
		for (int j = index_min_width; j <= index_max_width; j++)
		{
			this->drawAtIndex(_mapArray[i][j], x, y);
			x += _tileWidth;
		}
		x = a_x;
		y += _tileHeight;
	}
}

void GTiledBG::drawAllTheMap(int a_x, int a_y)
{
	int x, y;
	x = a_x;
	y = a_y;

	for (int i = 0; i < _mapArrayHeight; i++)
	{
		for (int j = 0; j < _mapArrayWidth; j++)
		{
			this->drawAtIndex(_mapArray[i][j], x, y);
			x += _tileWidth;
		}
		x = a_x;
		y += _tileHeight;
	}
}

void GTiledBG::GetMapFromFile(char * a_filePath)
{
	FILE *pFile = fopen(a_filePath, "r");

	if (pFile == NULL)
	{
		printf("Can't open file!");
	}
	fscanf(pFile, "%d %d", &_mapArrayWidth, &_mapArrayHeight);
	_mapArray = new int*[_mapArrayHeight];
	for (int i = 0; i < _mapArrayHeight; i++)
	{
		_mapArray[i] = new int[_mapArrayWidth];
	}
	for (int i = 0; i < _mapArrayHeight; i++)
	{
		for (int j = 0; j < _mapArrayWidth; j++)
		{
			fscanf(pFile, "%d", &_mapArray[i][j]);
			if (j == _mapArrayWidth - 1)
			{
				fseek(pFile, 1, SEEK_CUR);
			}
		}
	}
	fclose(pFile);
}

void GTiledBG::LoadImageFromFile(char *a_filePath)
{
	D3DXIMAGE_INFO info;
	HRESULT result;

	result = D3DXGetImageInfoFromFile(a_filePath, &info);

	RECT s = { 0, 0, info.Width, info.Height };

	if (result != D3D_OK)
	{
		GLMessage("Can not load image");
		GLTrace("[GTiledBG.h] Failed to get information from image file [%s]", a_filePath);
		OutputDebugString(a_filePath);
		return;
	}

	result = D3DXCreateTextureFromFileEx(
		G_Device,
		a_filePath,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255), //color
		&info,
		NULL,
		&_texture
	);

	if (result != D3D_OK)
	{
		GLMessage("Can not load image");
		GLTrace("[GTiledBG.h] Failed to create texture from file '%s'", a_filePath);
		return;
	}
}
