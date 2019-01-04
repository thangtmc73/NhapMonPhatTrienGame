#ifndef __SCENE_LEVEL_1_STAGE_1__
#define __SCENE_LEVEL_1_STAGE_1__

#include "GScene.h"
#include "GTiledBG.h"
#include "GTexture.h"
#include "Simon.h"
#include "Ghoul.h"
#include "SpearKnight.h"
#include "Panther.h"
#include "GCamera.h"
#include "GQuadTree.h"
#include "Ground.h"

class SceneLevel1Stage1 : public GScene
{
public:
	SceneLevel1Stage1();
	~SceneLevel1Stage1();

protected:
	void RenderFrame();
	virtual void ProcessInput();
	virtual void LoadResources();
	virtual void Update(int a_delta_time);
private:
	//GQuadtree *_quadTree;
	CGround *_ground;
	GTiledBG *_bg;
	CSimon *_simon;
	CGhoul *_ghoul;
	CSpearKnight *_spearKnight;
	CPanther *_panther;
	GCamera *_camera;
};

#endif //!__SCENE_LEVEL_1_STAGE_1__