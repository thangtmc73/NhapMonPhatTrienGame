#ifndef __ROBJECT_H__
#define __ROBJECT_H__

#include "GCamera.h"
#include "Global.h"
#include "RObject.h"
#include "RAnimation.h"
#include "ObjectConfig.h"
#include "RSprite.h"

class RObject
{
protected:
	bool _destroyed;
	GRect _boundingBox;
	int _zIndex;
	int _index;
	eTypeObject _type;
	RSprite *_sprite;
	eGroupTypeObject _groupType;
	std::string _objectName;
public:
	RObject();
	~RObject();

	bool isDestroyed();
	void setDestroyed(bool);
	eGroupTypeObject getGroupType();

	virtual bool isCollidingWith(RObject *object);
	virtual void setCollidingWith(RObject *object);
	virtual bool isOverlappingWith(RObject *object);
	virtual void setOverlappingWith(RObject *object);

	bool isBackgroundObject();

	bool isStairObject();

	bool isNormalGroundObject();

	eTypeObject getType();
	int getX();
	int getY();

	void setX(int);
	void setY(int);

	float getVX();
	float getVY();

	void setVX(float);
	void setVY(float);

	int getHeight();
	int getWidth();

	int getIndex();
	void setIndex(int index);

	int getZIndex();
	void setZIndex(int index);

	GRect getBoundingBox();
	virtual GPoint2D getTopLeftPoint();
	virtual GRect getTopLeftBoundingBox();

	virtual void draw();
	virtual void drawWithCamera(GCamera *a_camera);

	virtual void afterCollision(RObject *collided, CollisionInfo info, int deltaTime);
	virtual void onOverlapping(RObject *collided);
	virtual void afterCollisionWithWeapon(RObject *collided, CollisionInfo info);
	virtual void CollideWith(RObject *a_collided);
	virtual bool isLeftDirection();
	virtual void update(int a_deltaTime);
};
#endif // !__RBASEOBJECT_H__