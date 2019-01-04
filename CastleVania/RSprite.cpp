#include "RSprite.h"
#include "Global.h"
#include "RTexture.h"
#include "Log.h"

RSprite::RSprite(RTexture *a_texture)
{
	_texture = a_texture;
	_index = 0;
	_anchorPointX = 0.5;
	_anchorPointY = 0.5;
	_spriteSheetInfo.numCols = 1;
	_spriteSheetInfo.numRows = 1;
	_spriteSheetInfo.numFrames = 1;
}

RSprite::RSprite(const RSprite &sprite)
{
	_texture = sprite._texture;
	_index = 0;
	_anchorPointX = 0.5;
	_anchorPointY = 0.5;
	_spriteSheetInfo = sprite._spriteSheetInfo;
}

SpriteSheetInfo RSprite::getSpriteSheetInfo()
{
	return _spriteSheetInfo;
}

void RSprite::setSpriteSheetInfo(SpriteSheetInfo info)
{
	_spriteSheetInfo = info;
}

RSprite::~RSprite()
{
}

void RSprite::SelectIndex(int index)
{
	_index = index;
}

void RSprite::draw(float X, float Y)
{
	RECT srect;

	srect.left = (_index % _spriteSheetInfo.numCols)*(_spriteSheetInfo.frameWidth);// + 1;
	srect.top = (_index / _spriteSheetInfo.numCols)*(_spriteSheetInfo.frameHeight);// + 1;
	srect.right = srect.left + _spriteSheetInfo.frameWidth;
	srect.bottom = srect.top + _spriteSheetInfo.frameHeight;// + 1;

													 //D3DXVECTOR3 position((float)X, (float)Y, 0);
	D3DXVECTOR3 position(0, 0, 0);
	D3DXVECTOR3 center(0, 0, 0);
	position.x = X - (_spriteSheetInfo.frameWidth / 2);
	position.y = Y - (_spriteSheetInfo.frameHeight / 2);
	G_SpriteHandler->Draw(
		_texture->getDirectTexture(),
		&srect,
		&center,
		&position,
		0xFFFFFFFF //color
	);
}

void RSprite::drawFlipX(float x, float y)
{
	D3DXMATRIX oldMt;
	G_SpriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;
	D3DXVECTOR2 center = D3DXVECTOR2(x + _spriteSheetInfo.frameWidth / 2, y + _spriteSheetInfo.frameHeight / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(-1, 1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;
	G_SpriteHandler->SetTransform(&finalMt);

	x += _spriteSheetInfo.frameWidth;
	this->draw(x, y);

	G_SpriteHandler->SetTransform(&oldMt);
}

void RSprite::drawFlipY(float x, float y)
{
	D3DXMATRIX oldMt;
	G_SpriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;
	D3DXVECTOR2 center = D3DXVECTOR2(x + _spriteSheetInfo.frameWidth / 2, y + _spriteSheetInfo.frameHeight / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(1, -1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;
	G_SpriteHandler->SetTransform(&finalMt);

	this->draw(x, y);

	G_SpriteHandler->SetTransform(&oldMt);
}

void RSprite::drawRect(float X, float Y, RECT SrcRect)
{
	D3DXVECTOR3 position((float)X, (float)Y, 0);
	G_SpriteHandler->Draw(
		_texture->getDirectTexture(),
		&SrcRect,
		NULL,
		&position,
		D3DCOLOR_XRGB(255, 255, 255)
	);
}

void RSprite::drawIndex(int index, float X, float Y)
{
	RECT srect;

	srect.left = (index % _spriteSheetInfo.numCols)*(_spriteSheetInfo.frameWidth);// + 1;
	srect.top = (index / _spriteSheetInfo.numCols)*(_spriteSheetInfo.frameHeight);// + 1;
	srect.right = srect.left + _spriteSheetInfo.frameWidth;
	srect.bottom = srect.top + _spriteSheetInfo.frameHeight;// + 1;

	D3DXVECTOR3 position(0, 0, 0);
	D3DXVECTOR3 center(0, 0, 0);
	position.x = X - _spriteSheetInfo.frameWidth / 2;
	position.y = Y - _spriteSheetInfo.frameHeight / 2;
	G_SpriteHandler->Draw(
		_texture->getDirectTexture(),
		&srect,
		&center,
		&position,
		0xFFFFFFFF //color
	);
}

int RSprite::getIndex()
{
	return _index;
}

void RSprite::setAnchorPoint(float a_anchorPointX, float a_anchorPointY)
{
	if (a_anchorPointX < 0 || a_anchorPointY < 0
		|| a_anchorPointX > 0 || a_anchorPointY > 0)
		return;
}
