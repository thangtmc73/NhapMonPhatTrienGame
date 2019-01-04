#ifndef __SCENE_LEVEL_1_SCENE_4__
#define __SCENE_LEVEL_1_SCENE_4_

#include "GScene.h"
#include "GTiledBG.h"
#include "GTexture.h"
#include "Simon.h"
#include "Ghoul.h"
#include "SpearKnight.h"
#include "Panther.h"
#include "GCamera.h"
#include "GQuadTree.h"

class SceneLevel1Scene4 : public GScene
{
public:
	SceneLevel1Scene4();
	~SceneLevel1Scene4();

protected:
	void RenderFrame();
	virtual void ProcessInput();
	virtual void LoadResources();
	virtual void Update(int a_delta_time);
private:
	GQuadtree *_quadTree;
	GTiledBG *_bg;
	CSimon *_simon;
	CGhoul *_ghoul;
	CSpearKnight *_spearKnight;
	CPanther *_panther;
	GCamera *_camera;
};

#endif //!__SCENE_LEVEL_1_SCENE_3__