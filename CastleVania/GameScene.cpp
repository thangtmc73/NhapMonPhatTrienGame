#include "GameScene.h"
#include "Simon.h"
#include "Utils.h"

GameScene::GameScene()
{
	_simonPosition = new Text();
	_simonPosition->Init(17, 9, 20, false, "Nintendo NES Font");
	/*_simonPosition->SetString("SCORE-" + ConvertNumberToStringWithTheLength(6, CInfoManager::GetInstance()->GetScore()) + " TIME " + ConvertNumberToStringWithTheLength(4, CInfoManager::GetInstance()->GetClockTime())
		+ " STAGE " + ConvertNumberToStringWithTheLength(2, CInfoManager::GetInstance()->GetStage()));
	_simonPosition->SetTextRect(0, 430,
		500, 467);*/
}

GameScene::~GameScene()
{
	delete _simonPosition;
	delete _bg;
	delete _camera;
	CObjectManager::GetInstance()->Clear();
}

CSimon * GameScene::getSimon()
{
	return _simon;
}
