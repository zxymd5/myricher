#include "Util.h"

Vector<__String *> Util::splitString(const char *srcStr, const char *sSep)
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
