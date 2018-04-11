#include "Map3Scene.h"

Scene * Map3Scene::createScene()
{
	auto scene = Scene::create();
	auto layer = Map3Scene::create();
	scene->addChild(layer);
	return scene;
}

void Map3Scene::addMap()
{
	_map = TMXTiledMap::create("map/map_3.tmx");
	addChild(_map);
}

bool Map3Scene::init()
{
	addMap();
	initTiledGrid();
	if (!GameBaseScene::init())
	{
		return false;
	}
	return true;
}

void Map3Scene::initTiledGrid()
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
