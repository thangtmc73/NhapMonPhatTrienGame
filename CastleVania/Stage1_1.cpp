#include "Stage1_1.h"
#include "Utils.h"
#include "GInputManager.h"
#include "ObjectConfig.h"
#include "GSystem.h"
#include "ObjectManager.h"
#include "StatusBar.h"
#include "InfoManager.h"
#include "Stage1_2.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "BulletManager.h"

Stage1_1::Stage1_1() {	}

void Stage1_1::RenderFrame()
{
	if (_simon->getX() < _camera->GetMaxSize() - 150)
	{
		_bg->drawWithCamera(0, 69, _camera->viewport.x, 0, 515, 320);
		CObjectManager::GetInstance()->drawAllObjectsWithCameraAndGrid(_camera);
		CBulletManager::GetInstance()->drawAllBulletsWithCamera(_camera);
		CEffectManager::GetInstance()->drawAllEffectsWithCamera(_camera);
	}
	else
	{
		_bg->drawWithCamera(0, 69, _camera->viewport.x, 0, 515 - 192, 320);
		CObjectManager::GetInstance()->drawAllObjectsWithCameraAndGrid(_camera);
		CBulletManager::GetInstance()->drawAllBulletsWithCamera(_camera);
		CEffectManager::GetInstance()->drawAllEffectsWithCamera(_camera);
		_bg->drawApartOfTheMap(515 - 192, 69, 42, 47, 0, 8);
	}
	CStatusBar::GetInstance()->draw();
	_simonPosition->draw(DT_LEFT);
}

void Stage1_1::Release()
{
}

void Stage1_1::ProcessInput()
{
	bool left = GInputManager::GetInstance()->IsKeyDown(DIK_LEFT);
	bool right = GInputManager::GetInstance()->IsKeyDown(DIK_RIGHT);
	bool jump = GInputManager::GetInstance()->IsKeyDown(DIK_X);
	bool down = GInputManager::GetInstance()->IsKeyDown(DIK_DOWN);
	bool up = GInputManager::GetInstance()->IsKeyDown(DIK_UP);
	bool attack = GInputManager::GetInstance()->IsKeyDown(DIK_RETURN);

	_simon->GetInputRelatingToSimon(left, right, up, down, jump, attack);
}

void Stage1_1::LoadResources()
{
	_bg = new GTiledBG();
	_bg->GetMapFromFile("Stage1_1BG.txt");
	_bg->LoadImageFromFile("statemapTSLevel1.png");
	_simon = new CSimon(90, 156, true);
	CObjectManager::GetInstance()->AddObject(0, _simon);
	CObjectManager::GetInstance()->GetObjectsFromFile("Stage1_1GO.txt");
	//_objectManager->GetGroundObjectsFromFile("Stage1_1GD.txt");
	_bg->SetArrayDimensions(48, 9);
	_bg->SetTileDimensions(32, 32);
	_bg->SetNumberColumns(13);
	_bg->SetNumberRows(12);
	_bg->SetNumberOfTiles(168);
	_camera = new GCamera();
	_camera->SetSizeMap(1536, 515);
	_camera->viewport.x = 0;
	_camera->_xStartCamera = 0;
	_camera->viewport.y = G_ScreenHeight;
	CObjectManager::GetInstance()->SetInitialGridInfo(1536, G_ScreenHeight, _camera->_minSize, G_ScreenHeight);
	CInfoManager::GetInstance()->StartClock();
	CStatusBar::GetInstance()->SetPosition(GPoint2D(0, 0));
	CSoundManager::GetInstance()->StopSoundWithIndex(eSoundIndex::GAME_START);
	CSoundManager::GetInstance()->LoopSoundWithIndex(eSoundIndex::LEVEL_1);
}

void Stage1_1::update(int a_deltaTime)
{
	CInfoManager::GetInstance()->update(a_deltaTime);
	//CBulletManager::GetInstance()->UpdateAllBullets(a_deltaTime);
	CObjectManager::GetInstance()->CalculateGameObjectInCell();
	CObjectManager::GetInstance()->CheckViewportWithGrid(_camera);
	CObjectManager::GetInstance()->CollideEachOther(a_deltaTime);
	if (!CInfoManager::GetInstance()->IsSwitchingScene())
	{//_quadTree->Clear();
		CObjectManager::GetInstance()->UpdateAllObjects(a_deltaTime);
		CEffectManager::GetInstance()->UpdateAllEffects(a_deltaTime);
		//CObjectManager::GetInstance()->CollideWith(_simon);
		//_simon->update(a_deltaTime);
		CStatusBar::GetInstance()->update(a_deltaTime);
		_camera->UpdateCamera(_simon->getX());
	}
	else
	{
		if (_simon->runToPosition(GPoint2D(1481, 156), a_deltaTime)) {
			GSceneManager::GetInstance()->ReplaceScene(new Stage1_2());

		}
		return;
	}
	_simonPosition->SetString("X: " + ConvertNumberToStringWithTheLength(4, _simon->getBoundingBox().position.x) + " Y: " + ConvertNumberToStringWithTheLength(4, _simon->getBoundingBox().position.y)
	+ " VX: " + std::to_string(_simon->getBoundingBox().vx) + " VY: " + std::to_string(a_deltaTime)+ std::to_string(_simon->getBoundingBox().vy));
}


Stage1_1::~Stage1_1() {
	CObjectManager::GetInstance()->Clear();
}