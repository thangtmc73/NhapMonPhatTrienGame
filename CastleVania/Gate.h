#ifndef __GATE_H__
#define __GATE_H__

#include "StaticObject.h"

class CGate : public CStaticObject
{
public:
	CGate(float, float);
	~CGate();
	void update(int a_deltaTime);
	virtual void actionCollidingSimon();

private:
	bool _startAnimation;
	int _collided;
};
#endif //!__GATE_H__