#include "StatusBar.h"
#include "ObjectConfig.h"
#include "InfoManager.h"
#include "Utils.h"

CStatusBar* CStatusBar::_instance = NULL;

void CStatusBar::SetPosition(GPoint2D a_point)
{
	_topLeftPosition.x = a_point.x;
	_topLeftPosition.y = a_point.y;
}


void CStatusBar::update(int a_deltaTime)
{
	_firstRowTitle->SetString("SCORE-" + ConvertNumberToStringWithTheLength(6, CInfoManager::GetInstance()->GetScore()) + " TIME " + ConvertNumberToStringWithTheLength(4, CInfoManager::GetInstance()->GetClockTime())
		+ " STAGE " + ConvertNumberToStringWithTheLength(2, CInfoManager::GetInstance()->GetStage()));
	
	_heartsAndP->SetString(ConvertNumberToStringWithTheLength(2, CInfoManager::GetInstance()->GetNumberOfHearts()) + "\n" + ConvertNumberToStringWithTheLength(2, CInfoManager::GetInstance()->GetP()));
}

void CStatusBar::draw()
{
	_firstRowTitle->SetTextRect(5 + _topLeftPosition.x, 0 + _topLeftPosition.y,
		515 + _topLeftPosition.x, 17 + _topLeftPosition.y);
	_secondRowTitle->SetTextRect(5 + _topLeftPosition.x, 17 + _topLeftPosition.y, 99 + _topLeftPosition.x, 49 + _topLeftPosition.y);
	_heartsAndP->SetTextRect(430 + _topLeftPosition.x, 20 + _topLeftPosition.y, 470 + _topLeftPosition.x, 52 + _topLeftPosition.y);
	
	
	_bg->draw(_topLeftPosition.x, _topLeftPosition.y);
	_firstRowTitle->draw(DT_LEFT);
	_secondRowTitle->draw(DT_LEFT);
	_heartsAndP->draw(DT_LEFT);
	
	int xPlayer = 108 + _topLeftPosition.x;
	int xEnemy = 108 + _topLeftPosition.x;
	for (int i = 0; i < CInfoManager::GetInstance()->GetPlayerLife(); i++)
	{
		_playerTexture->draw(xPlayer, 26 + _topLeftPosition.y);
		xPlayer += _playerTexture->_texture->FrameWidth + 1;
	}
	for (int i = 0; i < CInfoManager::GetInstance()->GetEnemyLife(); i++)
	{
		_enemyTexture->draw(xEnemy, 45 + _topLeftPosition.y);
		xEnemy += _enemyTexture->_texture->FrameWidth + 1;
	}
	int specialweapon = CInfoManager::GetInstance()->GetCurrentSpeciaWeapon();
	if (specialweapon != 0)
	{
		_arraySpecialWeaponTexture[specialweapon - 1]->drawFlipX(_topLeftPosition.x + 370, _topLeftPosition.y + 30);
	}
}

CStatusBar * CStatusBar::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new CStatusBar();
	}
	return _instance;
}

CStatusBar::~CStatusBar()
{
	delete _playerTexture;
	delete _enemyTexture;
	delete _firstRowTitle;
	delete _secondRowTitle;
	delete _heartsAndP;
	delete _bg;
	for (int i = 0; i < 5; i++)
	{
		delete _arraySpecialWeaponTexture[i];
	}
	delete _arraySpecialWeaponTexture;
}

CStatusBar::CStatusBar()
{
	_topLeftPosition.x = 0;
	_topLeftPosition.y = 0;

	_bg = new GTexture("blackboard.png", 1, 1, 1);


	_playerTexture = new GSprite();
	_playerTexture->_texture = new GTexture("heal.png", 3, 1, 3);
	_playerTexture->_index = 0;
	_playerTexture->_texture->FrameHeight = 18;
	_playerTexture->_texture->FrameWidth = 11;

	_enemyTexture = new GSprite();
	_enemyTexture->_texture = new GTexture("heal.png", 3, 1, 3);
	_enemyTexture->_index = 2;
	_enemyTexture->_texture->FrameHeight = 18;
	_enemyTexture->_texture->FrameWidth = 11;

	_firstRowTitle = new Text();
	_firstRowTitle->Init(17, 9, 20, false, "Nintendo NES Font");
	_firstRowTitle->SetString("SCORE-" + ConvertNumberToStringWithTheLength(6, CInfoManager::GetInstance()->GetScore()) + " TIME " + ConvertNumberToStringWithTheLength(4, CInfoManager::GetInstance()->GetClockTime())
		+ " STAGE " + ConvertNumberToStringWithTheLength(2, CInfoManager::GetInstance()->GetStage()));

	_secondRowTitle = new Text();
	_secondRowTitle->Init(17, 9, 20, false, "Nintendo NES Font");
	_secondRowTitle->SetString("PLAYER\nENEMY");

	_heartsAndP = new Text();
	_heartsAndP->Init(17, 9, 20, false, "Nintendo NES Font");
	_heartsAndP->SetString(ConvertNumberToStringWithTheLength(2, CInfoManager::GetInstance()->GetNumberOfHearts()) + "\n" + ConvertNumberToStringWithTheLength(2, CInfoManager::GetInstance()->GetP()));


	_arraySpecialWeaponTexture[0] = new GTexture("dagger.png");
	_arraySpecialWeaponTexture[0]->FrameWidth = 32;
	_arraySpecialWeaponTexture[0]->FrameHeight = 18;
	_arraySpecialWeaponTexture[1] = new GTexture("holywater.png");
	_arraySpecialWeaponTexture[1]->FrameWidth = 32;
	_arraySpecialWeaponTexture[1]->FrameHeight = 18;
}