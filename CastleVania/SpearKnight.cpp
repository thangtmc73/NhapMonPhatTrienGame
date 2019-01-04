#include "SpearKnight.h"
#include "InfoManager.h"

CSpearKnight::CSpearKnight(int a_x, int a_y, int a_leftDirection) : CEnemy(a_x, a_y, a_leftDirection)
{
	//SPRITE = new GTexture("spearknight.png", 4, 1, 4);
	//_boundingBox.height = SPRITE->FrameHeight = 64;
	//_boundingBox.width = SPRITE->FrameWidth = 32;
	//_sprite->_start = 0;
	//_sprite->_end = 3;
	//_sprite->_index = 0;
	//_sprite->_timeAni = 150;
	//_timesCollidingToDie = 3;
	//_ratioBetweenStrongAndWeakWhip = 1.5;
	//_type = eTypeObject::EnemySpearKnight;
	//_groupType = eGroupTypeObject::ENEMY;
}

void CSpearKnight::AfterCollisionWithSimon(CObjectManager *a_objectManager)
{
}

void CSpearKnight::AfterCollisionWithWeapon(CObjectManager *a_objectManager)
{
	if (_colliding == 1)
	{
		CInfoManager::GetInstance()->ChangeScore(400);
		if (CInfoManager::GetInstance()->getStatusWhip() == 0)
		{
			--_timesCollidingToDie;
		}
		else
		{
			_timesCollidingToDie -= _ratioBetweenStrongAndWeakWhip;
		}
		if (_timesCollidingToDie <= 0)
		{
			_dead = true;
		}
	}
}

CSpearKnight::~CSpearKnight()
{
}
