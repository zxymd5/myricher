#include "Map2Scene.h"

Scene * Map2Scene::createScene()
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

bool Map2Scene::init()
{
	addMap();
	if (!GameBaseScene::init())
	{
		return false;
	}
	return true;
}
