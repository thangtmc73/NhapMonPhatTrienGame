#ifndef __HORIZONTAL_MONSTER_H__
#define __HORIZONTAL_MONSTER_H__

#include "DynamicObject.h"

class CHorizontalMonster : public CDynamicObject
{
public:
	CHorizontalMonster(int, int);
	void Draw();
	void Update(int a_delta_time);
	~CHorizontalMonster();
protected:
};
#endif // !__HORIZONTAL_MONSTER_H__