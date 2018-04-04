#include "Map1Scene.h"

cocos2d::Scene * Map1Scene::createScene()
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

void Map1Scene::initTiledGrid()
{
	tiledColsCount = 21;
	tiledRowsCount = 16;
	canPassGrid = new bool *[tiledRowsCount];
	for (int i = 0; i < tiledRowsCount; i++)
	{
		canPassGrid[i] = new bool [tiledColsCount];
	}

	for (int row = 0; row < tiledRowsCount; row++)
	{
		for (int col = 0; col < tiledColsCount; col++)
		{
			canPassGrid[row][col] = false;
		}
	}
}

bool Map1Scene::init()
{
	addMap();
	initTiledGrid();
	if (!GameBaseScene::init())
	{
		return false;
	}
	return true;
}
