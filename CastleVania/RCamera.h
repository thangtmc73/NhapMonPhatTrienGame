#ifndef __RCAMERA_H__
#define __RCAMERA_H__

#include "Global.h"

class RCamera
{
public:
	D3DXVECTOR2 viewport;
	int _maxSize, _minSize;
	int _xStartCamera;

	RCamera();
	D3DXVECTOR3 CenterSprite(int x, int y);
	void UpdateCamera(int x);
	bool scrollCameraCenterToPositionX(int x);
	bool scrollCameraViewportPositionToPositionX(int a_x);
	bool UpdateCameraUntilReachingPositionX(int x);
	int GetMaxSize();
	int GetMinSize();
	void UpdateCamera(int w, int h);
	void SetSizeMap(int _max, int _min);
	D3DXVECTOR2 Transform(int x, int y);
private:

};
#endif //!__CAMERA_H__