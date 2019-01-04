#ifndef __EFFECT_MANAGER_H__
#define __EFFECT_MANAGER_H__

#include "Effect.h"
#include "GCamera.h"
#include <map>

class CEffectManager
{
public:
	static CEffectManager *GetInstance();
	void AddEffectDestroyedItem(int a_x, int a_y);
	void AddEffectWaterSplashed(int a_x, int a_y);
	void AddEffectBrickBroken(int a_x, int a_y);
	void drawAllEffects();
	void drawAllEffectsWithCamera(GCamera *a_camera);
	void RemoveEffect(int);
	void UpdateAllEffects(float a_deltaTime);
	void Clear();
protected:
	static CEffectManager *_instance;
	int _currentIndex;
	CEffectManager();
	std::map<int, CEffect*> _listOfEffects;
};
#endif //!__EFFECT_MANAGER_H__