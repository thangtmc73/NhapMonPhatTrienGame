#ifndef __RBASEOBJECT_H__
#define __RBASEOBJECT_H__

#include "GCamera.h"
#include "Global.h"
#include "RObject.h"
#include "RAnimation.h"
#include "RObject.h"
#include <set>
//#include "Utils.h"


#define SPRITE _sprite->_texture


class RBaseObject : public RObject
{
protected:
	RAnimation ** _animations;
	int _currentAnimation;
	int _state;
	std::set<RObject *> _listColliding;
	std::set<RObject *> _listOverlapping;
public:
	RBaseObject();
	~RBaseObject();
	virtual bool isCollidingWith(RObject *object);
	virtual void setCollidingWith(RObject *object);
	virtual bool isOverlappingWith(RObject *object);
	virtual void setOverlappingWith(RObject *object);

	void loadResource();
	GRect getBoundingBox();
	virtual GPoint2D getTopLeftPoint();
	GRect getTopLeftBoundingBox();

	virtual void draw();
	virtual void drawWithCamera(GCamera *a_camera);

	virtual void afterCollision(RObject *collided, CollisionInfo info, int deltaTime);

	virtual void processWhenCollidingWithGround(RObject * collided, CollisionInfo info, int deltaTime);

	virtual void actionCollidingSimon();
	virtual void actionCollidingEnemy();
	virtual void afterCollisionWithWeapon(RObject *collided, CollisionInfo info);
	virtual bool isCollindingWith(RBaseObject *a_collided);
	virtual void CollideWith(RBaseObject *a_collided);
	virtual bool isLeftDirection();
	virtual GRect GetFirstBrick();
	virtual GRect GetSecondBrick();
	void runAnimation(int deltatime);
	virtual void update(int a_deltaTime);


	int getState();
	void setState(int status);
};
#endif // !__RBASEOBJECT_H__