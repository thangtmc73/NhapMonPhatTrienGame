#include "Resources.h"
#include "Utils.h";
#include "TinyXML/tinyxml.h"
#include "RTexture.h"
#include <string>     // std::string, std::stof

Resources* Resources::_instance = nullptr;

Resources * Resources::getInstance()
{
	if (_instance == nullptr) _instance = new Resources();
	return _instance;
}

bool Resources::loadResourceFromFile(const char * a_path)
{
	if (a_path != NULL)
	{
		TiXmlDocument doc(a_path);
		bool success = doc.LoadFile();
		if (success)
		{
			//TiXmlElement* root = doc.FirstChildElement();
			TiXmlElement* root = doc.RootElement();
			for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
			{
				const char *value = elem->Value();
				std::string nodeName = value;
				if (nodeName == "constant") {
					loadConstantFromTiXML(elem);
				}
				if (nodeName == "textures") {
					loadAllTextureFromXml(elem);
				}
				if (nodeName == "object-info") {
					loadObjectInfoFromTiXML(elem);
				}
			}
		}
		else
		{
			doc.ErrorDesc();
			return false;
		}
	}
	return true;

}

RTexture * Resources::getTextureWithName(std::string name)
{
	if (_listTextures.find(name) == _listTextures.end()) {
		return NULL;
	}
	return _listTextures[name];
}

int Resources::getIntegerConstWithName(std::string name)
{
	return _listInteger[name];
}

float Resources::getFloatConstWithName(std::string name)
{
	return _listFloat[name];
}

std::string Resources::getStringConstWithName(std::string name)
{
	return _listString[name];
}

bool Resources::loadTexturesFromTextureInfo()
{
	for (std::map<std::string, std::string>::iterator it = _mapNameTextures.begin(); it != _mapNameTextures.end(); it++)
	{
		_listTextures[it->first] = new RTexture(it->second);
	}
	_mapNameTextures.clear();
	return true;
}

bool Resources::loadFromXml(TiXmlElement * node)
{
	for (TiXmlElement* elem = node->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		std::string keyName = elem->FirstAttribute()->Value();
		std::string value = elem->FirstChild()->Value();
		_listTextures[keyName] = new RTexture(value);
	}
	return true;
}

void Resources::clear()
{
	_listTextures.clear();
	_listFloat.clear();
	_listInteger.clear();
	_listString.clear();
}

void Resources::loadConstantFromTiXML(TiXmlElement *node)
{
	for (TiXmlElement* elem = node->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		std::string nodeName = elem->Value();
		std::string keyName = elem->FirstAttribute()->Value();
		std::string value = elem->FirstChild()->Value();

		if (nodeName == "string") {
			_listString[keyName] = value;
		}
		else if (nodeName == "integer") {
			_listInteger[keyName] = atoi(value.c_str());
		}
		else if (nodeName == "float") {
			_listFloat[keyName] = stof(value);
		}
	}
}

void Resources::loadObjectInfoFromTiXML(TiXmlElement * node)
{
	for (TiXmlElement* elem = node->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		std::string nodeName = elem->Value();
		std::string keyName = elem->FirstAttribute()->Value();
		std::string objectName;
		ObjectResourceObject object;
		object.spriteSheet.numCols = 1;
		object.spriteSheet.numRows = 1;
		object.spriteSheet.numFrames = 1;
		for (TiXmlAttribute* attr = elem->FirstAttribute(); attr != NULL; attr = attr->Next()) {
			std::string attr_name = attr->Name();
			std::string attr_value = attr->Value();

			if (attr_name == "name") {
				objectName = attr_value;
			}
			if (attr_name == "textureName") {
				object.textureName = attr_value;
			}
			if (attr_name == "frameHeight") {
				object.spriteSheet.frameHeight = atoi(attr_value.c_str());
			}
			if (attr_name == "frameWidth") {
				object.spriteSheet.frameWidth = atoi(attr_value.c_str());
			}
			if (attr_name == "cols") {
				object.spriteSheet.numCols = atoi(attr_value.c_str());
			}
			if (attr_name == "rows") {
				object.spriteSheet.numRows = atoi(attr_value.c_str());
			}
			if (attr_name == "numberFrame") {
				object.spriteSheet.numFrames = atoi(attr_value.c_str());
			}
			if (attr_name == "boundingBoxHeight") {
				object.boundingBoxHeight = atoi(attr_value.c_str());
			}
			if (attr_name == "boundingBoxWidth") {
				object.boundingBoxWidth = atoi(attr_value.c_str());
			}
		}
		_objectResources[objectName] = object;
	}
}

Resources::Resources()
{
}

void Resources::addTexture(std::string name, RTexture *texture)
{
	_listTextures[name] = texture;
}

ObjectResourceObject Resources::getObjectResourceInfo(std::string name)
{
	return _objectResources[name];
}

bool Resources::loadAllTextureFromXml(TiXmlElement * node)
{
	for (TiXmlElement* elem = node->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		std::string keyName = elem->FirstAttribute()->Value();
		std::string value = elem->FirstChild()->Value();
		_mapNameTextures[keyName] = value;
	}
	return true;
}
