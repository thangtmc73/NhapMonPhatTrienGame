#ifndef __STAGE2_2__
#define __STAGE2_2__

#include "GameScene.h"

class Stage2_2 : public GameScene
{
public:
	Stage2_2();
	~Stage2_2();

protected:
	void RenderFrame();
	virtual void ProcessInput();
	virtual void LoadResources();
	virtual void update(int a_delta_time);
};

#endif //!__STAGE2_2__