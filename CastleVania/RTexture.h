#ifndef __RTEXTURE_H__
#define __RTEXTURE_H__

#include <d3d9.h>
#include <d3dx9.h>
#include "Global.h"
#include "Utils.h"

class RTexture
{
public:

	TextureObject getTextureObject();

	RTexture(const RTexture &ctexture);
	RTexture(std::string _fileName);
	~RTexture();
	void draw(int x, int y);
	void drawFlipX(int x, int y);
	LPDIRECT3DTEXTURE9 getDirectTexture();
protected:
	void load();
private:
	TextureObject _info;
	LPDIRECT3DTEXTURE9 _texture;
};

#endif