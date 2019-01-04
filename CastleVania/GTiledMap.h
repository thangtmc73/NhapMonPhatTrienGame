#ifndef __TILED_MAP_H__
#define __TILED_MAP_H__
#include "GTexture.h"
class GTiledMap
{
public:
	// the image which consist of all unique tiles
	LPDIRECT3DTEXTURE9 _texture;
private:
	// matrix which is load from file
	int **_array_map;

	// matrix's width and height
	int _array_width, _array_height;

	// tile's width and height
	int _tile_width, _tile_height;

	// number of tiles in the image
	int _number_tiles;

	// number of columns and rows in the image
	int _number_cols, _number_rows;
public:
	GTiledMap();
	
	void SetArrayDimensions(int a_width, int a_height);
	void SetTileDimensions(int a_width, int a_height);
	void SetNumberOfTiles(int a_number);

	void SetNumberColumns(int a_cols);
	void SetNumberRows(int a_rows);

	// get the map matrix from file
	void GetMapFromFile(char * a_filePath);

	// get the image which consist of all unique tiles from file
	void LoadImageFromFile(char *a_filePath);

	// draw the tile with index at (x, y)
	void DrawAtIndex(int a_index, int a_x, int a_y);

	// draw all the map
	void Draw(int a_x, int a_y);

	~GTiledMap();
};
#endif //!__TILED_MAP_H__