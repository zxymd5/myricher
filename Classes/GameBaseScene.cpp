#include "GameBaseScene.h"

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
	addPlayer();
	return true;
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

	LabelTTF *player_1_money = LabelTTF::create();
	player_1_money->setString("$");
	player_1_money->setAnchorPoint(Vec2(0, 0.5));
	player_1_money->setFontSize(25);
	player_1_money->setPosition(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight / 2);
	addChild(player_1_money);

	LabelTTF *player_1_strength = LabelTTF::create();
	player_1_strength->setString("+");
	player_1_strength->setAnchorPoint(Vec2(0, 0.5));
	player_1_strength->setFontSize(28);
	player_1_strength->setPosition(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight / 2 * 3);
	addChild(player_1_strength);

	Sprite *player_2 = Sprite::create(PLAYER_2);
	player_2->setPosition(tableStartPosition_x + tableWidth / 2, tableStartPosition_y - 3 * tableHeight);
	addChild(player_2);

	LabelTTF *player_2_money = LabelTTF::create();
	player_2_money->setString("$");
	player_2_money->setAnchorPoint(Vec2(0, 0.5));
	player_2_money->setFontSize(25);
	player_2_money->setPosition(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight / 2 * 5);
	addChild(player_2_money);

	LabelTTF *player_2_strength = LabelTTF::create();
	player_2_strength->setString("+");
	player_2_strength->setAnchorPoint(Vec2(0, 0.5));
	player_2_strength->setFontSize(28);
	player_2_strength->setPosition(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight / 2 * 7);
	addChild(player_2_strength);
}

void GameBaseScene::addRightBanner()
{
	Sprite *rightBanner = Sprite::create(RIGHT_BANNER);
	rightBanner->setAnchorPoint(Vec2(0, 0));
	rightBanner->setPosition(Vec2(tableStartPosition_x, 0));
	addChild(rightBanner);
}
