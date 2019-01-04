#ifndef __RGAME_SCENE__
#define __RGAME_SCENE__

#include "GScene.h"
#include "GTexture.h"
#include "GCamera.h"
#include "GQuadTree.h"
#include "EffectManager.h"
#include "InfoManager.h"
#include "Text.h"
#include <map>
#include <vector>

class GTiledBG;
class CSimon;
class GCamera;
class TiXmlElement;
struct StageObject;

class RGameScene : public GScene
{
public:
	RGameScene();
	~RGameScene();
	CSimon * getSimon();
protected:
	void loadConfigFile();
	void nextStage();
	void RenderFrame();
	virtual void ProcessInput();
	virtual void LoadResources();
	virtual void update(int a_delta_time);
	CSimon *_simon;
	GCamera *_camera;
	Text *_text;
	std::string _textureBackground;
	std::vector<StageObject> _listStageInfos;
	int _indexNextStage;
private:
	bool _replaceScence;
};

#endif //!__RGAME_SCENE__