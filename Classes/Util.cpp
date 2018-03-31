#include "Util.h"

Vector<String *> Util::splitString(const char *srcStr, const char *sSep)
{
	Vector<String *> stringList;

	int size = strlen(srcStr);
	String *str = String::create(srcStr);

	int startIndex = 0;
	int endIndex = 0;
	endIndex = str->_string.find(sSep);

	String *spliStr = NULL;
	while (endIndex > 0)
	{
		spliStr = String::create("");
		spliStr->_string = str->_string.substr(startIndex, endIndex);

		stringList.pushBack(spliStr);
		str->_string = str->_string.substr(endIndex + 1, size);
		endIndex = str->_string.find(sSep);
	}

	if (str->_string.compare("") != 0)
	{
		stringList.pushBack(String::create(str->_string));
	}

	return stringList;
}
