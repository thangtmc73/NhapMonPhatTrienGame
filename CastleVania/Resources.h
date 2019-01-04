#ifndef __RESOURCES_MANAGER__
#define __RESOURCES_MANAGER__

#include <map>
#include <string>
#include "struct.h"

class GTexture;
class RTexture;
class TiXmlElement;

class Resources {
public:
	static Resources * getInstance();
	bool loadResourceFromFile(const char *a_path);
	RTexture* getTextureWithName(std::string name);
	int getIntegerConstWithName(std::string name);
	float getFloatConstWithName(std::string name);
	std::string getStringConstWithName(std::string name);
	bool loadTexturesFromTextureInfo();
	bool loadFromXml(TiXmlElement *node);
	void addTexture(std::string name, RTexture *texture);
	ObjectResourceObject getObjectResourceInfo(std::string name);


	void clear();
private:
	void loadConstantFromTiXML(TiXmlElement* elem);
	void loadObjectInfoFromTiXML(TiXmlElement *elem);
	bool loadAllTextureFromXml(TiXmlElement * node);

	Resources();
	std::map<std::string, std::string> _listString;
	std::map<std::string, int> _listInteger;
	std::map<std::string, float> _listFloat;
	std::map<std::string, RTexture*> _listTextures;
	std::map<std::string, std::string> _mapNameTextures;
	std::map<std::string, ObjectResourceObject> _objectResources;
	static Resources *_instance;
};

#endif // !__RESOURCES_MANAGER__