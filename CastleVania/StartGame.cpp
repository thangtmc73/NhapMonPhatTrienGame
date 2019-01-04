#include "StartGame.h"
#include "StatusBar.h"
#include "SceneManager.h"
#include "Stage1_1.h"
#include "SoundManager.h"
#include "GSprite.h"

StartGame::StartGame()
{
	_spriteBat1 = new GSprite();
	_spriteBat2 = new GSprite();
	_spriteHelicopter = new GSprite();
	_spriteSimon = new GSprite();

	_simonX = 515 - 64;
	_simonY = 372;

	_bat1X = 0;
	_bat1Y = 280;

	_bat2X = 295;
	_bat2Y = 115;

	_helicopterX = 600;
	_helicopterY = 150;

	_spriteSimon->_start = 0;
	_spriteSimon->_end = 3;
	_spriteSimon->_timeAni = 100;
	_spriteSimon->_index = 0;
	_spriteSimon->_timeLocal = 0;
	
	_spriteBat1->_start = 0;
	_spriteBat1->_end = 1;
	_spriteBat1->_timeAni = 100;
	_spriteBat1->_index = 0;
	_spriteBat1->_timeLocal = 0;

	_spriteBat2->_start = 0;
	_spriteBat2->_end = 1;
	_spriteBat2->_timeAni = 100;
	_spriteBat2->_index = 0;
	_spriteBat2->_timeLocal = 0;

	_spriteHelicopter->_start = 0;
	_spriteHelicopter->_end = 0;
	_spriteHelicopter->_timeAni = 100;
	_spriteHelicopter->_index = 0;
	_spriteHelicopter->_timeLocal = 0;

	_simonFinish = false;
	_helicopterFinish = false;
	_batFinish1 = false;
	_batFinish2 = false;
}
void StartGame::LoadResources()
{
	_gTextureIntro = new GTexture("intro.png", 1, 1, 1);
	_spriteSimon->_texture = new GTexture("simon.png", 8, 3, 24);
	_spriteBat1->_texture = new GTexture("bat_intro.png", 2, 1, 2);
	_spriteBat2->_texture = new GTexture("bat_intro.png", 2, 1, 2);
	_spriteHelicopter->_texture = new GTexture("helicopter.png", 1, 1, 1);
	CSoundManager::GetInstance()->LoopSoundWithIndex(eSoundIndex::GAME_START);
	CStatusBar::GetInstance()->SetPosition(GPoint2D(0, 0));
}

void StartGame::RenderFrame()
{
	//_gTextureIntro->draw(0, 0);
	CStatusBar::GetInstance()->draw();
	_gTextureIntro->draw(0, 69);
	//_gTextureFrame->draw(0, 0);
	_spriteSimon->draw(_simonX, _simonY);
	_spriteBat1->draw(_bat1X, _bat1Y);
	_spriteBat2->draw(_bat2X, _bat2Y);
	_spriteHelicopter->draw(_helicopterX, _helicopterY);
}

void StartGame::update(int a_delta_time)
{
	_spriteBat1->update(a_delta_time);
	_spriteBat2->update(a_delta_time);
	

	if (_simonX <= 255)
	{
		_simonX = 255;
		_spriteSimon->_index = 9;
		_simonFinish = true;
		//_replace++;
	}
	else
	{
		_spriteSimon->update(a_delta_time);
		_simonX -= a_delta_time * 0.01;
	}


	if (_bat1X < 120)
	{
		_bat1X += a_delta_time * 0.065;
		_bat1Y -= a_delta_time * 0.000001;
	}
	else
	{
		_batFinish1 = true;
	}

	if (_bat2X > 235)
	{
		_bat2X -= a_delta_time * 0.008;
		_bat2Y += a_delta_time * 0.008;
	}
	else
	{
		_batFinish2 = true;
	}

	if (_helicopterX > 320)
	{
		_helicopterX -= a_delta_time * 0.0001;
	}
	else
	{
		_helicopterFinish = true;
	}
	
	
	if (_helicopterFinish && _batFinish1 && _batFinish2 && _simonFinish)
	{
		GSceneManager::GetInstance()->ReplaceScene(new Stage1_1());
		return;
	}
}
void StartGame::ProcessInput()
{
}

StartGame::~StartGame()
{

}