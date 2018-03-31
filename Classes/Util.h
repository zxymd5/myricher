#ifndef __UTIL_H__
#define __UTIL_H__

#include "cocos2d.h"

USING_NS_CC;

class Util
{
public:
	static Vector<String *> splitString(const char *srcStr, const char *sSep);
};

#endif
