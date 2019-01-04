#ifndef __BRICK_H__
#define __BRICK_H__

#include "StaticObject.h"
#include "GCamera.h"

class CBrick : public RBaseObject
{
public:
	CBrick(float a_x, float a_y, int a_type, int a_width, int a_height);
	virtual GPoint2D getTopLeftPoint();
	virtual void draw();
	virtual void drawWithCamera(GCamera *a_camera);
private:
	int _numberOfTilesWidth;
	int _numberOfTilesHeight;
	GPoint2D _positionOfFirstGround;
};
#endif //!__BRICK_H__