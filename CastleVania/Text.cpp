#include"Text.h"

int _count = 0;
int _countTime = 300;
Text::Text()
{
	_text = "Hello World";
	_font = NULL;
	SetRect(&_rect, 0, 0, 500, 100);
}
Text::~Text()
{
	_font->Release();
	_font = 0;
}
bool Text::Init(INT a_fontHeight, INT a_fontWidth, UINT a_fontWeight, bool _aItalic, LPCTSTR a_font)
{
	HRESULT hr = D3DXCreateFont(G_Device, a_fontHeight, a_fontWidth, a_fontWeight, 1, _aItalic, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, a_font, &_font);
	if (!SUCCEEDED(hr))
		return false;
	//Khi người dùng nút để PUSH START KEY thì sẽ vẽ lại text trong ô mới để tạo hiệu ứng nhấp nháy
	//Thay đổi tọa độ x giữ nguyên y thì sẽ nhấp nháy theo chiều ngang
	/*SetRect(&_rect2, 71, 280, 520, 450);
	_message1 ="            PUSH START KEY\n\n            TM  AND    1987\nKONAMI   INDUSTRY  CO..LTD."
				"\n                  LICENSED BY\nNINTENDO  OF  AMERICA  INC.";
	_message2 ="            PUSH START KEY";*/
	//SetRect(&_rect3,20,10, 520, 450);
	return true;
}

void Text::Release()
{
	if (_font) {
		_font->Release();
		_font = NULL;
	}
}

void Text::SetString(std::string a_text)
{
	_text = a_text;
}

void Text::SetTextRect(int a_x, int a_y, int a_width, int a_height)
{
	_rect.left = a_x;
	_rect.top = a_y;
	_rect.right = a_width;
	_rect.bottom = a_height;
}

void Text::draw(int a_type)
{
	if (_font)
	{
		int a = _font->DrawTextA(G_SpriteHandler, _text.c_str(), -1, &_rect, a_type, D3DCOLOR_XRGB(255,255,255));
		a = 5;
	}
	/*if (_start)
	{
		_font->DrawTextA(NULL, _message2.c_str(), -1, &_rect2, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
		_countConvert++;
		_start = false;
	}*/
}
void Text::drawIntro()
{
	/*if(_font)
	{
		_message3 = "SCORE-000000      TIME    0" + std::to_string(_countTime) + "     STAGE  " + "01\nPLAYER\nENEMY";
		_font->DrawTextA(NULL, _message3.c_str(), -1, &_rect3, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
	}
	_count += 1;*/
	/*if (_count == 80)
	{
		_countTime -= 1;
		_count = 0;
	}*/
}