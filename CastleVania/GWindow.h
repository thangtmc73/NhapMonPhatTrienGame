#ifndef __GWINDOW_H__
#define __GWINDOW_H__

#include <Windows.h>

class GWindow
{
public:
	GWindow *GetInstance();
	bool Init();
	void Release();
private:
	static GWindow *_instance;
	int nCmdShow;

	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	int InitWindow(int nCmdShow);

	bool InitDirectX();
	void ReleaseDirectX();
};
GWindow* GWindow::_instance = NULL;
#endif //!__GWINDOW_H__