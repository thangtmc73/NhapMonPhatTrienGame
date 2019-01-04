//#include "Stage6_2.h"
//#include "Utils.h"
//#include "GInputManager.h"
//#include "ObjectConfig.h"
//#include "Simon.h"
//#include "ObjectManager.h"
//#include "StatusBar.h"
//#define _USE_MATH_DEFINES // for C++  
//#include <cmath>  
//
//Stage6_2::Stage6_2() {
//	_simonPosition->SetTextRect(0, 450,
//		500, 487);
//	_simonPosition->draw(DT_LEFT);
//
//}
//
//void Stage6_2::RenderFrame()
//{
//	_bg->drawWithCamera(0, 69, _camera->viewport.x, 0, G_ScreenWidth, G_ScreenHeight);
//	CObjectManager::GetInstance()->drawAllObjectsWithCamera(_camera);
//	_simon->drawWithCamera(_camera);
//
//	CStatusBar::GetInstance()->draw();
//}
//
//void Stage6_2::ProcessInput()
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
//void Stage6_2::LoadResources()
//{
//	_bg = new GTiledBG();
//	_bg->GetMapFromFile("stage6_2BG.txt");
//	_bg->LoadImageFromFile("stage6_2TS.png");
//	_simon = new CSimon(1400, 225);
//	CObjectManager::GetInstance()->AddObject(0, _simon);
//	CObjectManager::GetInstance()->GetObjectsFromFile("stage6_2GO.txt");
//	_bg->SetArrayDimensions(48, 11);
//	_bg->SetTileDimensions(32, 32);
//	_bg->SetNumberColumns(7);
//	_bg->SetNumberRows(6);
//	_bg->SetNumberOfTiles(36);
//	_camera = new GCamera();
//	_camera->SetSizeMap(1536, G_ScreenWidth);
//	_camera->viewport.x = 1536 - G_ScreenWidth;
//	_camera->_xStartCamera = 0;
//	_camera->viewport.y = G_ScreenHeight;
//}
//
//void Stage6_2::update(int a_deltaTime)
//{
//	float a = sin(0.5 * D3DX_PI);
//	CObjectManager::GetInstance()->CollideEachOther();
//	CObjectManager::GetInstance()->UpdateAllObjects(a_deltaTime);
//	_camera->UpdateCamera(_simon->GetX());
//	_simonPosition->SetString("X: " + ConvertNumberToStringWithTheLength(4, _simon->GetBoundingBox().position.x) + " Y: " + ConvertNumberToStringWithTheLength(4, _simon->GetBoundingBox().position.y)
//		+ " VX: " + std::to_string(_simon->GetBoundingBox().vx) + " VY: " + std::to_string(_simon->GetBoundingBox().vy));
//}
//
//
//Stage6_2::~Stage6_2(void)
//{}