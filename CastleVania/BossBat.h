#ifndef __BOSS_BAT_H__
#define __BOSS_BAT_H__

#include "Enemy.h"
struct GPoint2D;
enum eBatPosition {
	BAT_REFRESH = 0,
	BAT_TOP = 1,
	BAT_LEFT = 2,
	BAT_RIGHT = 3,
	BAT_BOTTOM = 4
};
class CBossBat : public CEnemy
{
public:
	CBossBat(float, float, int);
	void update(int dt);
	virtual void afterCollision(RBaseObject * collided, CollisionInfo info, int deltaTime);
	virtual void afterCollisionWithWeapon(RBaseObject * collided, CollisionInfo info);
	void moveToLeftSimon();
	bool outOfBox(GPoint2D point);
	bool checkWhenOutOfTarget();
	void updateNewAction();
	void chooseTarget();
	GPoint2D validatePosition(GPoint2D point);
	~CBossBat();
private:
	void PrepareForAction();
	void refreshTarget();
	bool _doneAttack;
	bool _doneAction;
	GPoint2D _oldPosition;
	GPoint2D _endPosition;
	GPoint2D _leftPosition;
	GPoint2D _rightPosition;
	GPoint2D _topPosition;
	GPoint2D _bottomPosition;
	int _typeAction;
	DWORD _timePercentageStep;
	bool _initialMove;
	int _indexAction;
	bool _refreshTarget;
	int _numberActionsForEach;
	int _time;
};
#endif // !__BOSS_BAT_H__