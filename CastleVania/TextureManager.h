#ifndef __TEXTURE_MANAGER__
#define __TEXTURE_MANAGER__

#include <map>
#include <string>

class GTexture;
class RTexture;
class TiXmlElement;

class TextureManager {
public:
	static TextureManager * getInstance();
	RTexture* getTextureWithName(std::string name);
	bool loadFromXml(TiXmlElement *node);
	void addTexture(std::string name, RTexture *texture);
	void clear();
private:
	TextureManager();

	std::map<std::string, RTexture*> _listTextures;
	static TextureManager *_instance;
};

#endif // !__TEXTURE_MANAGER__