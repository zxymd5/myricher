#ifndef __GAME_BASE_SCENE_H__
#define __GAME_BASE_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ConstUtil.h"

USING_NS_CC;
USING_NS_CC_EXT;

const int tableStartPosition_x = 650;
const int tableStartPosition_y = 450;
const int tableWidth = 50;
const int tableHeight = 40;

class GameBaseScene : public Layer {
public:
	static Scene *createScene();
	TMXTiledMap *_map;
	virtual bool init();

	CREATE_FUNC(GameBaseScene);
private:
	void drawTable(int playerNumber);
	void addPlayer();
	void addRightBanner();
};

#endif
