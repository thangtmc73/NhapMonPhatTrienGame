#include <d3dx9.h>
#include "Utils.h"
#include <stdio.h>
#include "Global.h"

#include "RObject.h"
#include "ObjectConfig.h"
#include "GSystem.h"
#include "RObject.h"
#include "Log.h"

LPDIRECT3DSURFACE9 CreateSurfaceFromFile(LPDIRECT3DDEVICE9 d3ddv, char* filePath)
{
	D3DXIMAGE_INFO info;

	HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);

	if(result != D3D_OK)
	{
		return NULL;
	}

	LPDIRECT3DSURFACE9 surface;

	d3ddv->CreateOffscreenPlainSurface(
		info.Width,
		info.Height,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&surface,
		NULL);

	result = D3DXLoadSurfaceFromFile(
		surface,
		NULL,
		NULL,
		filePath,
		NULL,
		D3DX_DEFAULT,
		D3DCOLOR_ARGB(0, 0, 0, 0),
		NULL);

	if(result != D3D_OK)
	{
		return NULL;
	}

	return surface;
}

void GetMapInfoToRender(char * a_filePath, int **a_array_map[], int &a_width, int &a_height)
{
	FILE *pFile = fopen(a_filePath, "r");

	if (pFile == NULL)
	{
		printf("Can't open file!");
	}
	fscanf(pFile, "%d %d", &a_width, &a_height);
	(*a_array_map) = new int*[a_height];
	for (int i = 0; i < a_height; i++)
	{
		(*a_array_map)[i] = new int[a_width];
	}
	for (int i = 0; i < a_height; i++)
	{
		for (int j = 0; j < a_width; j++)
		{
			fscanf(pFile, "%d", &(*a_array_map)[i][j]);
			int a = (*a_array_map)[i][j];
			if (j == a_width - 1)
			{
				fseek(pFile, 1, SEEK_CUR);
			}
		}
	}
	fclose(pFile);
}

int GetTheLengthOfNumber(int a_number)
{
	int count = 0;
	if (a_number == 0)
	{
		return 1;
	}
	while (a_number != 0)
	{
		a_number = (int)a_number / 10;
		count++;
	}
	return count;
}

std::string ConvertNumberToStringWithTheLength(int a_length, int a_number)
{
	std::string result = "";
	if (a_length > GetTheLengthOfNumber(a_number))
	{
		int length_zero = a_length - GetTheLengthOfNumber(a_number);
		for (int i = 0; i < length_zero; i++)
		{
			result += "0";
		}
	}
	return result + std::to_string(a_number);
}



