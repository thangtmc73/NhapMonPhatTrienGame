#ifndef __TILED_BG_H__
#define __TILED_BG_H__

#include <d3dx9.h>
#include "Utils.h"
#include "RObject.h"

struct SpriteSheetInfo;

class RTiledBG : public RObject
{
public:

private:
	RTiledBG();
public:
	RTiledBG(int x, int y, std::string nameTexture, SpriteSheetInfo info, int a_index, int zIndex = 0);
	void draw();
	~RTiledBG();
};
#endif //!__TILED_BG_H__