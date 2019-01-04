#ifndef __EFFECT_WATER_SPLASHED_H__
#define __EFFECT_WATER_SPLASHED_H__

#include "Effect.h"
#include "GSprite.h"
#include "Utils.h"
#include "GCamera.h"

class CEffectWaterSplashed : public CEffect
{
private:
	GSprite *_effect1;
	GSprite *_effect2;
	GSprite *_effect3;
	GPoint2D _startPoint;
	bool _doneEffect1;
public:
	CEffectWaterSplashed(int a_x, int a_y);
	~CEffectWaterSplashed();
	virtual void update(int a_deltaTime);
	virtual void draw();
	virtual void drawWithCamera(GCamera *a_camera);
};

#endif //!__EFFECT_WATER_SPLASHED_H__