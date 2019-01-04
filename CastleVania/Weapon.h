#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "RBaseObject.h"

class CWeapon : public RBaseObject
{
public:
	CWeapon();
	CWeapon(float, float);
	void draw();

	void SetLeft(bool a_left);

	virtual void update(int a_deltaTime);
	~CWeapon();
protected:
	bool _leftDirection;
};
#endif // !__WEAPON_H__