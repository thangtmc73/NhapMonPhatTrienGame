#ifndef __TILED_BG_H__
#define __TILED_BG_H__

#include <d3dx9.h>

class GTiledBG
{
public:
	// the image which consist of all unique tiles
	LPDIRECT3DTEXTURE9 _texture;
private:
	// matrix which is load from file
	int **_mapArray;

	// matrix's width and height
	int _mapArrayWidth, _mapArrayHeight;

	// tile's width and height
	int _tileWidth, _tileHeight;

	// number of tiles in the image
	int _numberOfTiles;

	// number of columns and rows in the image
	int _numberOfCols, _numberOfRows;
public:
	GTiledBG();
	
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
	void drawAtIndex(int a_index, int a_x, int a_y);
	

	// draw the background with camera
	void drawWithCamera(int a_x, int a_y, int a_sx, int a_sy, int a_swidth, int a_sheight);

	// draw all the background
	void drawAllTheMap(int a_x, int a_y);

	// draw apart of the map
	void drawApartOfTheMap(int a_x, int a_y, int a_index_start_width, int a_index_end_width,
							int a_index_start_height, int a_index_end_height);
	~GTiledBG();
};
#endif //!__TILED_BG_H__