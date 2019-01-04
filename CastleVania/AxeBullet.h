#ifndef __AXE_BULLET_H__
#define __AXE_BULLET_H__

#include "Bullet.h"

class CAxeBullet : public CBullet
{
public:
	CAxeBullet(float, float, bool a_leftDirection);
	virtual void update(int a_deltaTime);
	void draw();
private:
};

#endif // !__DAGGER_BULLET_H__ 