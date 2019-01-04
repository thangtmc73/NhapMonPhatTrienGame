//#include "Stage5_2.h"
//#include "Utils.h"
//#include "GInputManager.h"
//#include "ObjectConfig.h"
//#include "Simon.h"
//#include "ObjectManager.h"
//#include "StatusBar.h"
//
//Stage5_2::Stage5_2() {}
//
//void Stage5_2::RenderFrame()
//{
//	_bg->drawWithCamera(0, 69, _camera->viewport.x, 0, G_ScreenWidth, G_ScreenHeight);
//	CObjectManager::GetInstance()->drawAllObjectsWithCamera(_camera);
//	_simon->drawWithCamera(_camera);
//
//	CStatusBar::GetInstance()->draw();
//}
//
//void Stage5_2::ProcessInput()
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
//void Stage5_2::LoadResources()
//{
//	_bg = new GTiledBG();
//	_bg->GetMapFromFile("stage5_2BG.txt");
//	_bg->LoadImageFromFile("stage5_2TS.png");
//	CObjectManager::GetInstance()->GetObjectsFromFile("stage5_2GO.txt");
//	_bg->SetArrayDimensions(62, 12);
//	_bg->SetTileDimensions(32, 32);
//	_bg->SetNumberColumns(7);
//	_bg->SetNumberRows(6);
//	_bg->SetNumberOfTiles(36);
//	_simon = new CSimon(90, 180);
//	_camera = new GCamera();
//	_camera->SetSizeMap(1536, G_ScreenWidth);
//	_camera->viewport.x = 894;
//	_camera->viewport.y = G_ScreenHeight;
//}
//
//void Stage5_2::update(int a_deltaTime)
//{
//	CObjectManager::GetInstance()->CollideEachOther();
//	CObjectManager::GetInstance()->UpdateAllObjects(a_deltaTime);
//	_simon->update(a_deltaTime);
//	_camera->UpdateCamera(_simon->GetX());
//}
//
//
//Stage5_2::~Stage5_2(void)
//{}