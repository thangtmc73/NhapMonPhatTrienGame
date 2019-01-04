#include "Stage2_2.h"
#include "Utils.h"
#include "GInputManager.h"
#include "ObjectConfig.h"
#include "Simon.h"
#include "ObjectManager.h"
#include "StatusBar.h"

Stage2_2::Stage2_2() {
	_simonPosition->SetTextRect(0, 430,
		500, 467);
}

void Stage2_2::RenderFrame()
{
	_bg->drawWithCamera(0, 69, _camera->viewport.x, 0, 515, 320);
	CObjectManager::GetInstance()->drawAllObjectsWithCamera(_camera);
	CStatusBar::GetInstance()->draw();
	_simonPosition->draw(DT_LEFT);

}

void Stage2_2::ProcessInput()
{
	bool left = GInputManager::GetInstance()->IsKeyDown(DIK_LEFT);
	bool right = GInputManager::GetInstance()->IsKeyDown(DIK_RIGHT);
	bool jump = GInputManager::GetInstance()->IsKeyDown(DIK_X);
	bool down = GInputManager::GetInstance()->IsKeyDown(DIK_DOWN);
	bool up = GInputManager::GetInstance()->IsKeyDown(DIK_UP);
	bool attack = GInputManager::GetInstance()->IsKeyDown(DIK_RETURN);

	_simon->GetInputRelatingToSimon(left, right, up, down, jump, attack);
}

void Stage2_2::LoadResources()
{
	_bg = new GTiledBG();
	_bg->GetMapFromFile("Stage2_2BG.txt");
	_bg->LoadImageFromFile("statemapTSLevel1.png");
	_simon = new CSimon(112, 427, false);
	_simon->SetLeftDirection(false);
	_simon->MakeSimonStepDown();
	CObjectManager::GetInstance()->AddObject(0, _simon);
	CObjectManager::GetInstance()->SetNeedToGetStair(true);
	CObjectManager::GetInstance()->GetObjectsFromFile("Stage2_2GO.txt");
	//_objectManager->GetGroundObjectsFromFile("Stage2_2GD.txt");
	_bg->SetArrayDimensions(32, 11);
	_bg->SetTileDimensions(32, 32);
	_bg->SetNumberColumns(13);
	_bg->SetNumberRows(12);
	_bg->SetNumberOfTiles(168);
	_camera = new GCamera();
	_camera->SetSizeMap(1024, 515);
	_camera->_xStartCamera = _camera->viewport.x = 0;
	_camera->viewport.y = G_ScreenHeight;
}

void Stage2_2::update(int a_deltaTime)
{
	CObjectManager::GetInstance()->spawnFishmen(GPoint2D(_simon->getX(), _simon->getY()), a_deltaTime);
	CObjectManager::GetInstance()->CollideEachOther(a_deltaTime);
	CObjectManager::GetInstance()->UpdateAllObjects(a_deltaTime);
	//_simon->update(a_deltaTime);
	//_objectManager->CollideWith(_simon);
	_camera->UpdateCamera(_simon->getX());
	_simonPosition->SetString("X: " + ConvertNumberToStringWithTheLength(4, _simon->getBoundingBox().position.x) + " Y: " + ConvertNumberToStringWithTheLength(4, _simon->getBoundingBox().position.y)
		+ " VX: " + std::to_string(_simon->getBoundingBox().vx) + " VY: " + std::to_string(_simon->getBoundingBox().vy));
}


Stage2_2::~Stage2_2(void)
{
	delete _simon;
	delete _bg;
	delete _camera;
	CObjectManager::GetInstance()->Clear();
}