#ifndef __STAGE1_1__
#define __STAGE1_1__

#include "GameScene.h"
class Stage1_1 : public GameScene
{
public:
	Stage1_1();
	~Stage1_1();

protected:
	void RenderFrame();
	virtual void Release();
	virtual void ProcessInput();
	virtual void LoadResources();
	virtual void update(int a_delta_time);
};

#endif //!__STAGE1_1__