#ifndef __FISHMAN_H__
#define __FISHMAN_H__

#include "Enemy.h"
#include "ObjectConfig.h"
//#include "Ground.h"
//#include "FireBall.h"
//#include "WaterBubble.h"



class CFishman : public CEnemy
{
private:
	//Fishman thoi ra lua
	//CFireBall *_fireball;
	//Bot nuoc
	//CWaterBubble *_waterbubble;
	GPoint2D _positionTopLeftGround;
	bool _passedGroundToStop;
public:
	CFishman(float, float, int);
	bool canStopJumping();
	void setState(int);
	void update(int a_deltaTime);
	virtual void processWhenCollidingWithGround(RObject * collided, CollisionInfo info, int deltaTime);
	~CFishman();
};
#endif // !__FISHMAN_H__
