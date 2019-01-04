#ifndef __STAGE2_1__
#define __STAGE2_1__

#include "GameScene.h"

class Stage2_1 : public GameScene
{
public:
	Stage2_1();
	~Stage2_1();

protected:
	void RenderFrame();
	virtual void ProcessInput();
	virtual void LoadResources();
	virtual void update(int a_delta_time);
};

#endif //!__STAGE2_1__