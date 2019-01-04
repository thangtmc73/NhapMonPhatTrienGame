#include "RGameScene.h"
#include "Utils.h"
#include "GInputManager.h"
#include "ObjectConfig.h"
#include "GSystem.h"
#include "RObjectManager.h"
#include "StatusBar.h"
#include "InfoManager.h"
#include "Stage1_2.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "BulletManager.h"
#include "TinyXML/tinyxml.h"
#include "Resources.h"

RGameScene::RGameScene()
{
	_indexNextStage = 0;
	CStatusBar::GetInstance()->SetPosition(GPoint2D(0, 0));
	_simon = NULL;
	_camera = new GCamera();
	_camera->viewport.x = 0;
	_camera->_xStartCamera = 0;
	loadConfigFile();
	nextStage();
	_text = new Text();
	_text->Init(14, 7, 20, false, "Nintendo NES Font");
	_text->SetTextRect(0, 450, 500, 467);
	//_simonPosition = new Text();
	//_simonPosition->Init(17, 9, 20, false, "Nintendo NES Font");
	//_simonPosition->SetString("SCORE-" + ConvertNumberToStringWithTheLength(6, CInfoManager::GetInstance()->GetScore()) + " TIME " + ConvertNumberToStringWithTheLength(4, CInfoManager::GetInstance()->GetClockTime())
	//	+ " STAGE " + ConvertNumberToStringWithTheLength(2, CInfoManager::GetInstance()->GetStage()));
	//_simonPosition->SetTextRect(0, 430,
	//	500, 467);
}

void RGameScene::update(int a_delta_time) {
	RObjectManager::GetInstance()->checkViewportWithGrid(_camera);
	CStatusBar::GetInstance()->update(a_delta_time);
	if (CInfoManager::GetInstance()->IsSwitchingScene()) {
		nextStage();
	}

	CInfoManager::GetInstance()->SetNewPosition("simon", _simon->getBoundingBox().position);

	
	if (CInfoManager::GetInstance()->IsMoveableCameraBeforeGate())
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
		_simon->setVX(0);
		_simon->setState(SimonState::STAY);
		if (_camera->scrollCameraViewportPositionToPositionX(CInfoManager::GetInstance()->GetCurrentPosition("gate").x)) {
			CInfoManager::GetInstance()->SetMovingThroughGate(false);
			CInfoManager::GetInstance()->SetMoveableCameraAfterGate(false);
			CInfoManager::GetInstance()->setStopCamera(false);
			CInfoManager::GetInstance()->SwitchScene(true);
		}
	}
	else {
		if (CInfoManager::GetInstance()->IsMovingThroughGate()) {
			_simon->Run();
		}
		if (_simon != NULL) {
			_camera->UpdateCamera(_simon->getX());
			_text->SetString("Objects drawn: " + std::to_string(RObjectManager::GetInstance()->getNumberGameObjectDrawn())
				+ " Objects updated: " + std::to_string(RObjectManager::GetInstance()->getNumberGameObjectUpdate())
				+ " Simon(" + std::to_string(_simon->getX()) + ", "
				+ std::to_string(_simon->getY()) + ") deltaTime " + std::to_string(a_delta_time));
		}
	}
	CBulletManager::GetInstance()->updateAllBullets(a_delta_time);
	//RObjectManager::GetInstance()->collideEachOther(a_delta_time);

	RObjectManager::GetInstance()->updateGameObjectsInGrid(a_delta_time);

}

void RGameScene::ProcessInput()
{
	if (_simon != NULL) {
		bool left = GInputManager::GetInstance()->IsKeyDown(DIK_LEFT);
		bool right = GInputManager::GetInstance()->IsKeyDown(DIK_RIGHT);
		bool jump = GInputManager::GetInstance()->IsKeyDown(DIK_X);
		bool down = GInputManager::GetInstance()->IsKeyDown(DIK_DOWN);
		bool up = GInputManager::GetInstance()->IsKeyDown(DIK_UP);
		bool attack = GInputManager::GetInstance()->IsKeyDown(DIK_RETURN);

		_simon->GetInputRelatingToSimon(left, right, up, down, jump, attack);
	}

}

RGameScene::~RGameScene()
{
	delete _camera;
	RObjectManager::GetInstance()->clear();
}

CSimon * RGameScene::getSimon()
{
	return _simon;
}

void RGameScene::LoadResources()
{
	//RObjectManager::GetInstance()->loadObjectsFromFile("Stage1_1.xml");
	_camera->viewport.x = 0;
	_camera->_xStartCamera = 0;
	_camera->viewport.y = Resources::getInstance()->getIntegerConstWithName("window-height");
}

void RGameScene::loadConfigFile()
{
	TiXmlDocument doc("scene_config.xml");
	bool success = doc.LoadFile();
	if (success)
	{
		//TiXmlElement* root = doc.FirstChildElement();
		TiXmlElement* root = doc.RootElement();
		for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
		{
			const char *value = elem->Value();
			std::string nodeName = value;
			if (nodeName == "stage") {
				StageObject stage;
				for (TiXmlAttribute* attribute = elem->FirstAttribute(); attribute != NULL; attribute = attribute->Next())
				{
					std::string name = attribute->Name();
					if (name == "path_config") {
						stage.path_config = attribute->Value();
						continue;
					}
					if (name == "mapWidth") {
						stage.mapWidth = atoi(attribute->Value());
						continue;
					}
				}
				_listStageInfos.push_back(stage);
			}
		}
	}
	else
	{
		doc.ErrorDesc();
		return;
	}
}

void RGameScene::nextStage()
{
	if (_indexNextStage < _listStageInfos.size()) {
		RObjectManager::GetInstance()->clear();
		RObjectManager::GetInstance()->loadObjectsFromFile(_listStageInfos.at(_indexNextStage).path_config.c_str());
		
		int mapWidth, mapHeight, screenWidth, screenHeight;
		mapWidth = _listStageInfos.at(_indexNextStage).mapWidth;
		screenWidth = Resources::getInstance()->getIntegerConstWithName("window-width");
		mapHeight = screenHeight = Resources::getInstance()->getIntegerConstWithName("window-height");

		RObjectManager::GetInstance()->setInitialGridInfo(mapWidth, mapHeight, screenWidth, screenHeight);
		RObjectManager::GetInstance()->calculateGameObjectInCell();

		CInfoManager::GetInstance()->SwitchScene(false);
		_simon = RObjectManager::GetInstance()->getSimon();
		_camera->SetSizeMap(mapWidth, screenWidth);
		_camera->viewport.x = 0;
		_camera->_xStartCamera = 0;
		_camera->viewport.y = screenHeight;
		++_indexNextStage;

	}
}

void RGameScene::RenderFrame()
{
	CStatusBar::GetInstance()->draw();
	//RObjectManager::GetInstance()->drawAllObjectsWithCameraAndGrid(_camera);
	RObjectManager::GetInstance()->drawAllObjectsWithCameraAndGrid(_camera);

	_text->draw(DT_LEFT);
}