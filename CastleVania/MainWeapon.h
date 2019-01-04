#ifndef __MAIN_WEAPON_H__
#define __MAIN_WEAPON_H__

#include "Weapon.h"

class CMainWeapon : public CWeapon
{
public:
	CMainWeapon(float, float, bool a_leftDirection = true);
	virtual void afterCollision(RBaseObject *collided, CollisionInfo info, int deltaTime);

	virtual void update(int a_deltaTime);
	void draw();
private:
};

#endif // !__MAIN_WEAPON_H__ 