float greater(float a, float b)
{
	if (a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

float less(float a, float b)
{
	if (a < b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

// returns true if the boxes are colliding (velocities are not used)
bool IsAABBCheck(GRect a_rect1, GRect a_rect2)
{
	if (!(a_rect1.position.x + a_rect1.width < a_rect2.position.x
		|| a_rect1.position.x > a_rect2.position.x + a_rect2.width
		|| a_rect1.position.y < a_rect2.position.y - a_rect2.height
		|| a_rect1.position.y - a_rect1.height > a_rect2.position.y)) {
		return true;
	}

	return false;
}

bool IsCollidingSide(GRect a_rect1, GRect a_rect2, eDirection & a_directionColliding)
{
	a_directionColliding = eDirection::NONE;
	if (a_rect1.position.x + a_rect1.width < a_rect2.position.x
		|| a_rect1.position.x > a_rect2.position.x + a_rect2.width
		|| a_rect1.position.y < a_rect2.position.y - a_rect2.height
		|| a_rect1.position.y - a_rect1.height > a_rect2.position.y)
	{
		return false;
	}

	float rect1_bottom = a_rect1.position.y + a_rect1.height;
	float rect2_bottom = a_rect2.position.y + a_rect2.height;
	float rect1_right = a_rect1.position.x + a_rect1.width;
	float rect2_right = a_rect2.position.x + a_rect2.width;

	float b_collision = rect2_bottom - a_rect1.position.y;
	float t_collision = rect1_bottom - a_rect2.position.y;
	float l_collision = rect1_right - a_rect2.position.x;
	float r_collision = rect2_right - a_rect1.position.x;

	if (t_collision < b_collision && t_collision < l_collision && t_collision < r_collision)
	{
		a_directionColliding = (eDirection)(a_directionColliding | eDirection::TOP);
	}
	if (b_collision < t_collision && b_collision < l_collision && b_collision < r_collision)
	{
		a_directionColliding = (eDirection)(a_directionColliding | eDirection::BOTTOM);
	}
	if (l_collision < r_collision && l_collision < t_collision && l_collision < b_collision)
	{
		a_directionColliding = (eDirection)(a_directionColliding | eDirection::LEFT);
	}
	if (r_collision < l_collision && r_collision < t_collision && r_collision < b_collision)
	{
		a_directionColliding = (eDirection)(a_directionColliding | eDirection::RIGHT);
	}
	return true;
}

bool IsCollidingSideLeftOrRight(GRect a_rect1, GRect a_rect2, eDirection & a_directionColliding)
{
	a_directionColliding = eDirection::NONE;
	if (a_rect1.position.x + a_rect1.width < a_rect2.position.x
		|| a_rect1.position.x > a_rect2.position.x + a_rect2.width
		|| a_rect1.position.y < a_rect2.position.y - a_rect2.height
		|| a_rect1.position.y - a_rect1.height > a_rect2.position.y)
	{
		return false;
	}

	if ((a_rect1.position.y - a_rect1.height < a_rect2.position.y && a_rect1.position.y - a_rect1.height >= a_rect2.position.y - a_rect2.height)
		|| (a_rect1.position.y <= a_rect2.position.y && a_rect1.position.y > a_rect2.position.y - a_rect2.height)
		|| (a_rect1.position.y >= a_rect2.position.y && a_rect1.position.y - a_rect1.height <= a_rect2.position.y - a_rect2.height))
	{
		if (a_rect1.position.x + a_rect1.width == a_rect2.position.x && a_rect1.position.x < a_rect2.position.x)
		{
			a_directionColliding = (eDirection)(a_directionColliding | eDirection::RIGHT);
		}
		else if (a_rect1.position.x == a_rect2.position.x + a_rect2.width && a_rect1.position.y > a_rect2.position.x)
		{
			a_directionColliding = (eDirection)(a_directionColliding | eDirection::LEFT);
		}

		if ((a_directionColliding & (eDirection::LEFT | eDirection::RIGHT)) == (eDirection::LEFT | eDirection::RIGHT))
		{
			a_directionColliding = eDirection::NONE;
		}
	}
	return true;
}

bool IsCollidingSideTopOrBottom(GRect a_rect1, GRect a_rect2, eDirection & a_directionColliding)
{
	a_directionColliding = eDirection::NONE;
	if (a_rect1.position.x + a_rect1.width < a_rect2.position.x
		|| a_rect1.position.x > a_rect2.position.x + a_rect2.width
		|| a_rect1.position.y < a_rect2.position.y - a_rect2.height
		|| a_rect1.position.y - a_rect1.height > a_rect2.position.y)
	{
		return false;
	}

	/*if ((a_rect1.position.x <= a_rect2.position.x && a_rect1.position.x + a_rect1.width > a_rect2.position.x)
		|| (a_rect1.position.x >= a_rect2.position.x && a_rect2.position.x + a_rect2.width > a_rect1.position.x))
	{*/
	if (a_rect1.position.x + a_rect1.width > a_rect2.position.x && a_rect1.position.x < a_rect2.position.x + a_rect2.width)
	{
		if (a_rect1.position.y < a_rect2.position.y && a_rect1.position.y >= a_rect2.position.y - a_rect2.height)
		{
			a_directionColliding = (eDirection)(a_directionColliding | eDirection::TOP);
		}
		else if (a_rect1.position.y > a_rect2.position.y && a_rect1.position.y - a_rect1.height <= a_rect2.position.y)
		{
			a_directionColliding = (eDirection)(a_directionColliding | eDirection::BOTTOM);
		}

		if ((a_directionColliding & (eDirection::TOP | eDirection::BOTTOM)) == (eDirection::TOP | eDirection::BOTTOM))
		{
			a_directionColliding = eDirection::NONE;
		}
	}
	return true;
}


GRect GetSweptBroadphaseBox(GRect b, int a_deltaTime)
{
	GRect broadphasebox;

	b.vx = b.vx * a_deltaTime;
	b.vy = b.vy * a_deltaTime;

	broadphasebox.position.x = b.vx > 0 ? b.position.x : b.position.x + b.vx;
	broadphasebox.position.y = b.vy > 0 ? b.position.y + b.vy: b.position.y;
	broadphasebox.width = b.vx > 0 ? b.width + b.vx : b.width - b.vx;
	broadphasebox.height = b.vy > 0 ? b.height + b.vy : b.height - b.vy;

	return broadphasebox;
}

//// performs collision detection on moving box b1 and static box b2
//// returns the time that the collision occured (where 0 is the start of the movement and 1 is the destination)
//// getting the new position can be retrieved by box.x = box.x + box.vx * collisiontime
//// normalx and normaly return the normal of the collided surface (this can be used to do a response)
float SweptAABB(GRect b1, GRect b2, eDirection& a_directionColliding, int a_deltaTime, bool debug)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	b1.vx = b1.vx * a_deltaTime;
	b1.vy = b1.vy * a_deltaTime;

	// find the distance between the objects on the near and far sides for x
	if (b1.vx > 0.0f)
	{
		xInvEntry = b2.position.x - (b1.position.x + b1.width);
		xInvExit = (b2.position.x + b2.width) - b1.position.x;
	}
	else
	{
		xInvEntry = (b2.position.x + b2.width) - b1.position.x;
		xInvExit = b2.position.x - (b1.position.x + b1.width);
	}

	// find the distance between the objects on the near and far sides for y
	if (b1.vy > 0.0f)
	{
		yInvEntry = (b2.position.y - b2.height) - b1.position.y;
		yInvExit = b2.position.y - (b1.position.y - b1.height);
	}
	else
	{
		yInvEntry = b2.position.y - (b1.position.y - b1.height);
		yInvExit = (b2.position.y - b2.height) - b1.position.y;
	}

	// find time of collision and time of leaving for each axis
	// (if statement is to prevent divide by zero)
	float xEntry, yEntry;
	float xExit, yExit;

	if (b1.vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / b1.vx;
		xExit = xInvExit / b1.vx;
	}

	if (b1.vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / b1.vy;
		yExit = yInvExit / b1.vy;
	}

	// find the earliest/latest times of collision
	float entryTime = greater(xEntry, yEntry);
	float exitTime = less(xExit, yExit);
	if (debug == true) {
	}
	// if there was no collision
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		a_directionColliding = eDirection::NONE;
		return 1.0f;
	}
	else // if there was a collision
	{
		// calculate normal of collided surface
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0.0f)
			{
				a_directionColliding = eDirection::RIGHT;

			}
			else
			{
				a_directionColliding = eDirection::LEFT;

			}
		}
		else
		{
			if (yInvEntry < 0.0f)
			{
				a_directionColliding = eDirection::TOP;
			}
			else
			{
				if (debug == true) {
					Log::getInstance()->addLog("tai sao lai bottom" + std::to_string(b1.vy));
				}
				a_directionColliding = eDirection::BOTTOM;
			}
		}

		// return the time of collision
		return entryTime;
	}
}

