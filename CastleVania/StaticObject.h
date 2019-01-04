#ifndef __STATIC_OBJECT_H__
#define __STATIC_OBJECT_H__

#include "RBaseObject.h"

class CStaticObject : public RBaseObject
{
public:
	CStaticObject();
	~CStaticObject();
	virtual void update(int a_deltaTime);
protected:
	bool _collidingBefore;
};
#endif //!__STATIC_OBJECT_H__