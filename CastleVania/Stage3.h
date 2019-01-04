#ifndef __STAGE3__
#define __STAGE3__

#include "GameScene.h"

class Stage3 : public GameScene
{
public:
	Stage3();
	~Stage3();

protected:
	void RenderFrame();
	virtual void ProcessInput();
	virtual void LoadResources();
	virtual void update(int a_delta_time);
};

#endif //!__STAGE3__