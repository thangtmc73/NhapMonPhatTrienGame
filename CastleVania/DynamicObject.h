#ifndef __DYNAMIC_OBJECT_H__
#define __DYNAMIC_OBJECT_H__

#include "RBaseObject.h"
#include "ObjectConfig.h"
#include "Brick.h"

class CDynamicObject : public RBaseObject
{
public:
	CDynamicObject();
	~CDynamicObject();
	virtual void setState(int);
	virtual void draw();
	virtual void update(int a_deltaTime);
	virtual void AfterCollidingWithStair(bool a_leftDirectionStair);
	virtual void SetBrickNearestStair(GRect a_rect);
	void SetLeftDirection(bool a_left = true);
	virtual void SetTwoBricksFromStair(RBaseObject *a_ground);
	void setVxWithLeftDirection(float vx_right);
	virtual bool isLeftDirection();
	int getTimeBetweenTwoShot();
	void updateTimeToShot(int a_deltaTime);
	bool isTimeToShot();
	bool IsDead();
protected:
	bool _dead;
	bool _leftDirection;
	bool _collidingWithAnyGround;
	int _timeBetweenTwoShot;
	int _timeLastShot;
	int _numberShot;
};
#endif //!__DYNAMIC_OBJECT_H__