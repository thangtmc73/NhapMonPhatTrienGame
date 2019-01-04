#ifndef __STAGE1_2__
#define __STAGE1_2__

#include "GameScene.h"

class Stage1_2 : public GameScene
{
public:
	Stage1_2();
	~Stage1_2();

protected:
	void RenderFrame();
	virtual void ProcessInput();
	virtual void LoadResources();
	virtual void update(int a_delta_time);
private:
	void moveCamera();
	bool replaceScreen;
};

#endif //!__STAGE1_2__