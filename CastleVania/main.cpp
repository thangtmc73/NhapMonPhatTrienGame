#include <windows.h>
#include "GSystem.h"
#include "Introduction.h"
#include "StartGame.h"
#include "SceneManager.h"
#include "Stage1_1.h"
#include "RGameScene.h"
#include "Resources.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/*SceneMain *game = new SceneMain(nCmdShow);
	game->InitGame();
	game->GameRun();
	game->GameEnd();*/
	srand(time(NULL));
	Resources::getInstance()->loadResourceFromFile("game_config.xml");

	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, 0);
	GSystem::GetInstance()->Set_nCmdShow(nCmdShow);
	GSystem::GetInstance()->Init();
	GSceneManager::GetInstance()->AddScene(new RGameScene());
	GSystem::GetInstance()->Run();
	GSystem::GetInstance()->Release();
	return 0;
}