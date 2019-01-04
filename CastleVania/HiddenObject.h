#ifndef __HIDDEN_OBJECT_H__
#define __HIDDEN_OBJECT_H__

#include "StaticObject.h"

class CHiddenObject : public CStaticObject
{
public:
	CHiddenObject(int, float, float);
	~CHiddenObject();
	virtual void actionCollidingSimon();
	void onOverlapping(RObject *collided);

	virtual void draw();
private:
};
#endif //!__HIDDEN_OBJECT_H__