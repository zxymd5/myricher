#ifndef __UTIL_H__
#define __UTIL_H__

#include "cocos2d.h"

USING_NS_CC;

class Util 
{
public:
	static Vector<__String *> splitString(const char *srcStr, const char *sSep);
	static Point map2GL(const Point& ptMap, TMXTiledMap *map);
	static Point GL2map(const Point& ptGL, TMXTiledMap *map);
	static void sendCustomEvent(const std::string messageType, __String *message);
};

#endif
