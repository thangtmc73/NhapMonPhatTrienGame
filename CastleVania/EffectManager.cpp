#include "EffectManager.h"
#include "EffectDestroyedItem.h"
#include "EffectWaterSplashed.h"
#include "EffectBrickBroken.h"

CEffectManager* CEffectManager::_instance = NULL;

CEffectManager * CEffectManager::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new CEffectManager();
	}
	return _instance;
}

void CEffectManager::AddEffectDestroyedItem(int a_x, int a_y)
{
	_listOfEffects[_currentIndex++] = new CEffectDestroyedItem(a_x, a_y);
}

void CEffectManager::AddEffectWaterSplashed(int a_x, int a_y)
{
	_listOfEffects[_currentIndex++] = new CEffectWaterSplashed(a_x, a_y);
}

void CEffectManager::AddEffectBrickBroken(int a_x, int a_y)
{
	_listOfEffects[_currentIndex++] = new CEffectBrickBroken(a_x, a_y);

}

void CEffectManager::drawAllEffects()
{
	for (std::map<int, CEffect*>::iterator it = _listOfEffects.begin(); it != _listOfEffects.end(); ++it)
	{
		it->second->draw();
	}
}

void CEffectManager::drawAllEffectsWithCamera(GCamera *a_camera)
{
	if (a_camera == NULL)
	{
		return;
	}
	for (std::map<int, CEffect*>::iterator it = _listOfEffects.begin(); it != _listOfEffects.end(); ++it)
	{
		it->second->drawWithCamera(a_camera);
	}
}

CEffectManager::CEffectManager()
{
	_currentIndex = 0;
}

void CEffectManager::RemoveEffect(int a_index)
{
	_listOfEffects.erase(a_index);
}

void CEffectManager::UpdateAllEffects(float a_deltaTime)
{
	std::map<int, CEffect*>::iterator it_tempt_1;
	for (std::map<int, CEffect*>::iterator it = _listOfEffects.begin(); it != _listOfEffects.end();)
	{
		it_tempt_1 = it++;
		it_tempt_1->second->update(a_deltaTime);
		if (it_tempt_1->second->IsDone())
		{
			_listOfEffects.erase(it_tempt_1->first);
		}
	}
}

void CEffectManager::Clear()
{
	_listOfEffects.clear();
	_currentIndex = 0;
}