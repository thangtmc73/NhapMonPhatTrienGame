#include "PurpleMoneyBag.h"
#include "MoneyBag.h"
#include "Resources.h"

CPurpleMoneyBag::CPurpleMoneyBag(float a_x, float a_y) : CMoneyBag(a_x, a_y)
{
	_animations = new RAnimation*[1];
	_animations[0] = new RAnimation(_sprite, 2, 2, 2, 100);
	_bonus = Resources::getInstance()->getIntegerConstWithName("purple-money-bag-points");
}