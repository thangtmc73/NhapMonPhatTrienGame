#ifndef __SMALL_HEART_H__
#define __SMALL_HEART_H__

#include "DynamicObject.h"

class CSmallHeart : public CDynamicObject
{
public:
	CSmallHeart(float, float);
	~CSmallHeart();
	virtual void update(int a_deltaTime);
	virtual void actionCollidingSimon();

private:
	GPoint2D _startPoint;
	int _time;
};
#endif //!__SMALL_HEART_H__