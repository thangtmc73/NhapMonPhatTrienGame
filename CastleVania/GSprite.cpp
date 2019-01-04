#include "GSprite.h"
#include "Global.h"

GSprite::GSprite()
{
	_texture = NULL;
	_start = 0;
	_end = 0;
	_timeAni = 0;
	_index = 0;
	_timeLocal = 0;
	_anchorPointX = 0.5;
	_anchorPointY = 0.5;
}

GSprite::GSprite(const GSprite &sprite)
{
	_texture = sprite._texture;
	_start = sprite._start;
	_end = sprite._end;
	_timeAni = sprite._timeAni;
	_index = sprite._start;
	_timeLocal = sprite._timeLocal;
}

GSprite::GSprite(GTexture* texture, int start, int end, int timeAnimation)
	: _texture(texture)
{
	_start = start;
	_end = end;
	_timeAni = timeAnimation;
	_index = start;
	_timeLocal = 0;
}

GSprite::GSprite(GTexture* texture, int timeAnimation)
	: _texture(texture)
{
	_start = 0;
	_end = _texture->Count - 1;
	_timeAni = timeAnimation;
	_index = 0;
	_timeLocal = 0;
}

GSprite::~GSprite()
{
	if(_texture != NULL)
		delete _texture;
}

void GSprite::Next() 
{
	_index++;
	if (_index > _end)
	{
		_index = _start;
	}
}

void GSprite::Reset()
{
	_index = _start;
	_timeLocal = 0;
}

void GSprite::SelectIndex(int index) 
{
	_index = index;
}

bool GSprite::update(int ellapseTime)
{
	_timeLocal += ellapseTime;

	if(_timeLocal >= _timeAni) 
	{
		_timeLocal = 0;
		this->Next();
	}
	return false;
}

bool GSprite::update(int ellapseTime, bool loop) {
	_timeLocal += ellapseTime;

	if (_timeLocal >= _timeAni)
	{
		_timeLocal = 0;
		if (loop == false) {
			if (_index < _end) {
				++_index;
				return false;
			}
			else {
				_index = _start;
				return true;
			}
		}
		else {
			this->Next();
		}
	}

	return false;
}

void GSprite::update(int ellapseTime, int & trach_change)
{
	_timeLocal += ellapseTime;

	if (_timeLocal >= _timeAni)
	{
		_timeLocal = 0;
		this->Next();
		trach_change++;
	}
}

bool GSprite::UpdateOnceTime(int ellapseTime, bool &a_changeIndex)
{
	_timeLocal += ellapseTime;

	if (_timeLocal >= _timeAni)
	{
		_timeLocal = 0;
		if (_index < _end)
		{
			_index++;
			a_changeIndex = true;
			return false;
		}
		else
		{
			a_changeIndex = false;
			return true;
		}
	}
	a_changeIndex = false;
	return false;
}

bool GSprite::UpdateOnceTimeFinishWithStart(int ellapseTime, bool & a_finished)
{
	_timeLocal += ellapseTime;

	if (_timeLocal >= _timeAni)
	{
		_timeLocal = 0;
		if (_index < _end && !a_finished)
		{
			_index++;
			return false;
		}
		else
		{
			_index = _start;
			a_finished = true;
			return true;
		}
	}
	return false;
}

bool GSprite::UpdateOnceTimeCountDown(int ellapseTime, int & a_changeIndex)
{
	_timeLocal += ellapseTime;

	if (_timeLocal >= _timeAni)
	{
		_timeLocal = 0;
		if (_index > _start)
		{
			_index--;
			a_changeIndex = true;
			return false;
		}
		else
		{
			a_changeIndex = false;
			return true;
		}
	}
	a_changeIndex = false;
	return false;
}

bool GSprite::UpdateOnceTimeCountDown(int ellapseTime, bool & a_changeIndex)
{
	_timeLocal += ellapseTime;

	if (_timeLocal >= _timeAni)
	{
		_timeLocal = 0;
		if (_index > _start)
		{
			_index--;
			a_changeIndex = true;
			return false;
		}
		else
		{
			a_changeIndex = false;
			return true;
		}
	}
	a_changeIndex = false;
	return false;
}

void GSprite::draw(int X, int Y)
{
	RECT srect;

	srect.left = (_index % _texture->Cols)*(_texture->FrameWidth);// + 1;
	srect.top = (_index / _texture->Cols)*(_texture->FrameHeight);// + 1;
	srect.right = srect.left + _texture->FrameWidth;
	srect.bottom = srect.top + _texture->FrameHeight;// + 1;

	//D3DXVECTOR3 position((float)X, (float)Y, 0);
	D3DXVECTOR3 position(0, 0, 0);
	D3DXVECTOR3 center(0, 0, 0);
	position.x = X -_texture->FrameWidth / 2;
	position.y = Y -_texture->FrameHeight / 2;
	G_SpriteHandler->Draw(
		_texture->Texture,
		&srect,
		&center,
		&position,
		0xFFFFFFFF //color
	);
}

void GSprite::drawFlipX(int x, int y)
{
	D3DXMATRIX oldMt;
	G_SpriteHandler->GetTransform(&oldMt);
	
	D3DXMATRIX newMt;
	D3DXVECTOR2 center = D3DXVECTOR2(x + _texture->FrameWidth / 2, y + _texture->FrameHeight / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(-1, 1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt ;
	G_SpriteHandler->SetTransform(&finalMt);

	x += _texture->FrameWidth;
	this->draw(x, y);

	G_SpriteHandler->SetTransform(&oldMt);
}

void GSprite::drawFlipY(int x, int y)
{
	D3DXMATRIX oldMt;
	G_SpriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;
	D3DXVECTOR2 center = D3DXVECTOR2(x + _texture->FrameWidth / 2, y + _texture->FrameHeight / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(1, -1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt ;
	G_SpriteHandler->SetTransform(&finalMt);

	this->draw(x, y);

	G_SpriteHandler->SetTransform(&oldMt);
}

void GSprite::drawRect(int X, int Y, RECT SrcRect)
{
	D3DXVECTOR3 position((float)X, (float)Y, 0);
	G_SpriteHandler->Draw(
		_texture->Texture,
		&SrcRect,
		NULL,
		&position,
		D3DCOLOR_XRGB(255, 255, 255)
		);
}

void GSprite::drawIndex(int index, int X, int Y)
{
	RECT srect;

	srect.left = (index % _texture->Cols)*(_texture->FrameWidth);// + 1;
	srect.top = (index / _texture->Cols)*(_texture->FrameHeight);// + 1;
	srect.right = srect.left + _texture->FrameWidth;
	srect.bottom = srect.top + _texture->FrameHeight;// + 1;

	D3DXVECTOR3 position(0, 0, 0);
	D3DXVECTOR3 center(0, 0, 0);
	position.x = X -_texture->FrameWidth / 2;
	position.y = Y -_texture->FrameHeight / 2;
	G_SpriteHandler->Draw(
		_texture->Texture,
		&srect,
		&center,
		&position,
		0xFFFFFFFF //color
	);
}

int GSprite::GetIndex()
{
	return _index;
}

void GSprite::SetAnchorPoint(float a_anchorPointX, float a_anchorPointY)
{
	if (a_anchorPointX < 0 || a_anchorPointY < 0
		|| a_anchorPointX > 0 || a_anchorPointY > 0)
		return;
}
