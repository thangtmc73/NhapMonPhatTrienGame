//#include "Stage6_1.h"
//#include "Utils.h"
//#include "GInputManager.h"
//#include "ObjectConfig.h"
//#include "Simon.h"
//#include "ObjectManager.h"
//#include "StatusBar.h"
//
//Stage6_1::Stage6_1() {}
//
//void Stage6_1::RenderFrame()
//{
//	_bg->drawWithCamera(0, 69, _camera->viewport.x, 0, G_ScreenWidth, G_ScreenHeight);
//	CObjectManager::GetInstance()->drawAllObjectsWithCamera(_camera);
//	_simon->drawWithCamera(_camera);
//
//	CStatusBar::GetInstance()->draw();
//}
//
//void Stage6_1::ProcessInput()
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
//void Stage6_1::LoadResources()
//{
//	_bg = new GTiledBG();
//	_bg->GetMapFromFile("stage6_1BG.txt");
//	_bg->LoadImageFromFile("stage6_1TS.png");
//	CObjectManager::GetInstance()->GetObjectsFromFile("stage6_1GO.txt");
//	_bg->SetArrayDimensions(48, 11);
//	_bg->SetTileDimensions(32, 32);
//	_bg->SetNumberColumns(6);
//	_bg->SetNumberRows(6);
//	_bg->SetNumberOfTiles(30);
//	_simon = new CSimon(90, 180);
//	_camera = new GCamera();
//	_camera->SetSizeMap(1536, G_ScreenWidth);
//	_camera->viewport.x = 894;
//	_camera->viewport.y = G_ScreenHeight;
//}
//
//void Stage6_1::update(int a_deltaTime)
//{
//	CObjectManager::GetInstance()->CollideEachOther();
//	CObjectManager::GetInstance()->UpdateAllObjects(a_deltaTime);
//	_simon->update(a_deltaTime);
//	_camera->UpdateCamera(_simon->GetX());
//}
//
//
//Stage6_1::~Stage6_1(void)
//{}