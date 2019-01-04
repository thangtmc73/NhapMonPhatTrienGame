#include "Stage2_1.h"
#include "Utils.h"
#include "GInputManager.h"
#include "ObjectConfig.h"
#include "Simon.h"
#include "ObjectManager.h"
#include "StatusBar.h"

Stage2_1::Stage2_1() {}

void Stage2_1::RenderFrame()
{
	_bg->drawWithCamera(0, 69, _camera->viewport.x, 0, 515, 320);
	CObjectManager::GetInstance()->drawAllObjectsWithCamera(_camera);
	//_ground->drawWithCamera(16, 106, _camera, 515);
	CStatusBar::GetInstance()->draw();
}

void Stage2_1::ProcessInput()
{
	bool left = GInputManager::GetInstance()->IsKeyDown(DIK_LEFT);
	bool right = GInputManager::GetInstance()->IsKeyDown(DIK_RIGHT);
	bool jump = GInputManager::GetInstance()->IsKeyDown(DIK_X);
	bool down = GInputManager::GetInstance()->IsKeyDown(DIK_DOWN);
	bool up = GInputManager::GetInstance()->IsKeyDown(DIK_UP);
	bool attack = GInputManager::GetInstance()->IsKeyDown(DIK_RETURN);

	_simon->GetInputRelatingToSimon(left, right, up, down, jump, attack);
}

void Stage2_1::LoadResources()
{
	//CObjectManager::GetInstance()->Clear();
	_bg = new GTiledBG();
	_bg->GetMapFromFile("Stage2_1BG.txt");
	_bg->LoadImageFromFile("statemapTSLevel1.png");
	_simon = new CSimon(90, 310, false);
	_simon->SetLeftDirection(false);
	CObjectManager::GetInstance()->AddObject(0, _simon);
	CObjectManager::GetInstance()->GetObjectsFromFile("Stage2_1GO.txt");
	//_objectManager->GetGroundObjectsFromFile("Stage2_1GD.txt");
	_bg->SetArrayDimensions(41, 10);
	_bg->SetTileDimensions(32, 32);
	_bg->SetNumberColumns(13);
	_bg->SetNumberRows(12);
	_bg->SetNumberOfTiles(168);
	_simon = new CSimon(90, 320, true);
	CObjectManager::GetInstance()->AddObject(0, _simon);
	_camera = new GCamera();
	_camera->SetSizeMap(1536, 515);
	_camera->viewport.x = 0;
	_camera->_xStartCamera = 0;
	_camera->viewport.y = G_ScreenHeight;
	//_quadTree = new GQuadtree();
}

void Stage2_1::update(int a_deltaTime)
{
	//_quadTree->Clear();
	CObjectManager::GetInstance()->CollideEachOther(a_deltaTime);
	CObjectManager::GetInstance()->UpdateAllObjects(a_deltaTime);
	//_panther->update(a_deltaTime);
	_camera->UpdateCamera(_simon->getX());
}


Stage2_1::~Stage2_1(void)
{
	delete _simon;
	delete _bg;
	delete _camera;
	CObjectManager::GetInstance()->Clear();
}