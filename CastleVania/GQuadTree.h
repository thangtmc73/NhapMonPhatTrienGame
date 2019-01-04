#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <map>
#include"QNode.h"
#include "GCamera.h"
#include <algorithm>

class GCamera;
class CQNode;
//Có thêm RedMoneyBagBonuses(Túi tiền màu đỏ xuất hiện trong stage 1_1) vào file ObjectConfig.h với type = 600
class CQuadTree
{
protected:
	CQNode *_nodeRoot;
	std::map <int, CQNode*> mapQuadtree;//luu lai nodeId va CQNode
	std::vector<int> _listObjectInViewPort;
	std::vector<int>_listNodeID;
	/*std::map <int, CBaseObject*>mapGameObject;*/
	//Xét hình chữ nhật cho các đối tượng động di chuyển trong đó
	RECT _rectFirst, _rectSecond;
public:
	CQuadTree();
	void GetFromFile(char *_filename);
	void SetQuadTree();
	//Lấy danh sách những đối tượng trong màn hình
	std::vector<int> ListObjectInViewport(GCamera *a_camera);
	~CQuadTree();
};
#endif //!__QUADTREE_H__


