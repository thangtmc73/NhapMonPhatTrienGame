#include "Stage1_2.h"
//#include "Utils.h"
#include "GInputManager.h"
#include "BulletManager.h"
#include "StatusBar.h"
#include "ObjectManager.h"
#include "Stage2_1.h"
#include "SceneManager.h"
#include "Simon.h"
#include "GTiledBG.h"
#include "GCamera.h"
#include "Utils.h"

Stage1_2::Stage1_2() { 
	replaceScreen = false;
}

void Stage1_2::RenderFrame()
{
	_bg->drawWithCamera(0, 69, _camera->viewport.x, 0, 515, 320);
	CObjectManager::GetInstance()->drawAllObjectsWithCamera(_camera);
	_simon->drawWithCamera(_camera);
	CStatusBar::GetInstance()->draw();
	_simonPosition->draw(DT_LEFT);

}

void Stage1_2::ProcessInput()
{
	bool left = GInputManager::GetInstance()->IsKeyDown(DIK_LEFT);
	bool right = GInputManager::GetInstance()->IsKeyDown(DIK_RIGHT);
	bool jump = GInputManager::GetInstance()->IsKeyDown(DIK_X);
	bool down = GInputManager::GetInstance()->IsKeyDown(DIK_DOWN);
	bool up = GInputManager::GetInstance()->IsKeyDown(DIK_UP);
	bool attack = GInputManager::GetInstance()->IsKeyDown(DIK_RETURN);

	_simon->GetInputRelatingToSimon(left, right, up, down, jump, attack);
}

void Stage1_2::LoadResources()
{
	CObjectManager::GetInstance()->Clear();
	_bg = new GTiledBG();
	_bg->GetMapFromFile("Stage1_2BG.txt");
	_bg->LoadImageFromFile("statemapTSLevel1.png");
	_simon = new CSimon(2000, 360, true);
	CObjectManager::GetInstance()->AddObject(0, _simon);
	CObjectManager::GetInstance()->GetObjectsFromFile("Stage1_2GO.txt");
	//_objectManager->GetGroundObjectsFromFile("Stage1_2GD.txt");
	_bg->SetArrayDimensions(122, 10);
	_bg->SetTileDimensions(32, 32);
	_bg->SetNumberColumns(13);
	_bg->SetNumberRows(12);
	_bg->SetNumberOfTiles(168);

	_camera = new GCamera();
	//_camera->SetSizeMap(3584, 515);
	_camera->SetSizeMap(3072, 515);
	_camera->_xStartCamera = 0;
	_camera->viewport.x = 0;
	_camera->viewport.y = G_ScreenHeight;
	CObjectManager::GetInstance()->SetInitialGridInfo(3072, G_ScreenHeight, _camera->_minSize, G_ScreenHeight);
	CInfoManager::GetInstance()->SwitchScene(false);
	CInfoManager::GetInstance()->StartClock();
}

void Stage1_2::update(int a_deltaTime)
{
	if (replaceScreen) {
		GSceneManager::GetInstance()->ReplaceScene(new Stage2_1());
		CInfoManager::GetInstance()->resetSwitchScreen();
		return;
	}
	CInfoManager::GetInstance()->update(a_deltaTime);
	CBulletManager::GetInstance()->updateAllBullets(a_deltaTime);
	//CObjectManager::GetInstance()->CalculateGameObjectInCell();
	//CObjectManager::GetInstance()->CheckViewportWithGrid(_camera);

	if (!CInfoManager::GetInstance()->IsMovingThroughGate()) {
		CInfoManager::GetInstance()->SetNewPosition("simon", _simon->getBoundingBox().position);
	}

	if (!CInfoManager::GetInstance()->IsSwitchingScene())
	{
		//CObjectManager::GetInstance()->UpdateGameObjectsInGrid(a_deltaTime);
		CObjectManager::GetInstance()->UpdateAllObjects(a_deltaTime);
		CObjectManager::GetInstance()->CollideEachOther(a_deltaTime);
		CEffectManager::GetInstance()->UpdateAllEffects(a_deltaTime);
	}
	else
	{
		if (CInfoManager::GetInstance()->IsMovingThroughGate()) {
			GPoint2D currentSimonPosition = CInfoManager::GetInstance()->GetCurrentPosition("simon");
			currentSimonPosition.x += 106;
			if (_simon->runToPosition(currentSimonPosition, a_deltaTime)) {
				CInfoManager::GetInstance()->SetMovingThroughGate(false);
				CInfoManager::GetInstance()->SetMoveableCameraBeforeGate(false);
				CInfoManager::GetInstance()->SetMoveableCameraAfterGate(true);
			}
		}
		if (_camera->viewport.x >= CInfoManager::GetInstance()->GetCurrentPosition("gate").x)
		{
			GSceneManager::GetInstance()->ReplaceScene(new Stage1_2());
			CInfoManager::GetInstance()->SwitchScene(false);
			return;

		}
	}
	CStatusBar::GetInstance()->update(a_deltaTime);

	moveCamera();
	//if (!CInfoManager::GetInstance()->IsMoveableCameraBeforeGate() && !CInfoManager::GetInstance()->IsMoveableCameraAfterGate())
	//{
	//	_camera->UpdateCamera(_simon->GetX());
	//}
	//else if (CInfoManager::GetInstance()->IsMoveableCameraBeforeGate())
	//{
	//	_camera->SetSizeMap(3584, 515);
	//	_camera->UpdateCamera(CInfoManager::GetInstance()->GetCurrentPosition("gate").x);
	//}
	//else if (_simon->IsDoneSwitchingScene())
	//{
	//	_camera->UpdateCamera(CInfoManager::GetInstance()->GetCurrentPosition("gate").x);
	//}
	_simonPosition->SetString("X: " + ConvertNumberToStringWithTheLength(4, _simon->getBoundingBox().position.x) + " Y: " + ConvertNumberToStringWithTheLength(4, _simon->getBoundingBox().position.y)
		+ " VX: " + std::to_string(_simon->getBoundingBox().vx) + " VY: " + std::to_string(_simon->getBoundingBox().vy));
}

void Stage1_2::moveCamera()
{
	// luc binh thuong
	if (!CInfoManager::GetInstance()->IsMoveableCameraBeforeGate() && !CInfoManager::GetInstance()->IsMoveableCameraAfterGate())
	{
		_camera->UpdateCamera(_simon->getX());
	} else if (CInfoManager::GetInstance()->IsMoveableCameraBeforeGate())
	{
		// truoc khi di qua cong
		_camera->SetSizeMap(3584, 515);

		// khi cong da o giua camera
		if (_camera->scrollCameraCenterToPositionX(CInfoManager::GetInstance()->GetCurrentPosition("gate").x)) {
			CInfoManager::GetInstance()->setShouldOpenGate(true);
			CInfoManager::GetInstance()->SwitchScene(false);
			CInfoManager::GetInstance()->SetMoveableCameraBeforeGate(false);
			CInfoManager::GetInstance()->SetMoveableCameraAfterGate(false);
		}
	}
	else if (CInfoManager::GetInstance()->IsMoveableCameraAfterGate()) {
		if (_camera->scrollCameraViewportPositionToPositionX(CInfoManager::GetInstance()->GetCurrentPosition("gate").x)) {
			replaceScreen = true;
		}

	}
}


Stage1_2::~Stage1_2() { }