#include "GCamera.h"
#include "InfoManager.h"
#include "GSystem.h"
#include "Utils.h"

GCamera::GCamera()
{
	viewport.x = 0;
	viewport.y = 0;
}

void GCamera::SetSizeMap(int _max, int _min)
{
	_maxSize = _max;
	_minSize = _min;
}
D3DXVECTOR2 GCamera::Transform(int x, int y)
{
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);
	matrix._22 = -1;
	matrix._41 = -viewport.x;
	matrix._42 = viewport.y;

	D3DXVECTOR3 pos3(x, y, 1);
	D3DXVECTOR4 MatrixResult;
	D3DXVec3Transform(&MatrixResult, &pos3, &matrix);

	D3DXVECTOR2 result = D3DXVECTOR2(MatrixResult.x, MatrixResult.y);
	return result;
}

D3DXVECTOR3 GCamera::CenterSprite(int x, int y)
{
	D3DXVECTOR3 pCenter = D3DXVECTOR3(x / 2, y / 2, 0);
	return pCenter;
}



void GCamera::UpdateCamera(int a_x)
{
	if (CInfoManager::GetInstance()->isStopCamera()) {
		return;
	}
	if (a_x < _minSize / 2)
	{
		viewport.x = _xStartCamera;
		return;
	}
	viewport.x = a_x - _xStartCamera - _minSize / 2;
	if (viewport.x > _maxSize - _minSize)
	{
		viewport.x = _xStartCamera + _maxSize - _minSize;
	}
}

bool GCamera::scrollCameraCenterToPositionX(int a_x)
{
	if (viewport.x + _minSize / 2 < a_x)
	{
		int temptViewPortX = viewport.x + CAMERA_VX * GSystem::GetInstance()->GetDeltaTime();
		//viewport.x += CAMERA_VX * GSystem::GetInstance()->GetDeltaTime();
		if (temptViewPortX + _minSize / 2 >= a_x)
		{
			viewport.x = a_x - _minSize / 2;
			return true;
			CInfoManager::GetInstance()->SetMovingThroughGate(true);
			CInfoManager::GetInstance()->SetMoveableCameraBeforeGate(false);
			CInfoManager::GetInstance()->SetMoveableCameraAfterGate(true);
		}
		else {
			viewport.x = temptViewPortX;
		}
	}
	else
	{
		int temptViewPortX = viewport.x + CAMERA_VX * GSystem::GetInstance()->GetDeltaTime();
		//viewport.x -= CAMERA_VX * GSystem::GetInstance()->GetDeltaTime();
		if (temptViewPortX <= a_x)
		{
			viewport.x = a_x;
			return true;
			CInfoManager::GetInstance()->SetMovingThroughGate(true);
			CInfoManager::GetInstance()->SetMoveableCameraBeforeGate(false);
			CInfoManager::GetInstance()->SetMoveableCameraAfterGate(true);
		}
		else {
			viewport.x = temptViewPortX;
		}
	}
	return false;
}

bool GCamera::scrollCameraViewportPositionToPositionX(int a_x)
{
	if (viewport.x < a_x)
	{
		viewport.x += CAMERA_VX * GSystem::GetInstance()->GetDeltaTime();
		if (viewport.x >= a_x)
		{
			viewport.x = a_x;
			return true;
		}
	}
	else if (viewport.x > a_x)
	{
		viewport.x -= CAMERA_VX * GSystem::GetInstance()->GetDeltaTime();
		if (viewport.x <= a_x)
		{
			viewport.x = a_x;
			return true;
		}
	}
	else {
		return true;
	}
	return false;
}

bool GCamera::UpdateCameraUntilReachingPositionX(int a_x)
{
	if (viewport.x < a_x)
	{
		viewport.x += CAMERA_VX * GSystem::GetInstance()->GetDeltaTime();
		if (viewport.x >= a_x)
		{
			viewport.x = a_x;
			_xStartCamera = a_x;
			return true;
		}
	}
	else
	{
		viewport.x -= CAMERA_VX * GSystem::GetInstance()->GetDeltaTime();
		if (viewport.x <= a_x)
		{
			viewport.x = a_x;
			_xStartCamera = a_x;
			return true;
		}
	}
	return false;
}

int GCamera::GetMaxSize()
{
	return _maxSize;
}

int GCamera::GetMinSize()
{
	return _minSize;
}

void GCamera::UpdateCamera(int w, int h)
{
	//Tự viết dự vào hướng dẫn của GV LT
	viewport.x -= w;
}