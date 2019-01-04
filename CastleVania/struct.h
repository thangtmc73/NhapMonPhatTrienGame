#ifndef __STRUCT_H__
#define __STRUCT_H__

#include <d3d9.h>
#include <string>

enum eDirection
{
	NONE = 0,
	TOP = 1,
	BOTTOM = 2,
	LEFT = 4,
	RIGHT = 8,
	ALL = (TOP | BOTTOM | LEFT | RIGHT),
};

struct CollisionInfo {
	eDirection direction;
	float collisionTime;
};

struct TextureObject {
	std::string path;
	RECT size;
};

struct StageObject {
	std::string path_config;
	int mapWidth;
};

struct SpriteSheetInfo {
	unsigned int numRows;
	unsigned int numCols;
	unsigned int numFrames;
	int frameHeight;
	int frameWidth;
};

struct AnimationObject {
	int start;
	int end;
	int index;
	int timeAni;
	int timeLocal;
};

struct ObjectResourceObject {
	std::string textureName;

	SpriteSheetInfo spriteSheet;
	float boundingBoxWidth;
	float boundingBoxHeight;
};
#endif //!__STRUCT_H__