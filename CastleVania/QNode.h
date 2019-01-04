#ifndef __QNode_H__
#define __QNode_H__

#include <vector>
#include "Global.h"
class CQNode{
public:
	CQNode();
	~CQNode();
	CQNode *_tl, *_tr, *_bl, *_br;
	int _nodeID;
	RECT _bound;
	std::vector<int>_listobject;
	void setParent(CQNode* _parent);
	void AddObject(int _idObject);//Cho biết đó là đối tượng nào
	GRect GetBound();
};

#endif 