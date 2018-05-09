#include "RicherGameController.h"
#include "GameBaseScene.h"

RicherGameController * RicherGameController::richerGameController_Instance = NULL;

bool RicherGameController::init()
{
	if (!Layer::init())
	{
		return false;
	}
	callEndGoFunc = CallFunc::create(CC_CALLBACK_0(RicherGameController::endGo, this));
	registerNotificationObserver();

	positionAroundEnd = new float *[4];
	for (int i = 0; i < 4; i++)
	{
		positionAroundEnd[i] = new float[2];
	}
	return true;
}

RicherGameController * RicherGameController::getInstance()
{
	if (!richerGameController_Instance)
	{
		richerGameController_Instance = RicherGameController::create();
	}
	richerGameController_Instance->retain();
	return richerGameController_Instance;
}

RicherGameController::~RicherGameController()
{
	spawnAction->release();
}

void RicherGameController::moveOneStep(RicherPlayer * richerPlayer)
{
	nextRow = _rowVector[stepHasGone + 1];
	nextCol = _colVector[stepHasGone + 1];

	int distanceRow = nextRow - currentRow;
	int distanceCol = nextCol - currentCol;

	if (distanceRow > 0)
	{
		moveBy = MoveBy::create(playerGoTotalTime, Vec2(0, tiledHeight));
		repeat = Repeat::create(richerPlayer->getUp(), 1);
	}
	if (distanceRow < 0)
	{
		moveBy = MoveBy::create(playerGoTotalTime, Vec2(0, -tiledHeight));
		repeat = Repeat::create(richerPlayer->getDown(), 1);
	}
	if (distanceCol > 0)
	{
		moveBy = MoveBy::create(playerGoTotalTime, Vec2(tiledWidth, 0));
		repeat = Repeat::create(richerPlayer->getRight(), 1);
	}
	if (distanceCol < 0)
	{
		moveBy = MoveBy::create(playerGoTotalTime, Vec2(-tiledWidth, 0));
		repeat = Repeat::create(richerPlayer->getLeft(), 1);
	}

	spawnAction = Sequence::create(Spawn::create(moveBy, repeat, NULL), callEndGoFunc, NULL);
	spawnAction->retain();
	richerPlayer->runAction(spawnAction);
}

void RicherGameController::startRealGo(std::vector<int> rowVector, std::vector<int> colVector, RicherPlayer * richerPlayer)
{
	currentRow = rowVector[0];
	currentCol = colVector[0];
	nextRow = 0;
	nextCol = 0;

	_rowVector = rowVector;
	_colVector = colVector;
	_richerPlayer = richerPlayer;
	isAnimFinished = false;
	stepHasGone = 0;
	stepsCount = _rowVector.size() - 1;
	moveOneStep(richerPlayer);
}

void RicherGameController::endGo()
{
	GameBaseScene::pathMarkVector.at(stepHasGone)->setVisible(false);
	stepHasGone++;
	if (stepHasGone >= stepsCount)
	{
		//_richerPlayer->setIsMyTurn(false);
		//pickOnePlayerToGo();
		handlePropEvent();
		return;
	}
	currentRow = nextRow;
	currentCol = nextCol;
	moveOneStep(_richerPlayer);
	log("go end");
}

void RicherGameController::pickOnePlayerToGo()
{
	for (auto it = GameBaseScene::players_vector.begin(); it != GameBaseScene::players_vector.end(); it++)
	{
		RicherPlayer *richerPlayer = dynamic_cast<RicherPlayer*>(*it);
		if (richerPlayer->getIsMyTurn())
		{
			int randNumber = rand() % 6 + 1;
			RouteNavigation::getInstance()->getPath(richerPlayer, randNumber, GameBaseScene::canPassGrid, GameBaseScene::tiledRowsCount, GameBaseScene::tiledColsCount);
			richerPlayer->startGo(RouteNavigation::getInstance()->getPathRows_vector(), RouteNavigation::getInstance()->getPathCols_vector());
			return;
		}
	}

	for (auto it = GameBaseScene::players_vector.begin(); it != GameBaseScene::players_vector.end(); it++)
	{
		RicherPlayer *richerPlayer = dynamic_cast<RicherPlayer *>(*it);
		richerPlayer->setIsMyTurn(true);
	}
	//NotificationCenter::getInstance()->postNotification(RICHER_MSG, String::createWithFormat("%d", MSG_GO_SHOW_TAG));
	//auto dispatcher = Director::getInstance()->getEventDispatcher();
	//EventCustom _event = EventCustom(RICHER_MSG);
	//_event.setUserData(__String::createWithFormat("%d", MSG_GO_SHOW_TAG));
	//dispatcher->dispatchEvent(&_event);
	Util::sendCustomEvent(RICHER_MSG, __String::createWithFormat("%d", MSG_GO_SHOW_TAG));
}

