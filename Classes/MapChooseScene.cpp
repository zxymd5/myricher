#include "MapChooseScene.h"

USING_NS_CC;

Scene *MapChooseScene::createScene() {
	auto scene = Scene::create();
	auto layer = MapChooseScene::create();
	scene->addChild(layer);
	return scene;
}

bool MapChooseScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	currentPage = 1;
	addBackgroundSprite();
	addScrollView();
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(MapChooseScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MapChooseScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(MapChooseScene::onTouchEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	Menu *menu = Menu::create();
	addChild(menu);

	MenuItem *backItem = MenuItemImage::create(BACK_NORMAL, BACK_PRESSED, this, 
						menu_selector(MapChooseScene::back));
	menu->addChild(backItem);

	backItem->setPosition(Vec2(visibleSize.width / 2 - backItem->getContentSize().width / 2, 
						backItem->getContentSize().height / 2 - visibleSize.height / 2));

	return true;
}

void MapChooseScene::back(Ref *)
{
	Director::getInstance()->popScene();
}

void MapChooseScene::addScrollView()
{
	Point center = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	_spriteContainer = Layer::create();

	Sprite *map1Sprite = Sprite::create(MAP_1);
	Sprite *map2Sprite = Sprite::create(MAP_2);
	Sprite *map3Sprite = Sprite::create(MAP_3);

	_spriteContainer->addChild(map1Sprite);
	map1Sprite->setPosition(center);

	_spriteContainer->addChild(map2Sprite);
	map2Sprite->setPosition(center + Vec2(visibleSize.width, 0));

	_spriteContainer->addChild(map3Sprite);
	map3Sprite->setPosition(center + Vec2(2 * visibleSize.width, 0));

	_spriteContainer->setPosition(Point::ZERO);
	_spriteContainer->setContentSize(Size(visibleSize.width * MAP_COUNT, visibleSize.height));

	scrollView = ScrollView::create();
	scrollView->setContainer(_spriteContainer);
	scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
	scrollView->setTouchEnabled(true);
	scrollView->setPosition(Point::ZERO);

	scrollView->setViewSize(visibleSize);
	scrollView->setContentOffset(Point::ZERO, true);
	scrollView->setContentSize(Size(visibleSize.width * MAP_COUNT, visibleSize.height));
	scrollView->setDelegate(this);
	scrollView->setBounceable(false);
	addChild(scrollView);
}

bool MapChooseScene::onTouchBegan(Touch * touch, Event * unused_event)
{
	beginTouchPoint = Director::getInstance()->convertToGL(touch->getLocationInView());
	log("touch began");
	return true;
}

void MapChooseScene::onTouchMoved(Touch * touch, Event * unused_event)
{
	log("Touch moved");
}

void MapChooseScene::onTouchEnded(Touch * touch, Event * unused_event)
{
	Point endPoint = Director::getInstance()->convertToGL(touch->getLocationInView());
	float distance = endPoint.x - beginTouchPoint.x;
	if (fabs(distance) > TOUCH_DISTANCE)
	{
		adjustScrollView(distance);
	}
	else {
		if (currentPage == 1)
		{
		}
		if (currentPage == 2)
		{
		}
		if (currentPage == 3)
		{
		}
	}
}

void MapChooseScene::adjustScrollView(float offset)
{
	if (offset < 0)
	{
		currentPage++;
	}
	else
	{
		currentPage--;
	}

	if (currentPage < 1)
	{
		currentPage = 1;
	}
	if (currentPage > MAP_COUNT)
	{
		currentPage = MAP_COUNT;
	}

	Point adjustPos = Vec2(-visibleSize.width * (currentPage - 1), 0);
	scrollView->setContentOffset(adjustPos, true);
}

void MapChooseScene::scrollViewDidScroll(ScrollView * view)
{
}

void MapChooseScene::addBackgroundSprite()
{
	Sprite *stage_bg = Sprite::create(STAGE_BACKGROUND);
	stage_bg->setPosition(Point::ZERO);
	stage_bg->setAnchorPoint(Point::ZERO);
	addChild(stage_bg);
}

void MapChooseScene::singleTouchDown(Ref *pSender, Control::EventType event)
{

}

void MapChooseScene::scrollViewDidZoom(ScrollView * view)
{
}

void MapChooseScene::scrollViewMoveOver(ScrollView * view)
{
}
