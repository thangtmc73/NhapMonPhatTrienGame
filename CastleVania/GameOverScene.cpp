#include "GameOverScene.h"
#include "GSystem.h"
#include "GInputManager.h"
#include "StatusBar.h"
#include "InfoManager.h"
#include "Stage1_1.h"
#include "Introduction.h"
#include "SceneManager.h"

GameOverScene::GameOverScene() {}

void GameOverScene::RenderFrame()
{
	_title->draw(DT_CENTER);
	_list->draw(DT_LEFT);
	_heart->draw(_chosenFirst.x, _chosenFirst.y + 40 * _chosen);
	CStatusBar::GetInstance()->draw();
}

void GameOverScene::ProcessInput()
{
	_up = GInputManager::GetInstance()->IsKeyDown(DIK_UPARROW);
	_down = GInputManager::GetInstance()->IsKeyDown(DIK_DOWNARROW);
	_enter = GInputManager::GetInstance()->IsKeyDown(DIK_RETURN);
}

void GameOverScene::LoadResources()
{
	_heart = new GTexture("largeheart.png");
	_chosen = 0;

	_up = false;
	_down = false;

	_title = new Text();
	_list = new Text();
	_title->Init(18, 9, 20, false, "Nintendo NES Font");
	_title->SetString("GAME OVER");
	_title->SetTextRect(0, 180, 515, 450);

	_list->Init(18, 9, 20, false, "Nintendo NES Font");
	_list->SetString("CONTINUE\n\nEND");
	_list->SetTextRect(220, 240, 600, 700);
	CInfoManager::GetInstance()->StopClock();
	_chosenFirst.x = 180;
	_chosenFirst.y = 237;
}

void GameOverScene::update(int a_deltaTime)
{
	if (_up ^ _down)
	{
		_chosen = (++_chosen) % 2;
	}
	if (_enter)
	{
		GSceneManager::GetInstance()->ClearScenes();
		if (_chosen = 0)
		{
			GSceneManager::GetInstance()->AddScene(new Stage1_1());
		}
		else
		{
			GSceneManager::GetInstance()->AddScene(new Introduction());
		}
	}
	_up = false;
	_down = false;
}


GameOverScene::~GameOverScene(void){}