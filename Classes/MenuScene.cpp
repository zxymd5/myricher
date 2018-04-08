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

//Menu点击回调方法
void MenuScene::menuTouchDown(Ref *pSender, Control::EventType event)
{
	log("single touched");
	ControlButton *button = (ControlButton *)pSender;
	int tag = button->getTag();

	switch (tag)
	{
	case Btn_Single_Game_TAG:
	{
		log("single game");
		Director::getInstance()->pushScene(MapChooseScene::createScene());
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
		popupQuitLayer();
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

//添加场景背景
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

//添加Menu方法
void MenuScene::addMenuSprites()
{
	cocos2d::ui::Scale9Sprite *btnNormal = cocos2d::ui::Scale9Sprite::create(NORMAL_MENU);
	cocos2d::ui::Scale9Sprite *btnPress = cocos2d::ui::Scale9Sprite::create(PRESS_MENU);

	Label *singleGameTTF = Label::createWithTTF(SINGLE_GAME, FONT_MENU, Btn_FontSize);
	ControlButton *singleGameBtn = ControlButton::create(singleGameTTF, btnNormal);

	//singleGameBtn->setBackgroundSpriteForState(btnPress, Control::State::HIGH_LIGHTED);
	singleGameBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 180));
	singleGameBtn->setPreferredSize(Size(Btn_Width, Btn_Height));
	singleGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	singleGameBtn->setTag(Btn_Single_Game_TAG);
	addChild(singleGameBtn);

	cocos2d::ui::Scale9Sprite *btnNormal2 = cocos2d::ui::Scale9Sprite::create(NORMAL_MENU);
	cocos2d::ui::Scale9Sprite *btnPress2 = cocos2d::ui::Scale9Sprite::create(PRESS_MENU);
	Label *multiGameTTF = Label::createWithTTF(MULTI_GAME, FONT_MENU, Btn_FontSize);
	ControlButton *multiGameBtn = ControlButton::create(multiGameTTF, btnNormal2);
	multiGameBtn->setBackgroundSpriteForState(btnPress2, Control::State::HIGH_LIGHTED);

	multiGameBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 240));
	multiGameBtn->setPreferredSize(Size(Btn_Width, Btn_Height));
	multiGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	multiGameBtn->setTag(Btn_Multi_Game_TAG);
	addChild(multiGameBtn);

	cocos2d::ui::Scale9Sprite *btnNormal3 = cocos2d::ui::Scale9Sprite::create(NORMAL_MENU);
	cocos2d::ui::Scale9Sprite *btnPress3 = cocos2d::ui::Scale9Sprite::create(PRESS_MENU);

	bool music_on = UserDefault::getInstance()->getBoolForKey(MUSIC_ON_KEY, true);
	Label *settingsGameTTF;
	if (music_on)
	{
		settingsGameTTF = Label::createWithTTF(MUSIC_ON, FONT_MENU, Btn_FontSize);
	}
	else
	{
		settingsGameTTF = Label::createWithTTF(MUSIC_OFF, FONT_MENU, Btn_FontSize);
	}

	ControlButton *settingsGameBtn = ControlButton::create(settingsGameTTF, btnNormal3);
	settingsGameBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 300));
	settingsGameBtn->setPreferredSize(Size(Btn_Width, Btn_Height));
	settingsGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	settingsGameBtn->setTag(Btn_Music_TAG);
	addChild(settingsGameBtn);

	cocos2d::ui::Scale9Sprite *btnNormal4 = cocos2d::ui::Scale9Sprite::create(NORMAL_MENU);
	cocos2d::ui::Scale9Sprite *btnPress4 = cocos2d::ui::Scale9Sprite::create(PRESS_MENU);
	Label *loadGameTTF = Label::createWithTTF(LOAD_GAME, FONT_MENU, Btn_FontSize);
	ControlButton *loadGameBtn = ControlButton::create(loadGameTTF, btnNormal4);

	loadGameBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 360));
	loadGameBtn->setPreferredSize(Size(Btn_Width, Btn_Height));
	loadGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	loadGameBtn->setTag(Btn_Load_Game_TAG);
	addChild(loadGameBtn);

	cocos2d::ui::Scale9Sprite *btnNormal5 = cocos2d::ui::Scale9Sprite::create(NORMAL_MENU);
	cocos2d::ui::Scale9Sprite *btnPress5 = cocos2d::ui::Scale9Sprite::create(PRESS_MENU);
	Label *quitGameTTF = Label::createWithTTF(QUIT_GAME, FONT_MENU, Btn_FontSize);
	ControlButton *quitGameBtn = ControlButton::create(quitGameTTF, btnNormal5);

	quitGameBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 420));
	quitGameBtn->setPreferredSize(Size(Btn_Width, Btn_Height));
	quitGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	quitGameBtn->setTag(Btn_Quit_Game_TAG);
	addChild(quitGameBtn);
}

void MenuScene::popupQuitLayer()
{
	PopupLayer *popDialog = PopupLayer::create(DIALOG_BG);
	popDialog->setContentSize(Size(Quit_Dialog_Size_Width, Quit_Dialog_Size_Height));
	popDialog->setTitle(DIALOG_TITLE);
	popDialog->setContentText(DIALOG_CONTENT, 20, 60, 250);
	popDialog->setCallbackFunc(this, callfuncN_selector(MenuScene::quitButtonCallback));
	popDialog->addButton(BUTTON_BG1, BUTTON_BG3, OK, Btn_Quit_OK_TAG);
	popDialog->addButton(BUTTON_BG2, BUTTON_BG3, CANCEL, Btn_Quit_Cancel_TAG);
	this->addChild(popDialog);
}

void MenuScene::quitButtonCallback(Node *pNode)
{
	if (pNode->getTag() == Btn_Quit_OK_TAG)
	{
		Director::getInstance()->end();
	}
	else
	{
		pNode->getParent()->getParent()->removeFromParent();
	}
}
