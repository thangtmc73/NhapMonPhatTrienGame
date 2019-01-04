#include "TextureManager.h"
#include "Utils.h";
#include "TinyXML/tinyxml.h"
#include "RTexture.h"

TextureManager* TextureManager::_instance = nullptr;

TextureManager * TextureManager::getInstance()
{
	if (_instance == nullptr) _instance = new TextureManager();
	return _instance;
}

RTexture * TextureManager::getTextureWithName(std::string name)
{
	return _listTextures[name];
}

bool TextureManager::loadFromXml(TiXmlElement * node)
{
	for (TiXmlElement* elem = node->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		std::string keyName = elem->FirstAttribute()->Value();
		std::string value = elem->FirstChild()->Value();
		_listTextures[keyName] = new RTexture(value);
	}
	return true;
}

void TextureManager::clear()
{
	_listTextures.clear();
}

TextureManager::TextureManager()
{
}

void TextureManager::addTexture(std::string name, RTexture *texture)
{
	_listTextures[name] = texture;
}
