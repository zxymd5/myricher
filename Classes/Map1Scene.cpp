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

bool Map1Scene::init()
{
	addMap();
	if (!GameBaseScene::init())
	{
		return false;
	}
	return true;
}
