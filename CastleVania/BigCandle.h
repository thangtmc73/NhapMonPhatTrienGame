#ifndef __CANDLE_H__
#define __CANDLE_H__

#include "StaticObject.h"
#include "ObjectManager.h"
#include "LargeHeart.h"

class CBigCandle : public CStaticObject
{
public:
	CBigCandle(int, float, float);
	~CBigCandle();
	virtual void afterCollisionWithWeapon(RObject *collided, CollisionInfo info);
private:
};
#endif //!__CANDLE_H__