#include "WhiteMoneyBag.h"
#include "DynamicObject.h"
#include "Resources.h"

CWhiteMoneyBag::CWhiteMoneyBag(float a_x, float a_y) : CMoneyBag(a_x, a_y)
{
	_animations = new RAnimation*[1];
	_animations[0] = new RAnimation(_sprite, 1, 1, 1, 100);
	_bonus = Resources::getInstance()->getIntegerConstWithName("white-money-bag-points");
}
