#ifndef CSPRITE_H
#define CSPRITE_H

#include <d3d9.h>
#include <d3dx9.h>

#include "GTexture.h"

class GSprite {
private:
	float _anchorPointX;
	float _anchorPointY;
public: 
	GTexture* _texture;

	int _start;		//chạy từ frame đầu tiên (chỉ số)
	int _end;		//chạy đến frame cuối cùng (chỉ số)
	int _index;		//frame hiện tại
	int _timeAni;	//thời gian chuyển frame
	int _timeLocal;	//biến hỗ trợ đếm thời gian

	GSprite();
	GSprite(const GSprite &sprite);
	GSprite(GTexture* texture, int timeAnimation);
	GSprite(GTexture* texture, int start, int end, int timeAnimation);

	//sang frame tiếp theo
	void Next();

	//trở về frame đầu tiên
	void Reset();

	//chọn 1 frame nào đó
	void SelectIndex(int index);

	//update animation
	bool update(int ellapseTime);
	bool update(int ellapseTime, bool loop);
	void update(int ellapseTime, int &trach_change);
	bool UpdateOnceTime(int ellapseTime, bool &a_changeIndex);
	bool UpdateOnceTimeFinishWithStart(int ellapseTime, bool &a_changeIndex);
	bool UpdateOnceTimeCountDown(int ellapseTime, int &a_changeIndex);
	bool UpdateOnceTimeCountDown(int ellapseTime, bool &a_changeIndex);

	// Render current sprite at location (X,Y) at the target surface
	void draw(int x, int y);
	
	//Render with scale (-1, 1)
	void drawFlipX(int x, int y);

	//render with scale (1, -1)
	void drawFlipY(int x, int y);

	//Render Rect of texture at (x,y)
	void drawRect(int X, int Y, RECT SrcRect);

	void drawIndex(int index, int X, int Y);

	int GetIndex();
	void SetAnchorPoint(float a_anchorPointX, float a_anchorPointY);
	~GSprite();
};

#endif