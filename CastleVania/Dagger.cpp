#include "Dagger.h"
#include "InfoManager.h"
#include "SoundManager.h"
#include "Utils.h"
#include "Resources.h"

CDagger::CDagger(float a_x, float a_y) : CDynamicObject()
{
	_objectName = "cdagger";
	_boundingBox.position.x = a_x;
	_boundingBox.position.y = a_y;
	loadResource();
	_animations = new RAnimation*[1];
	_animations[0] = new RAnimation(_sprite, 0, 0, 0, 0);
	_boundingBox.height = 18;
	_boundingBox.width = 32;
	_zIndex = 1;
	_type = eTypeObject::Dagger;
	_groupType = eGroupTypeObject::DYNAMIC_ITEM;
}

void CDagger::actionCollidingSimon()
{
	CInfoManager::GetInstance()->SetSpecialWeapon(WeaponEnum::DaggeBullet);
	CSoundManager::GetInstance()->PlaySoundWithIndex(eSoundIndex::COLLECTING_WEAPON);
	_destroyed = true;
}

CDagger::~CDagger()
{
}
