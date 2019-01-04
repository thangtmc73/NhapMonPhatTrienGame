#ifndef __DAGGER_H__
#define __DAGGER_H__

#include "DynamicObject.h"

class CDagger : public CDynamicObject
{
public:
	CDagger(float, float);
	virtual void actionCollidingSimon();

	~CDagger();
private:
};
#endif //!__DAGGER_H__