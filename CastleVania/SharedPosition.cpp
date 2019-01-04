#include "SharedPosition.h"

CSharedPosition * CSharedPosition::_instance = NULL;

CSharedPosition * CSharedPosition::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new CSharedPosition;
	}
	return _instance;
}

void CSharedPosition::SetNewPosition(const char * a_key, GPoint2D a_position)
{
	_position[a_key] = a_position;
}

GPoint2D CSharedPosition::GetCurrentPosition(const char * a_key)
{
	std::map<std::string, GPoint2D>::iterator it = _position.find(a_key);
	if (it != _position.end())
	{
		return _position[a_key];
	}
	return GPoint2D(0, 0);
}

CSharedPosition::CSharedPosition(){ }