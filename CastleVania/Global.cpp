#include "Global.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <algorithm>
#include <iostream>

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include "dsound.h"

//
//GLOBAL CONSTANT
//

// tieu nun
int G_CurForm;
// tieu nun
int G_NextForm;

int			G_GameDepth;
int			G_FrameRate = 30;
int			G_ColorMode;
bool		G_IsFullScreen = false;
D3DFORMAT	G_BackBufferFormat;

bool		G_HasBackgroundSound = true;
bool		G_HasEffectSound = true;

int			G_MaxSize;
int			G_MinSize;

int			G_ScreenHeight = 480; //480;	//480	//768	//768

//
//GLOBAL VARIANT
//

HINSTANCE					G_hInstance;		// Handle of the game instance
HWND						G_hWnd;				// Handle of the Game Window

LPDIRECT3D9					G_DirectX;
LPDIRECT3DDEVICE9			G_Device;
LPDIRECT3DSURFACE9			G_BackBuffer;

LPDIRECTINPUT8				G_DirectInput;		// The DirectInput object         
LPDIRECTINPUTDEVICE8		G_KeyBoard;			// The keyboard device 
LPDIRECTINPUTDEVICE8		G_Mouse;			// The mouse device
DIMOUSESTATE				G_MouseState;		// The mouse state
LPD3DXSPRITE				G_SpriteHandler;	// spriteHandler to draw texture
LPDIRECTSOUND8				G_SoundManager;


void GLTrace(char* format, ...)
{	
	char *_traceFile = "C:\\Temp\\Sample_TH_game.log";
	int _traceNum = 1;

	if (!_traceNum) return;

	FILE *f = stderr;
	if (_traceFile!=NULL)
	{
		if (fopen_s(&f, _traceFile,"a")!=0) 
		{
			fprintf(stderr,"WARNING: Failed to open trace file '%s' for writing!\n", _traceFile);
			return;
		}
	}
	va_list ap;
	va_start(ap, format);
	fprintf(f, format, ap);
	va_end(ap);
	fprintf(f,"\n");
	if (_traceFile != NULL) fclose(f);
}

void GLMessage(char* text)
{
	MessageBox(G_hWnd, text, "CastleVania", MB_OK);
}

void GLTitle(char* text){
	SetWindowText(G_hWnd, text);
}

bool operator==(const GPoint2D & lhs, const GPoint2D & rhs)
{
	return (lhs.x == rhs.x && lhs.y == rhs.y);
}

GPoint2D::GPoint2D()
{
	x = y = 0;
}

GPoint2D::GPoint2D(float a_x, float a_y)
{
	x = a_x;
	y = a_y;
}

void GPoint2D::operator=(const GPoint2D & point)
{
	this->x = point.x;
	this->y = point.y;
}

GRect::GRect()
{
	position.x = position.y = width = height = vx = vy = 0;
}

GRect::GRect(float a_x, float a_y, int a_width, int a_height, float a_vx, float a_vy)
{
	position.x = a_x;
	position.y = a_y;
	width = a_width;
	height = a_height;
	vx = a_vx;
	vy = a_vy;
}

GRect::GRect(const GRect& rect)
{
	position = rect.position;
	width = rect.width;
	height = rect.height;
	vx = rect.vx;
	vy = rect.vy;
}

void GRect::operator=(const GRect & rect)
{
	this->position.x = rect.position.x;
	this->position.y = rect.position.y;
	this->width = rect.width;
	this->height = rect.height;
	this->vx = rect.vx;
	this->vy = rect.vy;
}