void RicherGameController::handlePropEvent()
{
	float playerEnd_X = _colVector[stepsCount] * 32;
	float playerEnd_Y = _rowVector[stepsCount] * 32 + 32;

	// up
	positionAroundEnd[0][0] = playerEnd_X;
	positionAroundEnd[0][1] = playerEnd_Y + 32;

	// down
	positionAroundEnd[1][0] = playerEnd_X;
	positionAroundEnd[1][1] = playerEnd_Y - 32;

	// left
	positionAroundEnd[2][0] = playerEnd_X - 32;
	positionAroundEnd[2][1] = playerEnd_Y;

	// right
	positionAroundEnd[3][0] = playerEnd_X + 32;
	positionAroundEnd[3][1] = playerEnd_Y;

	log("handlePropEvent() called");

	for (int i = 0; i < 4; i++)
	{
		Point ptMap = Util::GL2map(Vec2(positionAroundEnd[i][0], positionAroundEnd[i][1]), GameBaseScene::_map);
		int titleId = GameBaseScene::landLayer->getTileGIDAt(ptMap);
		int x = ptMap.x;
		int y = ptMap.y;

		if (titleId == GameBaseScene::blank_land_tiledID)
		{
			__String *str = __String::createWithFormat("%d-%d-%d-%d", MSG_BUY_BLANK_TAG, x, y, _richerPlayer->getTag());
			Util::sendCustomEvent(RICHER_MSG, str);
			//auto dispatcher = Director::getInstance()->getEventDispatcher();
			//EventCustom _event = EventCustom(RICHER_MSG);
			//_event.setUserData(__String::createWithFormat("%d-%d-%d-%d", MSG_BUY_BLANK_TAG, x, y, _richerPlayer->getTag()));
			//dispatcher->dispatchEvent(&_event);
			break;
		}

		if (titleId == GameBaseScene::player1_building_1_tiledID)
		{
			if (_richerPlayer->getTag() == PLAYER_1_TAG)
			{
				__String *str = __String::createWithFormat("%d-%d-%d-%d", MSG_BUY_LAND_1_TAG, x, y, _richerPlayer->getTag());
				Util::sendCustomEvent(RICHER_MSG, str);
			}
			break;
		}

		if (titleId == GameBaseScene::player1_building_2_tiledID)
		{
			if (_richerPlayer->getTag() == PLAYER_1_TAG)
			{
				__String *str = __String::createWithFormat("%d-%d-%d-%d", MSG_BUY_LAND_2_TAG, x, y, _richerPlayer->getTag());
				Util::sendCustomEvent(RICHER_MSG, str);
			}
			break;
		}

		if (titleId == GameBaseScene::player1_building_3_tiledID)
		{
			Util::sendCustomEvent(RICHER_CONTROLLER_MSG, __String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
			break;
		}

		if (titleId == GameBaseScene::player2_building_1_tiledID)
		{
			if (_richerPlayer->getTag() == PLAYER_2_TAG)
			{
				__String *str = __String::createWithFormat("%d-%d-%d-%d", MSG_BUY_LAND_1_TAG, x, y, _richerPlayer->getTag());
				Util::sendCustomEvent(RICHER_MSG, str);
			}
			break;
		}

		if (titleId == GameBaseScene::player2_building_2_tiledID)
		{
			if (_richerPlayer->getTag() == PLAYER_2_TAG)
			{
				__String *str = __String::createWithFormat("%d-%d-%d-%d", MSG_BUY_LAND_2_TAG, x, y, _richerPlayer->getTag());
				Util::sendCustomEvent(RICHER_MSG, str);
			}
			break;
		}

		if (titleId == GameBaseScene::player2_building_3_tiledID)
		{
			Util::sendCustomEvent(RICHER_CONTROLLER_MSG, __String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
			break;
		}
	}
}

void RicherGameController::registerNotificationObserver()
{
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	controllerCustomListener = EventListenerCustom::create(RICHER_MSG, CC_CALLBACK_1(RicherGameController::receivedMsg, this));
	dispatcher->addEventListenerWithFixedPriority(controllerCustomListener, 1);
}

void RicherGameController::receivedMsg(EventCustom * event)
{
	__String *srcDate = (__String*)event->getUserData();
	int retMsgType = srcDate->intValue();
	if (retMsgType == MSG_PICKONE_TOGO_TAG)
	{
		pickOnePlayerToGo();
	}
}
