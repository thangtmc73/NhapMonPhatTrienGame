#ifndef __STAIR_H__
#define __STAIR_H__

#include "StaticObject.h"
#include "GCamera.h"
#include "Simon.h"

class CStair : public CStaticObject
{
public:
	CStair(float a_x, float a_y, int a_type, int a_left,int a_numberStep);
	virtual void draw();
	virtual void drawWithCamera(GCamera *a_camera);
	virtual void GetRectNearestBetweenSimonAndStair(CDynamicObject *a_simon);
	virtual void actionCollidingSimon();

	virtual GRect GetFirstBrick();
	virtual GRect GetSecondBrick();
	virtual bool isLeftDirection();
private:
	RSprite *_topBrick;
	int _leftDirection;
	int _numberOfBricks;
	GRect _firstBrick;
	GRect _secondBrick;
	RSprite *_brick;
	GPoint2D _startDraw;
};
#endif //!__STAIR_H__