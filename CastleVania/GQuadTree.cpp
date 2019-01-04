#include "GQuadTree.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Utils.h"

// Thêm thư viện fstream xử lý file vào
#include <fstream>

using namespace std;
CQuadTree::CQuadTree(){
	_nodeRoot = new CQNode();
	//Khởi tạo giá trị cho hình chữ nhật đó
	_rectFirst.left = 96;
	_rectFirst.top = 0;
	_rectFirst.right = 800;
	_rectFirst.bottom = G_ScreenHeight;
	_rectSecond.left = 2080;
	_rectSecond.top = 0;
	_rectSecond.right = 544;
	_rectSecond.bottom = G_ScreenHeight;
}
void CQuadTree::GetFromFile(char *_filename)
{
	FILE *pFile = fopen(_filename, "r");
	if (pFile == NULL)
	{
		printf("Can't open file!");
	}
	fstream f;
	f.open(_filename, ios::in);
	int j = 0;
	//  Đọc dữ liệu từ file vào string data
	std::string data;
	// Đọc từng dòng và nối vào data
	std::string line;
	while (!f.eof())
	{
		std::vector<int> _iLine;
		getline(f, line);
		std::istringstream is(line);
		int n;
		while (is >> n) {
			_iLine.push_back(n);
		}
		mapQuadtree[j] = new CQNode();
		mapQuadtree[j]->_nodeID = _iLine[0];
		mapQuadtree[j]->_bound.left = _iLine[1];
		mapQuadtree[j]->_bound.top = _iLine[2];
		mapQuadtree[j]->_bound.right = _iLine[3];
		mapQuadtree[j]->_bound.bottom = _iLine[4];
		if (_iLine.size() > 5)
		{
			for (int i = 5; i < _iLine.size(); i++)
			{
				mapQuadtree[j]->AddObject(_iLine[i]);
			}
		}
		j++;
	}

	fclose(pFile);
}

void CQuadTree::SetQuadTree()
{
	std::map<int, CQNode*>::iterator it;
	std::map<int, CQNode*>::iterator _check;
	int p, child, vt;
	/*Tim node cha cua no tu do cho no tro vao node con */
	for (it = mapQuadtree.begin(); it != mapQuadtree.end(); it++)
	{
		if (it->second->_nodeID == 0)//Node goc
		{
			_nodeRoot->setParent(it->second);
		}
		else
		{

			p = it->second->_nodeID / 8; //id cua node cha
			//Xét vị trí mà p xuất hiện trong map
			for (_check = mapQuadtree.begin(); _check->first < it->first; _check++)
			if (_check->second->_nodeID == p)
				vt = _check->first;
			child = it->second->_nodeID % 8; //id cua node con = id node cha * 8 +chi so(Theo mapeditor)
			//mapQuadtree[p] Con tro tro toi node cha
			switch (child)
			{
			case 1:
				mapQuadtree[vt]->_bl = it->second;
				break;
			case 2:
				mapQuadtree[vt]->_br = it->second;
				break;
			case 3:
				mapQuadtree[vt]->_tl = it->second;
				break;
			case 4:
				mapQuadtree[vt]->_tr = it->second;
				break;
			}
		}
	}
}

std::vector<int> CQuadTree::ListObjectInViewport(GCamera *a_camera)
{
	SetQuadTree();
	GRect _rect1;
	_rect1.position.x = a_camera->viewport.x;
	_rect1.position.y = 0;
	_rect1.width = a_camera->_minSize;
	_rect1.height = G_ScreenHeight;
	std::map<int, CQNode*>::iterator it;
	//Kiểm tra viewport sẽ va chạm với những node nào
	for (it = mapQuadtree.begin(); it != mapQuadtree.end(); it++)
	{
		if (it->second == _nodeRoot)//Nếu đối số truyền vào là node gốc thì clear list
			_listObjectInViewPort.clear();
		//Nếu đối số truyền vào là node lá mà trong đó có chứa các object thì đưa ra listObjectInViewPort
		if (IsAABBCheck(_rect1, it->second->GetBound()) && it->second->_tl == NULL)
		{
			//Tránh sự trùng lặp các object 
			if (it->second->_listobject.size() > 0)
			{
				if (!(std::find(_listNodeID.begin(), _listNodeID.end(), it->second->_nodeID) != _listNodeID.end()))
				{
					for (int k = 0; k < it->second->_listobject.size(); k++)
					{
						_listObjectInViewPort.push_back(it->second->_listobject[k]);

					}
					_listNodeID.push_back(it->second->_nodeID);
				}
			}
		}
	}
	return _listObjectInViewPort;
}

CQuadTree::~CQuadTree()
{

}