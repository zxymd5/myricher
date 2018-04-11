#ifndef __GAME_BASE_SCENE_H__
#define __GAME_BASE_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ConstUtil.h"
#include "RicherPlayer.h"
#include "RouteNavigation.h"
#include "Util.h"

USING_NS_CC;
USING_NS_CC_EXT;

const int tableStartPosition_x = 650;
const int tableStartPosition_y = 450;
const int tableWidth = 50;
const int tableHeight = 40;
const int tiledWidth = 32;
const int tiledHeight = 32;

const int goButtonTag = 700;

class GameBaseScene : public Layer {
public:
	static Scene *createScene();
	TMXTiledMap *_map;
	virtual bool init();

	CREATE_FUNC(GameBaseScene);

	static int tiledColsCount;
	static int tiledRowsCount;
	static bool **canPassGrid;
	static TMXLayer *wayLayer;
	std::vector<Vec2> wayLayerPass_vector;
	CC_SYNTHESIZE(Menu *, _menu, Menu);
	MenuItemImage *goMenuItemButton;
	int randStepsNumber;

	void setWayPassToGrid();
	void onExit();
	void addGoButton();
	void menuButtonCallback(Ref *pSender);

	RicherPlayer *player1;
	RicherPlayer *player2;

	static Vector<RicherPlayer*> players_vector;

private:
	void drawTable(int playerNumber);
	void addPlayer();
	void addRightBanner();
	void addNotificationObserver();
	void receivedNotificationMsg(Ref *data);
	void addDigiteRoundSprite();
	int gameRoundCount;
	Vector<SpriteFrame *>digiteRoundVector;
	Vector<Sprite*> refreshRoundVector;
	void refreshRoundDisplay();
};

#endif
