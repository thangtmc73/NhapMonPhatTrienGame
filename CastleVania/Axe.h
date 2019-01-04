#ifndef __AXE_H__
#define __AXE_H__

#include "DynamicObject.h"

class CAxe : public CDynamicObject
{
public:
	CAxe(float, float);
	~CAxe();
	virtual void afterCollisionWithWeapon(RBaseObject *collided, CollisionInfo info);
private:
};
#endif //!__AXE_H__