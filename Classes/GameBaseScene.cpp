#include "GameBaseScene.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

int GameBaseScene::tiledColsCount;
int GameBaseScene::tiledRowsCount;
bool **GameBaseScene::canPassGrid;
TMXLayer *GameBaseScene::wayLayer;
Vector<RicherPlayer *> GameBaseScene::players_vector;

cocos2d::Scene * GameBaseScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameBaseScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameBaseScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	addRightBanner();
	drawTable(2);
	setWayPassToGrid();
	addPlayer();
	addGoButton();
	addNotificationObserver();
	addDigiteRoundSprite();
	refreshRoundDisplay();
	return true;
}

void GameBaseScene::setWayPassToGrid()
{
	wayLayer = _map->getLayer("way");
	Size _mapSize = wayLayer->getLayerSize();
	for (int j = 0; j < _mapSize.width; j++)
	{
		for (int i = 0; i < _mapSize.height; i++)
		{
			Sprite *_sp = wayLayer->getTileAt(Point(j, i));
			if (_sp)
			{
				float x = _sp->getPositionX();
				float y = _sp->getPositionY();
				int col = x / tiledWidth;
				int row = y / tiledHeight;
				canPassGrid[row][col] = true;
				Vec2 p = _sp->getPosition();
				wayLayerPass_vector.push_back(p);
				log("canPassGrid row = %d, col = %d, canpass = %d", row, col, canPassGrid[row][col]);
			}
		}
	}
	log("setWayPassToGrid finished");
}

void GameBaseScene::onExit()
{
	CC_SAFE_DELETE(canPassGrid);
	Layer::onExit();
}

void GameBaseScene::addGoButton()
{
	Menu *menu = Menu::create();
	menu->setPosition(Point::ZERO);
	setMenu(menu);
	goMenuItemButton = MenuItemImage::create("button/go_normal.png", "button/go_press.png",
											CC_CALLBACK_1(GameBaseScene::menuButtonCallback, this));
	goMenuItemButton->setPosition(Vec2(tableStartPosition_x + 2 * tableWidth, 
								tableStartPosition_y - tableHeight * 6));
	goMenuItemButton->setTag(goButtonTag);
	menu->addChild(goMenuItemButton);
	addChild(menu);
}

void GameBaseScene::menuButtonCallback(Ref *pSender)
{
	int tag = ((Node *)pSender)->getTag();
	if (tag == goButtonTag)
	{
		log("go button clicked");
		randStepsNumber = rand() % 6 + 1;
		RouteNavigation::getInstance()->getPath(player1, randStepsNumber,
			canPassGrid, tiledRowsCount, tiledColsCount);
		std::vector<int> colVector = RouteNavigation::getInstance()->getPathCols_vector();
		std::vector<int> rowVector = RouteNavigation::getInstance()->getPathRows_vector();

		for (int i = 0; i < rowVector.size(); i++)
		{
			log(" rowVector row is %d -- colVector col is %d", rowVector[i], colVector[i]);
		}
		NotificationCenter::getInstance()->postNotification(RICHER_MSG, String::createWithFormat("%d", MSG_GO_HIDE_TAG));
		player1->startGo(rowVector, colVector);
		log("go button clicked over");
	}
}

void GameBaseScene::drawTable(int playerNumber)
{
	auto s = Director::getInstance()->getWinSize();
	auto draw = DrawNode::create();
	this->addChild(draw);

	for (int i = 0; i < playerNumber; i++)
	{
		draw->drawSegment(Vec2(tableStartPosition_x, tableStartPosition_y - 2 * i * tableHeight),
						  Vec2(tableStartPosition_x + 3 * tableWidth, tableStartPosition_y - 2 * i * tableHeight), 
						  1, Color4F(0, 1, 0, 1));

		draw->drawSegment(Vec2(tableStartPosition_x, tableStartPosition_y - 2 * (i + 1) * tableHeight), 
						  Vec2(tableStartPosition_x + 3 * tableWidth, tableStartPosition_y - 2 * (i + 1) * tableHeight), 
						  1, Color4F(0, 1, 0, 1));

		draw->drawSegment(Vec2(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight - 2 * i * tableHeight),
						  Vec2(tableStartPosition_x + 3 * tableWidth, tableStartPosition_y - tableHeight - 2 * i * tableHeight), 
						  1, Color4F(0, 1, 0, 1));

		draw->drawSegment(Vec2(tableStartPosition_x + tableWidth, tableStartPosition_y - 2 * i * tableHeight), 
						 Vec2(tableStartPosition_x + tableWidth, tableStartPosition_y - 2 * tableHeight - 2 * i * tableHeight), 
						  1, Color4F(0, 1, 0, 1));
	}
}

