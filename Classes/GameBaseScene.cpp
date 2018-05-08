#include "GameBaseScene.h"

int GameBaseScene::tiledColsCount;
int GameBaseScene::tiledRowsCount;
bool **GameBaseScene::canPassGrid;
TMXLayer *GameBaseScene::wayLayer;
Vector<RicherPlayer *> GameBaseScene::players_vector;
Vector<Sprite *> GameBaseScene::pathMarkVector;
TMXTiledMap *GameBaseScene::_map;
TMXLayer *GameBaseScene::landLayer;
int GameBaseScene::blank_land_tiledID;
int GameBaseScene::strength_30_tiledID;
int GameBaseScene::strength_50_tiledID;
int GameBaseScene::strength_80_tiledID;

int GameBaseScene::randomEvent_tiledID;
int GameBaseScene::lottery_tiledID;
int GameBaseScene::stock_tiledID;

int GameBaseScene::player1_building_1_tiledID;
int GameBaseScene::player1_building_2_tiledID;
int GameBaseScene::player1_building_3_tiledID;

int GameBaseScene::player2_building_1_tiledID;
int GameBaseScene::player2_building_2_tiledID;
int GameBaseScene::player2_building_3_tiledID;

Scene *GameBaseScene::createScene()
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
	addPathMark();
	addPlayer();
	addGoButton();
	addNotificationObserver();
	addDigiteRoundSprite();
	refreshRoundDisplay();
	initLandLayerFromMap();
	initPopDialog();
	doSomeForParticle();
	return true;
}

void GameBaseScene::addRightBanner()
{
	Sprite *rightBanner = Sprite::create(RIGHT_BANNER);
	rightBanner->setAnchorPoint(Point::ZERO);
	rightBanner->setPosition(Vec2(tableStartPosition_x, 0));
	addChild(rightBanner);
}

void GameBaseScene::addPlayer()
{
	Sprite *player_1 = Sprite::create(PLAYER_1);
	player_1->setPosition(tableStartPosition_x + tableWidth / 2, tableStartPosition_y - tableHeight);
	addChild(player_1);

	player1_money_label = Label::createWithTTF("$", FONT_MENU, 25);
	player1_money_label->setAnchorPoint(Vec2(0, 0.5));
	player1_money_label->setPosition(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight / 2);
	addChild(player1_money_label);

	Label *player_1_strength = Label::createWithTTF("+", FONT_MENU, 28);
	player_1_strength->setAnchorPoint(Vec2(0, 0.5));
	player_1_strength->setPosition(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight / 2 * 3);
	addChild(player_1_strength);

	Sprite *player_2 = Sprite::create(PLAYER_2);
	player_2->setPosition(tableStartPosition_x + tableWidth / 2, tableStartPosition_y - 3 * tableHeight);
	addChild(player_2);

	player2_money_label = Label::createWithTTF("$", FONT_MENU, 25);
	player2_money_label->setAnchorPoint(Vec2(0, 0.5));
	player2_money_label->setPosition(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight / 2 * 5);
	addChild(player2_money_label);

	Label *player_2_strength = Label::createWithTTF("+", FONT_MENU, 28);
	player_2_strength->setAnchorPoint(Vec2(0, 0.5));
	player_2_strength->setPosition(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight / 2 * 7);
	addChild(player_2_strength);

	struct  timeval now;
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

	memset(money1, 0, 20);
	sprintf(money1, "$ %d", player1->getMoney());
	getPlayer1_money_label()->setString(money1);

	memset(money2, 0, 20);
	sprintf(money2, "$ %d", player2->getMoney());
	getPlayer2_money_label()->setString(money2);
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

void GameBaseScene::addGoButton()
{
	Menu *menu = Menu::create();
	menu->setPosition(Point::ZERO);
	setMenu(menu);
	goMenuItemButton = MenuItemImage::create(GO_NORMAL, GO_PRESSED, CC_CALLBACK_1(GameBaseScene::menuButtonCallback, this));

	goMenuItemButton->setPosition(Vec2(tableStartPosition_x + 2 * tableWidth, tableStartPosition_y - tableHeight * 6));
	goMenuItemButton->setTag(goButtonTag);
	menu->addChild(goMenuItemButton);
	addChild(menu);
}

void GameBaseScene::menuButtonCallback(Ref * pSender)
{
	int tag = ((Node *)pSender)->getTag();
	if (tag == goButtonTag)
	{
		log("go button clicked");
		randStepsNumber = rand() % 6 + 1;
		RouteNavigation::getInstance()->getPath(player1, randStepsNumber, canPassGrid, tiledRowsCount, tiledColsCount);
		std::vector<int> colVector = RouteNavigation::getInstance()->getPathCols_vector();
		std::vector<int> rowVector = RouteNavigation::getInstance()->getPathRows_vector();

		for (int i = 0; i < rowVector.size(); i++)
		{
			log(" rowVector row is %d -- colVector col is %d", rowVector[i], colVector[i]);
		}
		//NotificationCenter::getInstance()->postNotification(RICHER_MSG, __String::createWithFormat("%d", MSG_GO_HIDE_TAG));
		//auto dispatcher = Director::getInstance()->getEventDispatcher();
		//EventCustom _event = EventCustom(RICHER_MSG);
		//_event.setUserData(__String::createWithFormat("%d", MSG_GO_HIDE_TAG));
		//dispatcher->dispatchEvent(&_event);
		//player1->startGo(rowVector, colVector);
		//log("go button clicked over");
		Util::sendCustomEvent(RICHER_MSG, __String::createWithFormat("%d", MSG_GO_HIDE_TAG));
		player1->startGo(rowVector, colVector);
		log("go button clicked over");
	}
}

void GameBaseScene::onExit()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(customListener);
	CC_SAFE_DELETE(canPassGrid);
	scaleby1ForBuyLand->release();
	scaleby2ForBuyLand->release();
	landFadeOut->release();
	landFadeIn->release();
	Layer::onExit();
}

