#ifndef __GAME_SCENE__
#define __GAME_SCENE__

#include "GScene.h"
#include "GTiledBG.h"
#include "GTexture.h"
#include "Ghoul.h"
#include "SpearKnight.h"
#include "Panther.h"
#include "GCamera.h"
#include "GQuadTree.h"
#include "EffectManager.h"
#include "ObjectManager.h"
#include "InfoManager.h"
#include "Text.h"

class GTiledBG;
class CSimon;
class GCamera;
class CObjectManager;

class GameScene : public GScene
{
public:
	GameScene();
	~GameScene();
	CSimon * getSimon();
protected:
	void RenderFrame() = 0;
	virtual void ProcessInput() = 0;
	virtual void LoadResources() = 0;
	virtual void update(int a_delta_time) = 0;
	//GQuadtree *_quadTree;
	GTiledBG * _bg;
	CSimon *_simon;
	GCamera *_camera;
	Text *_simonPosition;
};

#endif //!__GAME_SCENE__