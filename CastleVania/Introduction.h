#ifndef __INTRODUCTION_H__
#define __INTRODUCTION_H__
#include "Text.h"
#include"GTexture.h"
#include"GScene.h"
#include"GInputManager.h"
#include"GSystem.h"
#include"GSprite.h"

class Introduction : public GScene
{
private:
	Text *_textChoice;
	Text *_textDescription;
	GTexture *_gTextureFrame;
	GSprite *_bat;
	int _index = 0;
	bool _start;
	bool _draw;
public:
	Introduction();
	~Introduction();
protected:
	void RenderFrame();
	virtual void LoadResources();
	virtual void ProcessInput();
	virtual void update(int a_delta_time);
};
#endif //!__INTRODUCTION_H__