#ifndef __BULLET_MANAGER_H__
#define __BULLET_MANAGER_H__

#include "Bullet.h"
#include <map>

class CBulletManager
{
public:
	static CBulletManager *GetInstance();
	void updateAllBullets(int a_deltaTime);
	void removeBulletOwner(RBaseObject*);
	void shootBullet(RBaseObject* owner, RBaseObject* bullet);
	void drawAllBulletsWithCamera(GCamera *camera);
	bool isCanShoot(RBaseObject* owner);
	void Clear();
protected:
	static CBulletManager *_instance;
	int _currentBulletIndex;
	CBulletManager();
	std::map<RBaseObject*, int> _timeToShoot;
};
#endif //!__BULLET_MANAGER_H__