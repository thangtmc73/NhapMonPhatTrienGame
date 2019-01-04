#include "Effect.h"

CEffect::CEffect()
{
	_done = false;
}

void CEffect::update(int a_deltaTime)
{
}

void CEffect::draw()
{
}

void CEffect::drawWithCamera(GCamera * a_camera)
{
}

bool CEffect::IsDone()
{
	return _done;
}
