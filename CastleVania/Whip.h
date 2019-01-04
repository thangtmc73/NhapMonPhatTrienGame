#ifndef __WHIP_H__
#define __WHIP_H__

#include "Weapon.h"

class CWhip : public CWeapon
{
public:
	CWhip(float, float);
	void setState(int a_state);
	int getState();
	void setIndexFrame(int);
	int getIndexFrame();
	void upgrade();
private:
	int _state;
};

#endif // !__WHIP_H__ 