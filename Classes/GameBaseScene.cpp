#include "GameBaseScene.h"

Scene * GameBaseScene::createScene()
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
	addPlayer();
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

	Label *player_1_money = Label::createWithTTF("$", FONT_MENU, 25);
	player_1_money->setAnchorPoint(Vec2(0, 0.5));
	player_1_money->setPosition(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight / 2);
	addChild(player_1_money);

	Label *player_1_strength = Label::createWithTTF("+", FONT_MENU, 28);
	player_1_strength->setAnchorPoint(Vec2(0, 0.5));
	player_1_strength->setPosition(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight / 2 * 3);
	addChild(player_1_strength);

	Sprite *player_2 = Sprite::create(PLAYER_2);
	player_2->setPosition(tableStartPosition_x + tableWidth / 2, tableStartPosition_y - 3 * tableHeight);
	addChild(player_2);

	Label *player_2_money = Label::createWithTTF("$", FONT_MENU, 25);
	player_2_money->setAnchorPoint(Vec2(0, 0.5));
	player_2_money->setPosition(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight / 2 * 5);
	addChild(player_2_money);

	Label *player_2_strength = Label::createWithTTF("+", FONT_MENU, 28);
	player_2_strength->setAnchorPoint(Vec2(0, 0.5));
	player_2_strength->setPosition(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight / 2 * 7);
	addChild(player_2_strength);
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
