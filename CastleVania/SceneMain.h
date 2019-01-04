#ifndef _SCENEMAIN_H_
#define _SCENEMAIN_H_

#include "Game.h"
#include "GTiledMap.h"
#include "GTexture.h"
#include "Simon.h"
#include "Ghoul.h"
#include "SpearKnight.h"
#include "Panther.h"

class SceneMain: public CGame
{
public: 	
	SceneMain(int _nCmdShow);
	~SceneMain();

protected:	

	void RenderFrame();
	virtual void ProcessInput();
	virtual void LoadResources();
	virtual void Update();
private:
	GTiledMap *_map;
	CSimon *_simon;
	CGhoul *_ghoul;
	CSpearKnight *_spearknight;
	CPanther *_panther;
};

#endif