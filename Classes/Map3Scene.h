#ifndef __MAP3_SCENE_H__
#define __MAP3_SCENE_H__

#include "cocos2d.h"
#include "GameBaseScene.h"

USING_NS_CC;

class Map3Scene : public GameBaseScene
{
public:
	static Scene *createScene();
	void addMap();
	virtual bool init();
	void initTiledGrid();
	CREATE_FUNC(Map3Scene);
};

#endif
