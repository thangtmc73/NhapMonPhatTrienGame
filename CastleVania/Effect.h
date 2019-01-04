#ifndef __EFFECT_H__
#define __EFFECT_H__

#include "GCamera.h"

class CEffect
{
public:
	CEffect();
	virtual void update(int a_deltaTime);
	virtual void draw();
	virtual void drawWithCamera(GCamera *a_camera);
	bool IsDone();
protected:
	bool _done;
};
#endif //!__EFFECT_H__