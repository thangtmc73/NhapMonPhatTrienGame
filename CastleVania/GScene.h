#ifndef __GSCENE_H__
#define __GSCENE_H__
#include <windows.h>
#include <d3d9.h>
#include "Global.h"
#include <dinput.h>
#include "GCamera.h"

class GScene
{
public:
	GScene();

	void Init();

	virtual void Release();

	virtual void LoadResources() = 0;
	virtual void ProcessInput() = 0;
	virtual void update(int a_delta_time) = 0;
	virtual void RenderFrame();
};

#endif //!__GSCENE_H__