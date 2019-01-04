#ifndef __RANIMATION_H__
#define __RANIMATION_H__

#include <d3d9.h>
#include <d3dx9.h>
#include "struct.h"

class RSprite;

class RAnimation {
public:
	RSprite * _sprite;

	AnimationObject _info;

	RAnimation(RSprite *sprite, AnimationObject info);
	RAnimation(RSprite *sprite, int start, int end, int index, int timeAni);

	RAnimation(const RAnimation &animation);

	//sang frame tiếp theo
	void next();

	//trở về frame đầu tiên
	void reset();

	//chọn 1 frame nào đó
	void selectIndex(int index);

	//update animation
	bool update(int ellapseTime);
	bool update(int ellapseTime, bool loop);
	void update(int ellapseTime, int &trach_change);
	bool updateOnceTime(int ellapseTime);
	bool updateOnceTimeFinishWithStart(int ellapseTime, bool &a_changeIndex);
	bool updateOnceTimeCountDown(int ellapseTime, int &a_changeIndex);
	bool updateOnceTimeCountDown(int ellapseTime, bool &a_changeIndex);

	~RAnimation();
};

#endif //!__RANIMATION_H__