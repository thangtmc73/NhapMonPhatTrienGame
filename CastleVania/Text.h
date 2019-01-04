#ifndef __Text_H__
#define __Text_H__
#include"Global.h"
#include<sstream>

class Text
{
public:
	Text();
	~Text();
	
	bool Init(INT a_fontHeight, INT a_fontWidth, UINT a_fontWeight, bool _aItalic, LPCTSTR a_font);
	void Release();
	void SetString(std::string a_text);
	void SetTextRect(int a_x, int a_y, int a_width, int a_height);
	void draw(int a_type = DT_CENTER);
	void drawIntro();
private:
	ID3DXFont *_font;
	std::string _text;
	RECT _rect;
};

#endif