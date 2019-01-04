#ifndef __LITTLE_CANDLE_H__
#define __LITTLE_CANDLE_H__

#include "StaticObject.h"

class CLittleCandle : public CStaticObject
{
public:
	CLittleCandle(int, float, float);
	~CLittleCandle();
	virtual void afterCollisionWithWeapon(RObject *collided, CollisionInfo info);
private:
};
#endif //!__LITTLE_CANDLE_H__