#ifndef __EFFECT_BRICK_BROKEN_H__
#define __EFFECT_BRICK_BROKEN_H__

#include "Effect.h"
#include "GSprite.h"
#include "Utils.h"
#include "GCamera.h"

class CEffectBrickBroken : public CEffect
{
private:
	GSprite *_effect1;
	GSprite *_effect2;
	GPoint2D _startPoint;
	bool _doneEffect1;
public:
	CEffectBrickBroken(int a_x, int a_y);
	~CEffectBrickBroken();
	virtual void update(int a_deltaTime);
	virtual void draw();
	virtual void drawWithCamera(GCamera *a_camera);
};

#endif //!__EFFECT_BRICK_BROKEN_H__