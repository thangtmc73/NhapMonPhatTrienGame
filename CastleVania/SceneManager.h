#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include <vector>
#include "GScene.h"

class GSceneManager
{
public:
	~GSceneManager();
	static GSceneManager* GetInstance();

	bool Init();
	void update(int dt);
	void draw();
	void Release();

	void AddScene(GScene* scene);
	void RemoveScene();
	void ReplaceScene(GScene* scene);
	void ClearScenes();
	GScene* GetCurrentScene();

private:
	GSceneManager();
	static GSceneManager* _instance;

	std::vector<GScene*> _scenes;
};

#endif // !__SCENE_MANAGER_H__