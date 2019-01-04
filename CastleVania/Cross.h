#ifndef __Cross_H__
#define __Cross_H__

#include "DynamicObject.h"

class CCross : public CDynamicObject
{
public:
	CCross(float, float);
	~CCross();
	virtual void afterCollision(RBaseObject *collided, CollisionInfo info, int deltaTime);
private:
};
#endif