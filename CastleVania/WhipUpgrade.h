#ifndef __WHIP_UPGRADE_H__
#define __WHIP_UPGRADE_H__

#include "DynamicObject.h"

class CWhipUpgrade : public CDynamicObject
{
public:
	CWhipUpgrade(float, float);
	virtual void actionCollidingSimon();

	~CWhipUpgrade();
private:
};
#endif //!__WHIP_UPGRADE_H__