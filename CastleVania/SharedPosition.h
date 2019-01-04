#ifndef __CSHARED_POSITION_H__
#define __CSHARED_POSITION_H__

#include "Global.h"
#include <string>
#include <map>

class CSharedPosition
{
public:
	static CSharedPosition* GetInstance();
	void SetNewPosition(const char* a_key, GPoint2D a_position);
	GPoint2D GetCurrentPosition(const char* a_key);
private:
	std::map<std::string, GPoint2D> _position;
	static CSharedPosition *_instance;
	CSharedPosition();
};
#endif //!__CSHARED_POSITION_H__