CollisionInfo IsCollide(RObject* a_colliding, RObject* a_collided, int a_deltaTime)
{
	GRect collidingBox = a_colliding->getTopLeftBoundingBox();
	GRect collidedBox = a_collided->getTopLeftBoundingBox();
	
	collidingBox.vx -= collidedBox.vx;
	collidingBox.vy -= collidedBox.vy; 
	GRect boardphaseBoxObject = GetSweptBroadphaseBox(collidingBox, a_deltaTime);
	CollisionInfo result;
	if (a_colliding->getType() == eTypeObject::Simon && a_collided->isNormalGroundObject() && a_collided->getIndex() == 1121) {
	}
	if (IsAABBCheck(boardphaseBoxObject, collidedBox))
	{
		if (a_colliding->getType() == eTypeObject::Simon && a_collided->isNormalGroundObject()) {
		}
		if (a_colliding->getType() == eTypeObject::Simon && a_collided->isNormalGroundObject()) {
		}

		eDirection directionColliding;
		if (a_colliding->getType() == eTypeObject::Simon && a_collided->isNormalGroundObject()) {
			result.collisionTime = SweptAABB(collidingBox, collidedBox, result.direction, a_deltaTime, true);
		}
		else {
			result.collisionTime = SweptAABB(collidingBox, collidedBox, result.direction, a_deltaTime);
		}
		return result;
	}
	else {
		if ((int)collidedBox.position.y == 156)
		{
			Log::getInstance()->addLog("AABB fail" + std::to_string(collidedBox.position.y) + " " + std::to_string(collidingBox.position.y));
		}
	}
	result.direction = eDirection::NONE;
	result.collisionTime = 1;
	return result;
}

bool IsColliding(RObject * a_colliding, RObject * a_collided)
{
	GRect collidingBox = a_colliding->getTopLeftBoundingBox();
	GRect collidedBox = a_collided->getTopLeftBoundingBox();
	return IsAABBCheck(collidingBox, collidedBox);
}

GPoint2D linearInterpolation(GPoint2D startPoint, GPoint2D endPoint, GPoint2D currentPos, DWORD time, DWORD totalTime)
{
	GPoint2D result;
	float percentage = (float)time / totalTime;
	if (percentage >= 1)
	{
		return endPoint;
	}
	result.x = startPoint.x + (endPoint.x - startPoint.x) * percentage;
	result.y = startPoint.y + (endPoint.y - startPoint.y) * percentage;
	return result;
}
