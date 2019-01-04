#include "PhantomBat.h"
#include "StatusBar.h"

CPhantomBat::CPhantomBat(int a_x, int a_y) : CEnemy(a_x, a_y)
{
	SPRITE = new GTexture("phantombat.png", 4, 1, 4);
	SPRITE->FrameHeight = 32;
	SPRITE->FrameWidth = 32;
	_leftDirection = false;
	_sprite->_start = 0;
	_sprite->_end = 1;
	_sprite->_index = 0;
	_sprite->_timeAni = 100;

}

void CPhantomBat::AfterCollisionWithSimon()
{
}

void CPhantomBat::AfterCollisionWithWeapon()
{
	CStatusBar::GetInstance()->ChangeScore(3000);

}

CPhantomBat::~CPhantomBat()
{
}
