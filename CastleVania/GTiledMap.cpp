#include "GTiledMap.h"
#include "Global.h"

GTiledMap::GTiledMap()
{
	_texture = NULL;
	_array_map = NULL;
	_array_width = 0;
	_array_height = 0;
	_tile_width = 0;
	_tile_height = 0;
}

void GTiledMap::SetArrayDimensions(int a_width, int a_height)
{
	_array_width = a_width;
	_array_height = a_height;
}

void GTiledMap::SetTileDimensions(int a_width, int a_height)
{
	_tile_width = a_width;
	_tile_height = a_height;
}

void GTiledMap::SetNumberOfTiles(int a_number)
{
	_number_tiles = a_number;
}

void GTiledMap::SetNumberColumns(int a_cols)
{
	_number_cols = a_cols;
}

void GTiledMap::SetNumberRows(int a_rows)
{
	_number_rows = a_rows;
}


GTiledMap::~GTiledMap()
{
	if (_texture != NULL)
	{
		_texture->Release();
	}
	if (_array_map != NULL)
	{
		for (int i = 0; i < _array_height; i++)
		{
			delete[] _array_map[i];
			_array_map[i] = NULL;
		}
		delete[] _array_map;
		_array_map = NULL;
	}
}


void GTiledMap::DrawAtIndex(int a_index, int a_x, int a_y)
{
	if (a_index >= _number_tiles || a_index < 0)
	{
		return;
	}
	RECT srect;

	srect.left = (a_index % _number_cols)*(_tile_width);// + 1;
	srect.top = (a_index / _number_cols)*(_tile_height);// + 1;
	srect.right = srect.left + _tile_width;
	srect.bottom = srect.top + _tile_height;// + 1;

	D3DXVECTOR3 position((float)a_x, (float)a_y, 0);
	D3DXVECTOR3 center(0, 0, 0);
	position.x = a_x - _tile_width / 2;
	position.y = a_y - _tile_height / 2;
	G_SpriteHandler->Draw(
		_texture,
		&srect,
		&center,
		&position,
		0xFFFFFFFF //color
	);
}

void GTiledMap::Draw(int a_x, int a_y)
{
	int x, y;
	x = a_x;
	y = a_y;
	for (int i = 0; i < _array_height; i++)
	{
		for (int j = 0; j < _array_width; j++)
		{
			this->DrawAtIndex(_array_map[i][j], x, y);
			x += _tile_width;
		}
		x = a_x;
		y += _tile_height;
	}
}

void GTiledMap::GetMapFromFile(char * a_filePath)
{
	FILE *pFile = fopen(a_filePath, "r");

	if (pFile == NULL)
	{
		printf("Can't open file!");
	}
	fscanf(pFile, "%d %d", &_array_width, &_array_height);
	_array_map = new int*[_array_height];
	for (int i = 0; i < _array_height; i++)
	{
		_array_map[i] = new int[_array_width];
	}
	for (int i = 0; i < _array_height; i++)
	{
		for (int j = 0; j < _array_width; j++)
		{
			fscanf(pFile, "%d", &_array_map[i][j]);
			if (j == _array_width - 1)
			{
				fseek(pFile, 1, SEEK_CUR);
			}
		}
	}
	fclose(pFile);
}

void GTiledMap::LoadImageFromFile(char *a_filePath)
{
	D3DXIMAGE_INFO info;
	HRESULT result;

	result = D3DXGetImageInfoFromFile(a_filePath, &info);

	RECT s = { 0, 0, info.Width, info.Height };

	if (result != D3D_OK)
	{
		GLMessage("Can not load image");
		GLTrace("[gtiledmap.h] Failed to get information from image file [%s]", a_filePath);
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
		GLTrace("[gtiledmap.h] Failed to create texture from file '%s'", a_filePath);
		return;
	}
}
