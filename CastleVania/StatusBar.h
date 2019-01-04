#ifndef __STATUS_BAR_H___
#define __STATUS_BAR_H___

#include "StaticObject.h"
#include "Text.h"
#include "GTexture.h"
#include "GSprite.h"

class CStatusBar : public CStaticObject
{
public:
	void SetPosition(GPoint2D a_point);
	virtual void update(int a_deltaTime);
	virtual void draw();
	static CStatusBar* GetInstance();
	~CStatusBar();
private:
	static CStatusBar* _instance;
	CStatusBar();
	// position top-left point status bar
	GPoint2D _topLeftPosition;

	GSprite *_playerTexture;
	GSprite *_enemyTexture;
	Text *_firstRowTitle;
	Text *_secondRowTitle;
	Text *_heartsAndP;
	GTexture *_bg;

	// special weapon display
	GTexture *_arraySpecialWeaponTexture[5];
};
#endif