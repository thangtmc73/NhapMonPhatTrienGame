#include "RTexture.h"
#include "Utils.h"

RTexture::RTexture(std::string a_fileName)
{
	_info.path = a_fileName;
	this->load();
}

TextureObject RTexture::getTextureObject()
{
	return _info;
}

RTexture::RTexture(const RTexture &ctexture)
{
	_info = ctexture._info;
	if (_texture == NULL) {
		this->load();
	}
}

RTexture::~RTexture()
{
	if (this->_texture != NULL)
	{
		this->_texture->Release();
		this->_texture = NULL;
	}
}

void RTexture::draw(int x, int y)
{
	D3DXVECTOR3 position((float)x, (float)y, 0);
	G_SpriteHandler->Draw(_texture, &_info.size, NULL, &position, 0xFFFFFFFF);
}

void RTexture::drawFlipX(int x, int y)
{
	D3DXMATRIX oldMt;
	G_SpriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;
	D3DXVECTOR2 center = D3DXVECTOR2(x + _info.size.right / 2, y + _info.size.bottom / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(-1, 1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;
	G_SpriteHandler->SetTransform(&finalMt);

	//x += FrameWidth;
	this->draw(x, y);

	G_SpriteHandler->SetTransform(&oldMt);
}

LPDIRECT3DTEXTURE9 RTexture::getDirectTexture()
{
	return _texture;
}

void RTexture::load()
{
	D3DXIMAGE_INFO info;
	HRESULT result;

	result = D3DXGetImageInfoFromFile(_info.path.c_str(), &info);

	RECT s = { 0, 0, info.Width, info.Height };
	_info.size = s;

	if (result != D3D_OK)
	{
		GLMessage("Can not load texture");
		GLTrace("[texture.h] Failed to get information from image file [%s]", _info.path.c_str());
		OutputDebugString(_info.path.c_str());
		return;
	}

	result = D3DXCreateTextureFromFileEx(
		G_Device,
		_info.path.c_str(),
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
		GLMessage("Can not load texture");
		GLTrace("[texture.h] Failed to create texture from file '%s'", _info.path);
		return;
	}
}