//#include "Stage4_2.h"
//#include "Utils.h"
//#include "GInputManager.h"
//#include "ObjectConfig.h"
//#include "Simon.h"
//#include "ObjectManager.h"
//#include "StatusBar.h"
//
//Stage4_2::Stage4_2() {}
//
//void Stage4_2::RenderFrame()
//{
//	_bg->drawWithCamera(0, 69, _camera->viewport.x, 0, G_ScreenWidth, G_ScreenHeight);
//	CObjectManager::GetInstance()->drawAllObjectsWithCamera(_camera);
//	_simon->drawWithCamera(_camera);
//
//	CStatusBar::GetInstance()->draw();
//	_simonPosition->draw(DT_LEFT);
//
//}
//
//void Stage4_2::ProcessInput()
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
//void Stage4_2::LoadResources()
//{
//	_bg = new GTiledBG();
//	_bg->GetMapFromFile("stage4_2BG.txt");
//	_bg->LoadImageFromFile("stage4_2TS.png");
//	_simon = new CSimon(1300, 180);
//	CObjectManager::GetInstance()->AddObject(0, _simon);
//
//	CObjectManager::GetInstance()->GetObjectsFromFile("stage4_2GO.txt");
//	_bg->SetArrayDimensions(48, 12);
//	_bg->SetTileDimensions(32, 32);
//	_bg->SetNumberColumns(6);
//	_bg->SetNumberRows(5);
//	_bg->SetNumberOfTiles(27);
//	_camera = new GCamera();
//	_camera->SetSizeMap(1536, G_ScreenWidth);
//	_camera->viewport.x = 1024;
//	_camera->viewport.y = G_ScreenHeight;
//	_camera->_xStartCamera = 0;
//
//}
//
//void Stage4_2::update(int a_deltaTime)
//{
//	CObjectManager::GetInstance()->CollideEachOther();
//	CObjectManager::GetInstance()->UpdateAllObjects(a_deltaTime);
//	_camera->UpdateCamera(_simon->GetX());
//	_simonPosition->SetString("X: " + ConvertNumberToStringWithTheLength(4, _simon->GetBoundingBox().position.x) + " Y: " + ConvertNumberToStringWithTheLength(4, _simon->GetBoundingBox().position.y)
//		+ " VX: " + std::to_string(_simon->GetBoundingBox().vx) + " VY: " + std::to_string(_simon->GetBoundingBox().vy));
//}
//
//
//Stage4_2::~Stage4_2(void)
//{}