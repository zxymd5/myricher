#include "Util.h"

Vector<__String*> Util::splitString(const char * srcStr, const char * sSep)
{
	Vector<__String *> stringList;
	int size = strlen(srcStr);
	__String *str = __String::create(srcStr);

	int startIndex = 0;
	int endIndex = 0;
	endIndex = str->_string.find(sSep);

	__String *spliStr = NULL;
	while (endIndex > 0)
	{
		spliStr = __String::create("");
		spliStr->_string = str->_string.substr(startIndex, endIndex);
		stringList.pushBack(spliStr);
		str->_string = str->_string.substr(endIndex + 1, size);
		endIndex = str->_string.find(sSep);
	}

	if (str->_string.compare("") != 0)
	{
		stringList.pushBack(__String::create(str->_string));
	}

	return stringList;
}

Point Util::map2GL(const Point & ptMap, TMXTiledMap * map)
{
	Point ptUI;
	ptUI.x = ptMap.x * map->getTileSize().width;
	ptUI.y = (ptMap.y + 1) * map->getTileSize().height;

	Point ptGL = ptUI;
	ptGL.y = map->getContentSize().height - ptUI.y;
	return ptGL;
}

Point Util::GL2map(const Point & ptGL, TMXTiledMap * map)
{
	Point ptUI = ptGL;
	ptUI.y = map->getContentSize().height - ptGL.y;

	int x = ptUI.x / map->getTileSize().width;
	int y = ptUI.y / map->getTileSize().height;

	return Vec2(x, y);
}

void Util::sendCustomEvent(const std::string messageType, __String * message)
{
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	EventCustom _event = EventCustom(messageType);
	_event.setUserData(message);
	dispatcher->dispatchEvent(&_event);
}
