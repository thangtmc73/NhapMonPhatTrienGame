#include "EffectDestroyedItem.h"

CEffectDestroyedItem::CEffectDestroyedItem(int a_x, int a_y) : CEffect()
{
	_startPoint.x = a_x;
	_startPoint.y = a_y;

	_effect1 = new GSprite();
	_effect2 = new GSprite();

	_effect1->_texture = new GTexture("effect_destroyed_item_1.png", 1, 1, 1);
	_effect1->_texture->FrameWidth = 16;
	_effect1->_texture->FrameHeight = 20;
	_effect1->_start = 0;
	_effect1->_end = 0;
	_effect1->_timeAni = 1500;

	_effect2->_texture = new GTexture("effect_destroyed_item_2.png", 3, 1, 3);
	_effect2->_texture->FrameWidth = 42;
	_effect2->_texture->FrameHeight = 44; 
	_effect1->_start = 0;
	_effect1->_end = 2;
	_effect1->_timeAni = 400;

	_doneEffect1 = false;
}

CEffectDestroyedItem::~CEffectDestroyedItem()
{
	delete _effect1->_texture;
	delete _effect2->_texture;
	delete _effect1;
	delete _effect2;
}

void CEffectDestroyedItem::update(int a_deltaTime)
{
	bool tempt;
	if (_effect1->UpdateOnceTime(a_deltaTime, tempt) || _doneEffect1)
	{
		if (_effect2->UpdateOnceTime(a_deltaTime, tempt))
		{
			_done = true;
		}
		_doneEffect1 = true;
	}
}

void CEffectDestroyedItem::draw()
{
	if (!_doneEffect1)
	{
		_effect1->draw(_startPoint.x, _startPoint.y);
	}
	else
	{
		_effect2->draw(_startPoint.x + 10, _startPoint.y);
	}
}

void CEffectDestroyedItem::drawWithCamera(GCamera * a_camera)
{
	if (a_camera == NULL)
	{
		return;
	}

	int x = _startPoint.x;
	int y = _startPoint.y;
	D3DXVECTOR2 pos = a_camera->Transform(_startPoint.x, _startPoint.y);
	_startPoint.x = pos.x;
	_startPoint.y = pos.y;
	draw();
	_startPoint.x = x;
	_startPoint.y = y;
}
