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
	if (!GameBaseScene::init())
	{
		return false;
	}
	return true;
}
