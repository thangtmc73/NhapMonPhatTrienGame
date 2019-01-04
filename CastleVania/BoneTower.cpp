#include "BoneTower.h"
#include "InfoManager.h"

CBoneTower::CBoneTower(int a_x, int a_y, int a_leftDirection) : CEnemy(a_x, a_y, a_leftDirection)
{
	//SPRITE = new GTexture("bonetower.png", 1, 1, 1);
	//_boundingBox.height = SPRITE->FrameHeight = 64;
	//_boundingBox.width = SPRITE->FrameWidth = 32;
	//_leftDirection = false;
	//_sprite->_start = 0;
	//_sprite->_end = 1;
	//_sprite->_index = 0;
	//_sprite->_timeAni = 100;

}

void CBoneTower::AfterCollisionWithSimon(CObjectManager *a_objectManager)
{
}

void CBoneTower::AfterCollisionWithWeapon(CObjectManager *a_objectManager)
{
	CInfoManager::GetInstance()->ChangeScore(400);
}

CBoneTower::~CBoneTower()
{
}
