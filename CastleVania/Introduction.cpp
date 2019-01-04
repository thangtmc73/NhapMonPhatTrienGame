#include "Introduction.h"
#include "StartGame.h"
#include "SceneManager.h"

Introduction::Introduction()
{
	_index = 0;
	_start = false;
	_draw = true;
}

void Introduction::LoadResources()
{
	_gTextureFrame = new GTexture("mainmenu.png");
	_bat = new GSprite();
	_textChoice = new Text();
	_textDescription = new Text();
	_textChoice->Init(18, 9, 20, false, "Nintendo NES Font");
	_textChoice->SetString("PUSH START KEY");
	_textChoice->SetTextRect(0, 270, 512, 450);
	_textDescription->Init(17, 9, 10, false, "Nintendo NES Font");
	_textDescription->SetString("TM AND 1987\nKONAMI INDUSTRY CO..LTD.\nLICENSED BY\nNINTENDO OF AMERICA INC.");
	_textDescription->SetTextRect(0, 312, 512, 450);
	_bat->_texture = new GTexture("bat_main_menu.png", 5, 3, 15);
	_bat->_texture->FrameHeight = 112;
	_bat->_texture->FrameWidth = 144;
	_bat->_start = 0;
	_bat->_end = 14;
	_bat->_index = 0;
	_bat->_timeAni = 150;
	//_result1=_text->InitFont();
}
void Introduction::RenderFrame()
{
	_gTextureFrame->draw(0, 0);
	
	_textDescription->draw();
	_bat->draw(450, 251);
	if (_draw)
	{
		_textChoice->draw();
	}
}

void Introduction::update(int a_delta_time)
{
	if (_start)
	{
		_index++;
		if (_index % 15 == 0)
		{
			_draw = !_draw;
		}
	}
	if (_index == 75)
	{
		GSceneManager::GetInstance()->ReplaceScene(new StartGame());
		return;
	}
	if (_bat->_index == 9 && _bat->_start == 0)
	{
		_bat->_start = 12;
	}
	_bat->update(a_delta_time);
}

void Introduction::ProcessInput()
{
	if (!_start)
	{
		_start = GInputManager::GetInstance()->IsKeyDown(DIK_RETURN);
	}
}

Introduction::~Introduction()
{

}