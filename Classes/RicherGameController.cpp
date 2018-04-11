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
		_richerPlayer->setIsMyTurn(false);
		pickOnePlayerToGo();
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
	NotificationCenter::getInstance()->postNotification(RICHER_MSG, String::createWithFormat("%d", MSG_GO_SHOW_TAG));
}
