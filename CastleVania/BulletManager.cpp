#include "BulletManager.h"
#include "DaggerBullet.h"
#include "AxeBullet.h"
#include "RObjectManager.h"

CBulletManager* CBulletManager::_instance = NULL;

CBulletManager * CBulletManager::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new CBulletManager();
	}
	return _instance;
}

CBulletManager::CBulletManager()
{
	_currentBulletIndex = 0;
}

void CBulletManager::updateAllBullets(int a_deltaTime)
{	
	for (std::map<RBaseObject*, int>::iterator it = _timeToShoot.begin(); it != _timeToShoot.end(); ++it) {
		it->second += a_deltaTime;
		/*if (it->second > it->first->getTimeBetweenTwoShot()) {
			it->second = it->first->getTimeBetweenTwoShot();
		}*/
	}
}

void CBulletManager::removeBulletOwner(RBaseObject *owner)
{
	_timeToShoot.erase(owner);
}

void CBulletManager::shootBullet(RBaseObject * owner, RBaseObject * bullet)
{
	//if (owner == NULL || owner->getTimeBetweenTwoShot() == -1) {
	//	return;
	//}
	//if (_timeToShoot.find(owner) == _timeToShoot.end() || isCanShoot(owner)) {
	//	_timeToShoot[owner] = 0;
	//	RObjectManager::GetInstance()->addObject(_currentBulletIndex + 5000, bullet);
	//	++_currentBulletIndex;
	//}
}

void CBulletManager::drawAllBulletsWithCamera(GCamera * camera)
{
}

bool CBulletManager::isCanShoot(RBaseObject * owner)
{
	//if (owner == NULL || owner->getTimeBetweenTwoShot() == -1) {
	//	return false;
	//}
	//if (_timeToShoot[owner] >= owner->getTimeBetweenTwoShot()) {
	//	return true;
	//}
	return false;
}

void CBulletManager::Clear()
{
	_timeToShoot.clear();
	_currentBulletIndex = 0;
}