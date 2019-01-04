#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>
#include "GQuadTree.h"
#include "ObjectConfig.h"
#include "struct.h"

class RObject;

LPDIRECT3DSURFACE9 CreateSurfaceFromFile(LPDIRECT3DDEVICE9 d3ddv, char* filePath);
void GetMapInfoToRender(char * a_filePath, int **a_array_map[], int &width, int &height);

//#ifdef  __QUADTREE_H__

//GQuadtree* CreateQuadTree()
//{
//	//Init base game region for detecting collision
//	GQuadtree* quadtree = new GQuadtree(1, new GRect(0, 0, 800, 600));
//
//	//list* entity_list = EntityManager::GetInstance()->GetEntityList();
//	//for (auto i = entity_list->begin(); i != entity_list->end(); i++)
//	//	quadtree->Insert(*i);
//
//	return quadtree;
//}
int GetTheLengthOfNumber(int a_number);
std::string ConvertNumberToStringWithTheLength(int a_length, int a_number);

float greater(float a, float b);
float less(float a, float b);

// returns true if the boxes are colliding (velocities are not used)
bool IsAABBCheck(GRect a_rect1, GRect a_rect2);

bool IsCollidingSide(GRect a_rect1, GRect a_rect2, eDirection &a_directionColliding);
bool IsCollidingSideLeftOrRight(GRect a_rect1, GRect a_rect2, eDirection &a_directionColliding);
bool IsCollidingSideTopOrBottom(GRect a_rect1, GRect a_rect2, eDirection &a_directionColliding);

// returns true if the boxes are colliding (velocities are not used)
// moveX and moveY will return the movement the b1 must move to avoid the collision
//bool IsAABBCollision(CBaseObject *a_object1, CBaseObject *a_object2);
GRect GetSweptBroadphaseBox(GRect b, int a_deltaTime);
float SweptAABB(GRect b1, GRect b2, eDirection& a_directionColliding, int a_deltaTime, bool debug = false);
CollisionInfo IsCollide(RObject* a_colliding, RObject* a_collided, int a_deltaTime);
bool IsColliding(RObject* a_colliding, RObject* a_collided);
GPoint2D linearInterpolation(GPoint2D startPoint, GPoint2D endPoint, GPoint2D currentPos, DWORD time, DWORD totalTime);


#endif //!__UTILS_H__