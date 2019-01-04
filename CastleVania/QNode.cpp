#include "QNode.h"


CQNode::CQNode()
{
	_bound.left = _bound.top = _bound.right = _bound.bottom = 0;
	_tl = _tr = _bl = _br = NULL;
}


void CQNode::setParent(CQNode *_parent)
{
	_nodeID = _parent->_nodeID;
	_bound.left = _parent->_bound.left;
	_bound.top = _parent->_bound.top;
	_bound.right = _parent->_bound.right;
	_bound.bottom = _parent->_bound.bottom;
}

void CQNode::AddObject(int _idObject)
{
	_listobject.push_back(_idObject);
}

GRect CQNode::GetBound()
{
	GRect _rect;
	_rect.position.x = _bound.left;
	_rect.position.y = _bound.top;
	_rect.width = _bound.right;
	_rect.height = _bound.bottom;
	return _rect;
}
CQNode::~CQNode()
{

}