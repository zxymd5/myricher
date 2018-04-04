#include "Map2Scene.h"

cocos2d::Scene * Map2Scene::createScene()
{
	auto scene = Scene::create();
	auto layer = Map2Scene::create();
	scene->addChild(layer);
	return scene;
}

void Map2Scene::addMap()
{
	_map = TMXTiledMap::create("map/map_2.tmx");
	addChild(_map);
}

void Map2Scene::initTiledGrid()
{
	tiledColsCount = 21;
	tiledRowsCount = 15;
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

bool Map2Scene::init()
{
	addMap();
	initTiledGrid();
	if (!GameBaseScene::init())
	{
		return false;
	}
	return true;
}
