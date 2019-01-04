#include "SpecialMoneyBag.h"
#include "MoneyBag.h"
#include "Resources.h"

CSpecialMoneyBag::CSpecialMoneyBag(float a_x, float a_y) : CMoneyBag(a_x, a_y)
{
	_animations = new RAnimation*[1];
	_animations[0] = new RAnimation(_sprite, 0, 2, 2, 100);
	_bonus = Resources::getInstance()->getIntegerConstWithName("special-money-bag-points");
}