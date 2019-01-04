#include "SceneManager.h"

GSceneManager* GSceneManager::_instance = nullptr;

GSceneManager::~GSceneManager()
{
}

GSceneManager::GSceneManager()
{
}

GSceneManager * GSceneManager::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new GSceneManager();
	}

	return _instance;
}

bool GSceneManager::Init()
{
	if (!_scenes.empty())
	{
		_scenes.back()->Init();
	}
	return true;
}

void GSceneManager::update(int dt)
{
	if (!_scenes.empty())
	{
		_scenes.back()->update(dt);
	}
}

void GSceneManager::draw()
{
	/*if (!_scenes.empty())
		_scenes.back()->draw();*/
}

void GSceneManager::Release()
{
	if (!_scenes.empty())
	{
		_scenes.back()->Release();
		if (_scenes.back())
		{
			delete _scenes.back();
			_scenes.back() = NULL;
		}
	}
}

void GSceneManager::AddScene(GScene * scene)
{
	_scenes.push_back(scene);
	_scenes.back()->Init();
}

void GSceneManager::RemoveScene()
{
	if (!_scenes.empty())
	{
		_scenes.back()->Release();
		delete _scenes.back();
		_scenes.pop_back();
	}
}

void GSceneManager::ReplaceScene(GScene * scene)
{
	this->RemoveScene();
	this->AddScene(scene);
}

void GSceneManager::ClearScenes()
{
	while (!_scenes.empty())
	{
		_scenes.back()->Release();
		delete _scenes.back();
		_scenes.pop_back();
	}
}

GScene * GSceneManager::GetCurrentScene()
{
	if (!_scenes.empty())
		return _scenes.back();

	return nullptr;
}