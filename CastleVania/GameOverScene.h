#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "GScene.h"
#include "GTexture.h"
#include "Simon.h"
#include "GCamera.h"
#include "InfoManager.h"
#include "Text.h"

class GameOverScene : public GScene
{
public:
	GameOverScene();
	~GameOverScene();

protected:
	void RenderFrame();
	virtual void ProcessInput();
	virtual void LoadResources();
	virtual void update(int a_delta_time);
private:
	GPoint2D _chosenFirst;
	Text *_title;
	Text *_list;
	int _chosen;
	bool _up, _down;
	GTexture *_heart;
	bool _enter;
};

#endif //!__GAME_OVER_SCENE_H__