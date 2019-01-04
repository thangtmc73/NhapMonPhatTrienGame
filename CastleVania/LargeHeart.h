#ifndef __LARGE_HEART_H__
#define __LARGE_HEART_H__

#include "DynamicObject.h"

class CLargeHeart : public CDynamicObject
{
public:
	CLargeHeart(float, float);
	~CLargeHeart();
	virtual void actionCollidingSimon();

private:
};
#endif //!__LARGE_HEART_H__