void GameBaseScene::addNotificationObserver()
{
	//NotificationCenter::getInstance()->addObserver(
	//	this, 
	//	CC_CALLFUNCO_SELECTOR(GameBaseScene::receivedNotificationMsg),
	//	RICHER_MSG,
	//	NULL);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	customListener = EventListenerCustom::create(RICHER_MSG, CC_CALLBACK_1(GameBaseScene::onReceiveCustomEvent, this));
	dispatcher->addEventListenerWithFixedPriority(customListener, 1);
}

void GameBaseScene::onReceiveCustomEvent(EventCustom * event)
{
	__String *srcDate = (__String*)event->getUserData();
	Vector<__String *> messageVector = Util::splitString(srcDate->getCString(), "-");
	int retMsgType = messageVector.at(0)->intValue();
	log("received go message is: %d", retMsgType);
	switch (retMsgType)
	{
	case MSG_GO_SHOW_TAG: {
		goMenuItemButton->runAction(MoveBy::create(0.3, Vec2(-(goMenuItemButton->getContentSize().width) * 2, 0)));
		gameRoundCount++;
		refreshRoundDisplay();
		break;
	}
	case MSG_GO_HIDE_TAG: {
		goMenuItemButton->runAction(MoveBy::create(0.3, Vec2((goMenuItemButton->getContentSize().width) * 2, 0)));
		break;
	}
	case MSG_BUY_BLANK_TAG:
	{
		buy_land_x = messageVector.at(1)->intValue();
		buy_land_y = messageVector.at(2)->intValue();
		int playerTag = messageVector.at(3)->intValue();
		switch (playerTag)
		{
		case PLAYER_1_TAG:
		{
			showBuyLandDialog(MSG_BUY_BLANK_TAG);
			break;
		}
		case PLAYER_2_TAG:
		{
			buyLand(MSG_BUY_BLANK_TAG, buy_land_x, buy_land_y, foot2Sprite, player2_building_1_tiledID, player2, PLAYER2_1_PARTICLE_PLIST);
			Util::sendCustomEvent(RICHER_CONTROLLER_MSG, __String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
			break;
		}
		default:
			break;
		}
		break;
	}
	case MSG_BUY_LAND_1_TAG:
	{
		buy_land_x = messageVector.at(1)->intValue();
		buy_land_y = messageVector.at(2)->intValue();
		int playerTag = messageVector.at(3)->intValue();
		switch (playerTag)
		{
		case PLAYER_1_TAG:
		{
			showBuyLandDialog(MSG_BUY_LAND_1_TAG);
			break;
		}
		case PLAYER_2_TAG:
		{
			buyLand(MSG_BUY_LAND_1_TAG, buy_land_x, buy_land_y, starFish2Sprite, player2_building_2_tiledID, player2, PLAYER2_1_PARTICLE_PLIST);
			Util::sendCustomEvent(RICHER_CONTROLLER_MSG, __String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
			break;
		}
		default:
			break;
		}
	}
	case MSG_BUY_LAND_2_TAG:
	{
		buy_land_x = messageVector.at(1)->intValue();
		buy_land_y = messageVector.at(2)->intValue();
		int playerTag = messageVector.at(3)->intValue();
		switch (playerTag)
		{
		case PLAYER_1_TAG:
		{
			showBuyLandDialog(MSG_BUY_LAND_2_TAG);
			break;
		}
		case PLAYER_2_TAG:
		{
			buyLand(MSG_BUY_LAND_2_TAG, buy_land_x, buy_land_y, heart2Sprite, player1_building_3_tiledID, player2, PLAYER2_1_PARTICLE_PLIST);
			Util::sendCustomEvent(RICHER_CONTROLLER_MSG, __String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
			break;
		}
		default:
			break;
		}

		break;
	}
	default:
		break;
	}
}

//void GameBaseScene::receivedNotificationMsg(Ref * data)
//{
//	__String *srcDate = (__String*)data;
//	Vector<__String *>messageVector = Util::splitString(srcDate->getCString(), "-");
//	int retMsgType = messageVector.at(0)->intValue();
//	log("received go message is : %d", retMsgType);
//
//	switch (retMsgType)
//	{
//	case MSG_GO_SHOW_TAG:
//		{
//			goMenuItemButton->runAction(MoveBy::create(0.3, Vec2(-(goMenuItemButton->getContentSize().width) * 2, 0)));
//			gameRoundCount++;
//			refreshRoundDisplay();
//			break;
//		}
//	case MSG_GO_HIDE_TAG:
//	{
//		goMenuItemButton->runAction(MoveBy::create(0.3, Vec2((goMenuItemButton->getContentSize().width) * 2, 0)));
//		break;
//	}
//	default:
//		break;
//	}
//}

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
		((Sprite*)*it)->setVisible(false);
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
		sp->setVisible(true);
	}
}

void GameBaseScene::addPathMark()
{
	Sprite *mark1 = Sprite::create(PATH_MARK_1);
	Sprite *mark2 = Sprite::create(PATH_MARK_2);
	Sprite *mark3 = Sprite::create(PATH_MARK_3);
	Sprite *mark4 = Sprite::create(PATH_MARK_4);
	Sprite *mark5 = Sprite::create(PATH_MARK_5);
	Sprite *mark6 = Sprite::create(PATH_MARK_6);

	mark1->setAnchorPoint(Point::ZERO);
	mark2->setAnchorPoint(Point::ZERO);
	mark3->setAnchorPoint(Point::ZERO);
	mark4->setAnchorPoint(Point::ZERO);
	mark5->setAnchorPoint(Point::ZERO);
	mark6->setAnchorPoint(Point::ZERO);

	mark1->setVisible(false);
	mark2->setVisible(false);
	mark3->setVisible(false);
	mark4->setVisible(false);
	mark5->setVisible(false);
	mark6->setVisible(false);

	addChild(mark1);
	addChild(mark2);
	addChild(mark3);
	addChild(mark4);
	addChild(mark5);
	addChild(mark6);

	pathMarkVector.pushBack(mark1);
	pathMarkVector.pushBack(mark2);
	pathMarkVector.pushBack(mark3);
	pathMarkVector.pushBack(mark4);
	pathMarkVector.pushBack(mark5);
	pathMarkVector.pushBack(mark6);
}

void GameBaseScene::drawPathColor(std::vector<int> rowVector, std::vector<int> colVector)
{
	int stepsCount = rowVector.size() - 1;

	for (int i = 1; i < rowVector.size(); i++)
	{
		pathMarkVector.at(i - 1)->setPosition(Vec2(colVector[i] * 32, rowVector[i] * 32));
		pathMarkVector.at(i - 1)->setVisible(true);
	}
}

void GameBaseScene::initPopDialog()
{
	popDialog = PopupLayer::create(DIALOG_BG);
	popDialog->setPopModalDialog(false);
	popDialog->setContentSize(Size(Dialog_Size_Width, Dialog_Size_Height));
	popDialog->setTitle(DIALOG_TITLE);
	popDialog->setContentText("", 20, 60, 250);
	popDialog->setCallbackFunc(this, callfuncN_selector(GameBaseScene::buyLandCallBack));

	popDialog->addButton(BUTTON_BG1, BUTTON_BG3, OK, Btn_OK_tag);
	popDialog->addButton(BUTTON_BG2, BUTTON_BG3, CANCEL, Btn_Cancel_tag);
	this->addChild(popDialog);
	popDialog->setVisible(false);
}

void GameBaseScene::initLandLayerFromMap()
{
	landLayer = _map->getLayer("land");
}

void GameBaseScene::showBuyLandDialog(int landTag)
{
	__String showMessage = "";
	switch (landTag)
	{
	case MSG_BUY_BLANK_TAG:
	{
		showMessage = __String::createWithFormat("Do you want to buy the land ? need $ %d", LAND_BLANK_MONEY)->getCString();
		break;
	}
	case MSG_BUY_LAND_1_TAG:
	{
		showMessage = __String::createWithFormat("Do you want to buy the land ? need $ %d", LAND_LEVEL_1_MONEY)->getCString();
		break;
	}
	case MSG_BUY_LAND_2_TAG:
	{
		showMessage = __String::createWithFormat("Do you want to buy the land ? need $ %d", LAND_LEVEL_2_MONEY)->getCString();
		break;
	}
	default:
		break;
	}
	popDialog->setDataTag(landTag);
	popDialog->getLabelContentText()->setString(showMessage.getCString());
	popDialog->setVisible(true);
}

void GameBaseScene::buyLandCallBack(Node *pNode)
{
	if (pNode->getTag() == Btn_OK_tag)
	{
		switch (popDialog->getDataTag())
		{
		case MSG_BUY_BLANK_TAG:
		{
			buyLand(MSG_BUY_BLANK_TAG, buy_land_x, buy_land_y, foot1Sprite, player1_building_1_tiledID, player1, PLAYER1_1_PARTICLE_PLIST);
			log("need $1000");
			break;
		}
		case MSG_BUY_LAND_1_TAG: 
		{
			buyLand(MSG_BUY_LAND_1_TAG, buy_land_x, buy_land_y, starFish1Sprite, player1_building_2_tiledID, player1, PLAYER1_1_PARTICLE_PLIST);
			log("need $2000");
			break;
		}
		case MSG_BUY_LAND_2_TAG:
		{
			buyLand(MSG_BUY_LAND_2_TAG, buy_land_x, buy_land_y, heart1Sprite, player1_building_3_tiledID, player1, PLAYER1_1_PARTICLE_PLIST);
			log("need $3000");
			break;
		}
		default:
			break;
		}
	}
	popDialog->setVisible(false);
	Util::sendCustomEvent(RICHER_CONTROLLER_MSG, __String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
	//EventCustom _event = EventCustom(RICHER_CONTROLLER_MSG);
	//_event.setUserData(__String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
	//Director::getInstance()->getEventDispatcher()->dispatchEvent(&_event);
}

void GameBaseScene::doSomeForParticle()
{
	landFadeOut = FadeOut::create(0.1);
	landFadeIn = FadeIn::create(0.1);
	landFadeOut->retain();
	landFadeIn->retain();

	scaleby1ForBuyLand = ScaleBy::create(0.1, 1.5);
	scaleby2ForBuyLand = ScaleBy::create(0.5, 0.7);
	scaleby1ForBuyLand->retain();
	scaleby2ForBuyLand->retain();
	foot1Sprite = Sprite::create(PLAYER1_1_PARTICLE_PNG);
	addChild(foot1Sprite);
	foot1Sprite->setAnchorPoint(Vec2(0, 0));

	foot2Sprite = Sprite::create(PLAYER2_1_PARTICLE_PNG);
	addChild(foot2Sprite);
	foot2Sprite->setAnchorPoint(Vec2(0, 0));
}

void GameBaseScene::playParticle(Point point, char * plistName)
{
	ParticleSystem *particleSystem_foot = ParticleSystem::create(plistName);
	particleSystem_foot->retain();
	ParticleBatchNode *batch = ParticleBatchNode::createWithTexture(particleSystem_foot->getTexture());
	batch->addChild(particleSystem_foot);
	addChild(batch);

	particleSystem_foot->setPosition(point + Vec2(tiledWidth / 2, tiledHeight / 2));
	particleSystem_foot->release();
	particleSystem_foot->setAutoRemoveOnFinish(true);
}

void GameBaseScene::buyLand(int buyTag, float x, float y, Sprite * landSprite, int landLevel, RicherPlayer * player, char * particlelistName)
{
}

void GameBaseScene::refreshMoneyLabel(RicherPlayer * player, int money)
{
}

void GameBaseScene::payTolls(int payTag, float x, float y, int playerTag)
{
}

RicherPlayer * GameBaseScene::getPlayerByTiled(float x, float y)
{
	return nullptr;
}
