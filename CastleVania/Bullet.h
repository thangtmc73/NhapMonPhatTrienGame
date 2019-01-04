#ifndef __BULLET_H__
#define __BULLET_H__

#include "DynamicObject.h"

class CBullet : public CDynamicObject
{
public:
	CBullet(float a_x, float a_y, bool a_leftDirection);
	void draw();
	bool IsDestroyable();
private:
	bool _destroyable;
};

#endif // !__BULLET_H__ 