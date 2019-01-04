#ifndef __GROUND_H__
#define __GROUND_H__

#include "StaticObject.h"
#include "GCamera.h"

class CGround : public CStaticObject
{
public:
	CGround(float a_x, float a_y, int a_type, int a_width);
	virtual void draw();
	virtual void drawWithCamera(int a_x, int a_y, GCamera *a_camera, int a_swidth);
private:
	int _numberOfTiles;
	GPoint2D _positionOfFirstGround;
};
#endif //!__GROUND_H__
