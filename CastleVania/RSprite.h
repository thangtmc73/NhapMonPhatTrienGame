#ifndef __RSPRITE_H__
#define __RSPRITE_H__

#include <d3d9.h>
#include <d3dx9.h>
#include "Utils.h"
#include "struct.h"

class RTexture;

class RSprite {
private:
	float _anchorPointX;
	float _anchorPointY;
	SpriteSheetInfo _spriteSheetInfo;
	int _index;
public:
	RTexture * _texture;
	RSprite(RTexture *a_texture);
	RSprite(const RSprite &sprite);

	SpriteSheetInfo getSpriteSheetInfo();
	void setSpriteSheetInfo(SpriteSheetInfo);

	// chon 1 frame nao do
	void SelectIndex(int index);

	// Render current sprite at location (X,Y) at the target surface
	void draw(float x, float y);

	//Render with scale (-1, 1)
	void drawFlipX(float x, float y);

	//render with scale (1, -1)
	void drawFlipY(float x, float y);

	//Render Rect of texture at (x,y)
	void drawRect(float X, float Y, RECT SrcRect);

	void drawIndex(int index, float X, float Y);

	int getIndex();
	void setAnchorPoint(float a_anchorPointX, float a_anchorPointY);
	~RSprite();
};

#endif //!__RSPRITE_H__