#ifndef __GCAMERA_H__
#define __GCAMERA_H__

#include "Global.h"

class GCamera
{
public:
	D3DXVECTOR2 viewport;		//Thiết lập tọa độ của camera	
	int _maxSize, _minSize;
	int _xStartCamera;

	GCamera();
	D3DXVECTOR3 CenterSprite(int x, int y);	//Tìm tọa độ center của sprite
	void UpdateCamera(int nterToPositionXx);
	bool scrollCameraCenterToPositionX(int x);
	bool scrollCameraViewportPositionToPositionX(int a_x);
	bool UpdateCameraUntilReachingPositionX(int x);
	int GetMaxSize();
	int GetMinSize();
	void UpdateCamera(int w, int h);
	void SetSizeMap(int _max, int _min);
	D3DXVECTOR2 Transform(int x, int y);		//Hàm transform, chuyển tọa độ viewport về tọa độ world
private:

};
#endif //!__CAMERA_H__