void GameBaseScene::addPlayer()
{
	Sprite *player_1 = Sprite::create(PLAYER_1);
	player_1->setPosition(tableStartPosition_x + tableWidth / 2, tableStartPosition_y - tableHeight);
	addChild(player_1);

	Label *player_1_money = Label::createWithTTF("$", "fonts/Marker Felt.ttf", 25);
	player_1_money->setAnchorPoint(Vec2(0, 0.5));
	player_1_money->setPosition(Vec2(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight / 2));
	addChild(player_1_money);

	Label *player_1_strength = Label::createWithTTF("+", "fonts/Marker Felt.ttf", 28);
	player_1_strength->setAnchorPoint(Vec2(0, 0.5));
	player_1_strength->setPosition(Vec2(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight / 2 * 3));
	addChild(player_1_strength);
	
	Sprite *player_2 = Sprite::create(PLAYER_2);
	player_2->setPosition(tableStartPosition_x + tableWidth / 2, tableStartPosition_y - 3 * tableHeight);
	addChild(player_2);

	Label *player_2_money = Label::createWithTTF("$", "fonts/Marker Felt.ttf", 25);
	player_2_money->setAnchorPoint(Vec2(0, 0.5));
	player_2_money->setPosition(Vec2(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight / 2 * 5));
	addChild(player_2_money);

	Label *player_2_strength = Label::createWithTTF("+", "fonts/Marker Felt.ttf", 28);
	player_2_strength->setAnchorPoint(Vec2(0, 0.5));
	player_2_strength->setPosition(Vec2(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight / 2 * 7));
	addChild(player_2_strength);

	struct timeval now;
	gettimeofday(&now, NULL);
	unsigned rand_seed = (unsigned)(now.tv_sec * 1000 + now.tv_usec / 1000);
	srand(rand_seed);
	
	player1 = RicherPlayer::create(PLAYER_1_NAME, PLAYER_1_TAG);
	int _rand1 = rand() % (wayLayerPass_vector.size());
	log("rand %d", _rand1);
	Vec2 vec2ForPlayer1 = wayLayerPass_vector.at(_rand1);
	vec2ForPlayer1.y += tiledHeight;
	player1->setPosition(vec2ForPlayer1);
	player1->setAnchorPoint(Vec2(0, 0.5));
	addChild(player1);
	players_vector.pushBack(player1);

	player2 = RicherPlayer::create(PLAYER_2_NAME, PLAYER_2_TAG);
	int _rand2 = rand() % (wayLayerPass_vector.size());
	log("rand %d", _rand2);
	Vec2 vec2ForPlayer2 = wayLayerPass_vector.at(_rand2);
	vec2ForPlayer2.y += tiledHeight;
	player2->setPosition(vec2ForPlayer2);
	player2->setAnchorPoint(Vec2(0, 0.5));
	addChild(player2);
	players_vector.pushBack(player2);
}

void GameBaseScene::addRightBanner()
{
	Sprite *rightBanner = Sprite::create(RIGHT_BANNER);
	rightBanner->setAnchorPoint(Vec2(0, 0));
	rightBanner->setPosition(Vec2(tableStartPosition_x, 0));
	addChild(rightBanner);
}

void GameBaseScene::addNotificationObserver()
{
	NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(GameBaseScene::receivedNotificationMsg),
		RICHER_MSG, NULL);	
}

void GameBaseScene::receivedNotificationMsg(Ref *data)
{
	__String *srcDate = (__String *)data;
	Vector<__String *> messageVector = Util::splitString(srcDate->getCString(), "-");
	int retMsgType = messageVector.at(0)->intValue();
	log("received go message is: %d", retMsgType);

	switch (retMsgType)
	{
	case MSG_GO_SHOW_TAG:
	{
		goMenuItemButton->runAction(MoveBy::create(0.3, Vec2(-(goMenuItemButton->getContentSize().width) * 2, 0)));
		gameRoundCount++;
		refreshRoundDisplay();
		break;
	}
	case MSG_GO_HIDE_TAG: 
	{
		goMenuItemButton->runAction(MoveBy::create(0.3, Vec2(goMenuItemButton->getContentSize().width * 2, 0)));
		break;
	}
	default:
		break;
	}
}

void GameBaseScene::addDigiteRoundSprite()
{
	gameRoundCount = 0;
	auto frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("images/digital_round.plist");

	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_0));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_1));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_2));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_3));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_4));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_5));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_6));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_7));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_8));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_9));
}

void GameBaseScene::refreshRoundDisplay()
{
	for (auto it = refreshRoundVector.begin(); it != refreshRoundVector.end(); it++)
	{
		((Sprite *)*it)->setVisible(false);
	}

	refreshRoundVector.clear();
	int count = gameRoundCount;
	Sprite *st;
	if (count == 0)
	{
		st = Sprite::createWithSpriteFrame(digiteRoundVector.at(0));
		addChild(st);
		refreshRoundVector.pushBack(st);
	}
	while (count != 0)
	{
		st = Sprite::createWithSpriteFrame(digiteRoundVector.at(count % 10));
		addChild(st);
		refreshRoundVector.pushBack(st);
		count = count / 10;
	}
	refreshRoundVector.reverse();
	for (int i = 0; i < refreshRoundVector.size(); i++)
	{
		Sprite *sp = refreshRoundVector.at(i);
		sp->setPosition(Vec2((tableStartPosition_x + 50) + (i * 25), 50));
		sp->setVisible(false);
	}
}
