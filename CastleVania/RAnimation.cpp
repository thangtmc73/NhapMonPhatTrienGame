#include "RAnimation.h"
#include "RSprite.h"
#include "Global.h"
#include "Utils.h"

RAnimation::RAnimation(RSprite *sprite, AnimationObject info)
{
	_sprite = sprite;
	_info = info;
}

RAnimation::RAnimation(RSprite * sprite, int start, int end, int index, int timeAni)
{
	_sprite = sprite;
	AnimationObject info;
	info.start = start;
	info.end = end;
	info.index = index;
	info.timeAni = timeAni;
	info.timeLocal = 0;
	_info = info;
}

RAnimation::RAnimation(const RAnimation &sprite)
{
	_sprite = sprite._sprite;
	_info = sprite._info;
}

RAnimation::~RAnimation() { }

void RAnimation::next()
{
	_info.index++;
	if (_info.index > _info.end)
	{
		_info.index = _info.start;
	}
	_sprite->SelectIndex(_info.index);

}

void RAnimation::reset()
{
	_info.index = _info.start;
	_info.timeLocal = 0;
	_sprite->SelectIndex(_info.index);
}

void RAnimation::selectIndex(int index)
{
	_info.index = index;
}

bool RAnimation::update(int ellapseTime)
{
	_info.timeLocal += ellapseTime;

	if (_info.timeLocal >= _info.timeAni)
	{
		_info.timeLocal = 0;
		this->next();
	}
	return false;
}

bool RAnimation::update(int ellapseTime, bool loop) {
	_info.timeLocal += ellapseTime;

	if (_info.timeLocal >= _info.timeAni)
	{
		_info.timeLocal = 0;
		if (loop == false) {
			if (_info.start != _info.end) {
				if (_info.index < _info.end) {
					++_info.index;
					_sprite->SelectIndex(_info.index);
					return false;
				}
				else {
					_info.index = _info.start;
					_sprite->SelectIndex(_info.index);
					return true;
				}
			}
			else {
				_sprite->SelectIndex(_info.index);
			}
		}
		else {
			this->next();
		}
	}

	return false;
}

void RAnimation::update(int ellapseTime, int & trach_change)
{
	_info.timeLocal += ellapseTime;

	if (_info.timeLocal >= _info.timeAni)
	{
		_info.timeLocal = 0;
		this->next();
		trach_change++;
	}
}

bool RAnimation::updateOnceTime(int ellapseTime)
{
	_info.timeLocal += ellapseTime;

	if (_info.timeLocal >= _info.timeAni)
	{
		_info.timeLocal = 0;
		if (_info.index < _info.end)
		{
			_info.index++;
			_sprite->SelectIndex(_info.index);
			return false;
		}
		else
		{
			return true;
		}
	}
	return false;
}

bool RAnimation::updateOnceTimeFinishWithStart(int ellapseTime, bool & a_finished)
{
	_info.timeLocal += ellapseTime;

	if (_info.timeLocal >= _info.timeAni)
	{
		_info.timeLocal = 0;
		if (_info.index < _info.end && !a_finished)
		{
			_info.index++;
			return false;
		}
		else
		{
			_info.index = _info.start;
			a_finished = true;
			return true;
		}
	}
	return false;
}

bool RAnimation::updateOnceTimeCountDown(int ellapseTime, int & a_changeIndex)
{
	_info.timeLocal += ellapseTime;

	if (_info.timeLocal >= _info.timeAni)
	{
		_info.timeLocal = 0;
		if (_info.index > _info.start)
		{
			_info.index--;
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

bool RAnimation::updateOnceTimeCountDown(int ellapseTime, bool & a_changeIndex)
{
	_info.timeLocal += ellapseTime;

	if (_info.timeLocal >= _info.timeAni)
	{
		_info.timeLocal = 0;
		if (_info.index > _info.start)
		{
			_info.index--;
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