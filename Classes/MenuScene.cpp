#include "MenuScene.h"

Scene *MenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MenuScene::create();
	scene->addChild(layer);
	return scene;
}

bool MenuScene::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	addBackgroundSprite();
	addMenuSprites();

	return true;
}

//Menu����ص�����
void MenuScene::menuTouchDown(Object *pSender, Control::EventType event)
{
	log("single touched");
	ControlButton *button = (ControlButton *)pSender;
	int tag = button->getTag();

	switch (tag)
	{
	case Btn_Single_Game_TAG:
	{
		log("single game");
		break;
	}
	case Btn_Multi_Game_TAG:
	{
		log("multi game");
		break;
	}
	case Btn_Music_TAG:
	{
		bool music_on = UserDefault::getInstance()->getBoolForKey(MUSIC_ON_KEY, true);
		if (music_on)
		{
			UserDefault::getInstance()->setBoolForKey(MUSIC_ON_KEY, false);
			button->setTitleForState(MUSIC_OFF, Control::State::NORMAL);
		} else {
			UserDefault::getInstance()->setBoolForKey(MUSIC_ON_KEY, true);
			button->setTitleForState(MUSIC_ON, Control::State::NORMAL);
		}
		break;
	}
	case Btn_Quit_Game_TAG:
	{
		log("quit game");
		break;
	}
	case Btn_Load_Game_TAG:
	{
		log("load game");
		break;
	}
	default:
		break;
	}
}

//���ӳ�������
void MenuScene::addBackgroundSprite()
{
	Sprite *menuSpriteLogo = Sprite::create(MENU_LOGO);
	menuSpriteLogo->setPosition(Vec2(visibleSize.width / 2, visibleSize.height));
	menuSpriteLogo->setAnchorPoint(Vec2(0.5, 1));
	menuSpriteLogo->setScale(0.6f);
	addChild(menuSpriteLogo);

	Sprite *rainBowSprite = Sprite::create(RAINBOW);
	rainBowSprite->setPosition(Vec2(5, visibleSize.height - 20));
	rainBowSprite->setAnchorPoint(Vec2(0, 1));
	rainBowSprite->setScale(0.3f);
	addChild(rainBowSprite);

	MoveBy *rainBowMove = MoveBy::create(1, Vec2(8, 0));
	MoveBy *rainBowMoveReverse = rainBowMove->reverse();
	Sequence *rainBowAction = Sequence::create(rainBowMove, rainBowMoveReverse, NULL);
	rainBowSprite->runAction(RepeatForever::create(rainBowAction));
}

//����Menu����
void MenuScene::addMenuSprites()
{
	Scale9Sprite *btnNormal = Scale9Sprite::create(NORMAL_MENU);
	Scale9Sprite *btnPress = Scale9Sprite::create(PRESS_MENU);

	LabelTTF *singleGameTTF = LabelTTF::create(SINGLE_GAME, FONT_MENU, Btn_FontSize);
	ControlButton *singleGameBtn = ControlButton::create(singleGameTTF, btnNormal);

	//singleGameBtn->setBackgroundSpriteForState(btnPress, Control::State::HIGH_LIGHTED);
	singleGameBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 180));
	singleGameBtn->setPreferredSize(Size(Btn_Width, Btn_Height));
	singleGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	singleGameBtn->setTag(Btn_Single_Game_TAG);
	addChild(singleGameBtn);

	Scale9Sprite *btnNormal2 = Scale9Sprite::create(NORMAL_MENU);
	Scale9Sprite *btnPress2 = Scale9Sprite::create(PRESS_MENU);
	LabelTTF *multiGameTTF = LabelTTF::create(MULTI_GAME, FONT_MENU, Btn_FontSize);
	ControlButton *multiGameBtn = ControlButton::create(multiGameTTF, btnNormal2);
	multiGameBtn->setBackgroundSpriteForState(btnPress2, Control::State::HIGH_LIGHTED);

	multiGameBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 240));
	multiGameBtn->setPreferredSize(Size(Btn_Width, Btn_Height));
	multiGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	multiGameBtn->setTag(Btn_Multi_Game_TAG);
	addChild(multiGameBtn);

	Scale9Sprite *btnNormal3 = Scale9Sprite::create(NORMAL_MENU);
	Scale9Sprite *btnPress3 = Scale9Sprite::create(PRESS_MENU);

	bool music_on = UserDefault::getInstance()->getBoolForKey(MUSIC_ON_KEY, true);
	LabelTTF *settingsGameTTF;
	if (music_on)
	{
		settingsGameTTF = LabelTTF::create(MUSIC_ON, FONT_MENU, Btn_FontSize);
	}
	else
	{
		settingsGameTTF = LabelTTF::create(MUSIC_OFF, FONT_MENU, Btn_FontSize);
	}

	ControlButton *settingsGameBtn = ControlButton::create(settingsGameTTF, btnNormal3);
	settingsGameBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 300));
	settingsGameBtn->setPreferredSize(Size(Btn_Width, Btn_Height));
	settingsGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	settingsGameBtn->setTag(Btn_Music_TAG);
	addChild(settingsGameBtn);

	Scale9Sprite *btnNormal4 = Scale9Sprite::create(NORMAL_MENU);
	Scale9Sprite *btnPress4 = Scale9Sprite::create(PRESS_MENU);
	LabelTTF *loadGameTTF = LabelTTF::create(LOAD_GAME, FONT_MENU, Btn_FontSize);
	ControlButton *loadGameBtn = ControlButton::create(loadGameTTF, btnNormal4);

	loadGameBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 360));
	loadGameBtn->setPreferredSize(Size(Btn_Width, Btn_Height));
	loadGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	loadGameBtn->setTag(Btn_Load_Game_TAG);
	addChild(loadGameBtn);

	Scale9Sprite *btnNormal5 = Scale9Sprite::create(NORMAL_MENU);
	Scale9Sprite *btnPress5 = Scale9Sprite::create(PRESS_MENU);
	LabelTTF *quitGameTTF = LabelTTF::create(QUIT_GAME, FONT_MENU, Btn_FontSize);
	ControlButton *quitGameBtn = ControlButton::create(quitGameTTF, btnNormal5);

	quitGameBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 420));
	quitGameBtn->setPreferredSize(Size(Btn_Width, Btn_Height));
	quitGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	quitGameBtn->setTag(Btn_Quit_Game_TAG);
	addChild(quitGameBtn);
}