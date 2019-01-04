#ifndef __MONEY_BAG_H__
#define __MONEY_BAG_H__

#include "DynamicObject.h"

class CMoneyBag : public CDynamicObject
{
public:
	CMoneyBag(float, float);
	virtual void actionCollidingSimon();

	~CMoneyBag();
protected:
	int _bonus;
};
#endif //!__MONEY_BAG_H__