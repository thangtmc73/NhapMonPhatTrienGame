#ifndef __START_GAME_H__
#define __START_GAME_H__

#include "Text.h"
#include"GTexture.h"
#include"GScene.h"
#include "GInputManager.h"
#include "dsound.h"
#include "dsutil.h"
#include "GSprite.h"

class StartGame :public GScene
{
private:
	GSound *_themeSound;
	GTexture *_gTextureIntro;
	int _simonX, _simonY;
	int _bat1X, _bat1Y;
	int _bat2X, _bat2Y;
	int _helicopterX, _helicopterY;
	bool _batFinish1;
	bool _batFinish2;
	bool _helicopterFinish;
	bool _simonFinish;
public:
	
	StartGame();
	~StartGame();
	GSprite *_spriteSimon, *_spriteBat1, *_spriteBat2, *_spriteHelicopter;
	
	void RenderFrame();
	virtual void LoadResources();
	virtual void ProcessInput();
	virtual void update(int a_delta_time);
};
#endif //!__START_GAME_H__