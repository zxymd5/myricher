#include "Map1Scene.h"

Scene * Map1Scene::createScene()
{
	auto scene = Scene::create();
	auto layer = Map1Scene::create();
	scene->addChild(layer);
	return scene;
}

void Map1Scene::addMap()
{
	_map = TMXTiledMap::create("map/map_1.tmx");
	addChild(_map);
}

bool Map1Scene::init()
{
	addMap();
	initTiledGrid();
	initPropTiledID();
	if (!GameBaseScene::init())
	{
		return false;
	}
	return true;
}

void Map1Scene::initTiledGrid()
{
	tiledColsCount = 21;
	tiledRowsCount = 16;
	canPassGrid = new bool *[tiledRowsCount];
	for (int i = 0; i < tiledRowsCount; i++)
	{
		canPassGrid[i] = new bool[tiledColsCount];
	}

	for (int row = 0; row < tiledRowsCount; row++)
	{
		for (int col = 0; col < tiledColsCount; col++)
		{
			canPassGrid[row][col] = false;
		}
	}
}

void Map1Scene::initPropTiledID()
{
	blank_land_tiledID = 1;
	strength_30_tiledID = 4;
	strength_50_tiledID = 5;
	strength_80_tiledID = 6;

	randomEvent_tiledID = 7;
	lottery_tiledID = 8;
	stock_tiledID = 9;

	player1_building_1_tiledID = 13;
	player1_building_2_tiledID = 14;
	player1_building_3_tiledID = 15;

	player2_building_1_tiledID = 10;
	player2_building_2_tiledID = 11;
	player2_building_3_tiledID = 12;
}
