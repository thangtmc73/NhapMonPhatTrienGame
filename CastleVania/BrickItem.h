#ifndef __BRICK_ITEM_H__
#define __BRICK_ITEM_H__

#include "StaticObject.h"

class CBrickItem : public CStaticObject
{
public:
	CBrickItem(float, float);
	~CBrickItem();
	virtual void afterCollisionWithWeapon(RBaseObject *collided, CollisionInfo info);
private:
};
#endif //!__BRICK_ITEM_H__