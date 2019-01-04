//#include "Stage4_1.h"
//#include "Utils.h"
//#include "GInputManager.h"
//#include "ObjectConfig.h"
//#include "Simon.h"
//#include "ObjectManager.h"
//#include "StatusBar.h"
//
//Stage4_1::Stage4_1() { }
//
//void Stage4_1::RenderFrame()
//{
//	_bg->drawWithCamera(0, 69, _camera->viewport.x, 0, 515, G_ScreenHeight);
//	CObjectManager::GetInstance()->drawAllObjectsWithCamera(_camera);
//	CStatusBar::GetInstance()->draw();
//	_simonPosition->draw(DT_LEFT);
//}
//
//void Stage4_1::ProcessInput()
//{
//	bool left = GInputManager::GetInstance()->IsKeyDown(DIK_LEFT);
//	bool right = GInputManager::GetInstance()->IsKeyDown(DIK_RIGHT);
//	bool jump = GInputManager::GetInstance()->IsKeyDown(DIK_X);
//	bool down = GInputManager::GetInstance()->IsKeyDown(DIK_DOWN);
//	bool up = GInputManager::GetInstance()->IsKeyDown(DIK_UP);
//	bool attack = GInputManager::GetInstance()->IsKeyDown(DIK_RETURN);
//
//	_simon->GetInputRelatingToSimon(left, right, up, down, jump, attack);
//}
//
//void Stage4_1::LoadResources()
//{
//	_bg = new GTiledBG();
//	_bg->GetMapFromFile("stage4_1BG.txt");
//	_bg->LoadImageFromFile("stage4_1TS.png");
//	_simon = new CSimon(90, 125);
//	CObjectManager::GetInstance()->AddObject(0, _simon);
//	CObjectManager::GetInstance()->GetObjectsFromFile("stage4_1GO.txt");
//	_bg->SetArrayDimensions(16, 11);
//	_bg->SetTileDimensions(32, 32);
//	_bg->SetNumberColumns(6);
//	_bg->SetNumberRows(6);
//	_bg->SetNumberOfTiles(33);
//
//	_camera = new GCamera();
//	_camera->SetSizeMap(512, 515);
//	_camera->viewport.x = 0;
//	_camera->viewport.y = G_ScreenHeight;
//	_camera->_xStartCamera = 0;
//	//_quadTree = new GQuadtree();
//}
//
//void Stage4_1::update(int a_deltaTime)
//{
//	CObjectManager::GetInstance()->CollideEachOther();
//	CObjectManager::GetInstance()->UpdateAllObjects(a_deltaTime);
//	_camera->UpdateCamera(_simon->GetX());
//	_simonPosition->SetString("X: " + ConvertNumberToStringWithTheLength(4, _simon->GetBoundingBox().position.x) + " Y: " + ConvertNumberToStringWithTheLength(4, _simon->GetBoundingBox().position.y)
//		+ " VX: " + std::to_string(_simon->GetBoundingBox().vx) + " VY: " + std::to_string(_simon->GetBoundingBox().vy));
//}
//
//
//Stage4_1::~Stage4_1(void)
//{}