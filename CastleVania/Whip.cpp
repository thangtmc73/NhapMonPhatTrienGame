#include "Whip.h"
#include "ObjectConfig.h"
#include "Resources.h"

CWhip::CWhip(float a_x, float a_y) : CWeapon(a_x, a_y)
{
	_boundingBox.position.x = a_x;
	_boundingBox.position.y = a_y;
	_sprite = new RSprite(Resources::getInstance()->getTextureWithName("cwhip"));
	SpriteSheetInfo info;
	info.numCols = 3;
	info.numRows = 3;
	info.numFrames = 9;
	info.frameHeight = 66;
	info.frameWidth = 160;
	_sprite->setSpriteSheetInfo(info);
	_animations = new RAnimation*[3];
	_animations[WhipState::NORMAL_WHIP] = new RAnimation(_sprite, 0, 2, 0, 100);
	_animations[WhipState::UPGRADE_1] = new RAnimation(_sprite, 3, 5, 3, 100);
	_animations[WhipState::UPGRADE_2] = new RAnimation(_sprite, 6, 8, 6, 100);

	_boundingBox.height = 66;
	_boundingBox.width = 85;
	setState(WhipState::NORMAL_WHIP);
	_groupType = eGroupTypeObject::WEAPON_MAIN;
	_type = eTypeObject::WeaponWhip;
}



void CWhip::setState(int a_state)
{
	if (a_state >= TOTAL_WHIP_STATES || a_state < 0)
	{
		return;
	}
	_state = a_state;
	switch (_state)
	{
	case WhipState::NORMAL_WHIP:
		_boundingBox.width = 90;
		_boundingBox.height = 18;
		break;
	case WhipState::UPGRADE_1:
		_boundingBox.width = 120;
		_boundingBox.height = 18;
		break;
	case WhipState::UPGRADE_2:
		_boundingBox.width = 80;
		_boundingBox.height = 18;
		break;
	}
}

int CWhip::getState()
{
	return _state;
}

void CWhip::setIndexFrame(int a_index)
{
	_sprite->SelectIndex(a_index);
}

int CWhip::getIndexFrame()
{
	return _sprite->getIndex();
}

void CWhip::upgrade()
{
	if (_state == WhipState::UPGRADE_2) return;
	if (_state == WhipState::NORMAL_WHIP) setState(WhipState::UPGRADE_1);
	if (_state == WhipState::UPGRADE_1) setState(WhipState::UPGRADE_2);
}
