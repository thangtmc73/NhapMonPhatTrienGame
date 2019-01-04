#include "SceneMain.h"
#include "Utils.h"

SceneMain::SceneMain(int _nCmdShow): CGame(_nCmdShow)
{}

void SceneMain::RenderFrame()
{
	//_simon->SetX(_simon->GetX() - 1);
	_map->Draw(16, 16);
	_simon->Draw();
	_simon->DrawWhip();
	_ghoul->Draw();
	_spearknight->Draw();
	_panther->Draw();
}


void SceneMain::ProcessInput()
{
	bool left = IsKeyDown(DIK_LEFT);
	bool right = IsKeyDown(DIK_RIGHT);
	bool jump = IsKeyDown(DIK_X);
	bool down = IsKeyDown(DIK_DOWN);
	bool up = IsKeyDown(DIK_UP);
	bool attack = IsKeyDown(DIK_RETURN);

	_simon->UpdateWithState(left, right, up, down, jump, attack);
}

void SceneMain::LoadResources()
{
	_map = new GTiledMap();
	_map->GetMapFromFile("state1map1BG.txt");
	_map->LoadImageFromFile("state1map1TS.png");
	_map->SetArrayDimensions(48, 10);
	_map->SetTileDimensions(32, 32);
	_map->SetNumberColumns(7);
	_map->SetNumberRows(7);
	_map->SetNumberOfTiles(49);
	_simon = new CSimon(90, 260);
	_ghoul = new CGhoul(110, 260);
	_spearknight = new CSpearKnight(140, 260);
	_panther = new CPanther(220, 280);
}

void SceneMain::Update()
{
	_simon->MakeAnimation(_DeltaTime);
	_spearknight->MakeAnimation(_DeltaTime);
	_ghoul->MakeAnimation(_DeltaTime);
	_panther->MakeAnimation(_DeltaTime);
	_spearknight->Update();
	_ghoul->Update();
	_panther->Update();
}


SceneMain::~SceneMain(void)
{
}