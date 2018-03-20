#include "SplashScene.h"

Scene* SplashScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SplashScene::create();
	scene->addChild(layer);
	return scene;
}

bool SplashScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	initMoveSprite();
	scheduleOnce(schedule_selector(SplashScene::startMoveSprite), ONE_SECOND);
	return true;
}

void SplashScene::moveFu2SpriteToLeft()
{
	MoveBy *moveFu1ToLeft2 = MoveBy::create(MOVE_SPEED, Vec2(-spriteSize.width, 0));
	fu1_Sprite->runAction(moveFu1ToLeft2);
	
	MoveBy *fu2SpriteMoveBy = MoveBy::create(MOVE_SPEED, Vec2(spriteSize.width, 0));
	CallFunc *callFunc2 = CallFunc::create(CC_CALLBACK_0(SplashScene::moveWengSpriteToLeft, this));
	fu2_Sprite->runAction(Sequence::create(fu2SpriteMoveBy, callFunc2, NULL));
}

void SplashScene::moveWengSpriteToLeft()
{
	MoveBy *moveFu1ToLeft3 = MoveBy::create(MOVE_SPEED, Vec2(-spriteSize.width, 0));
	fu1_Sprite->runAction(moveFu1ToLeft3);

	MoveBy *wengSpriteMoveBy = MoveBy::create(MOVE_SPEED, Vec2(spriteSize.width, 0));
	CallFunc *callFunc3 = CallFunc::create(CC_CALLBACK_0(SplashScene::spriteFadeOut, this));
	weng_Sprite->runAction(Sequence::create(wengSpriteMoveBy, callFunc3, NULL));
}

void SplashScene::initMoveSprite()
{
	weng_Sprite = Sprite::create(WENG_IMAGE);
	fu2_Sprite = Sprite::create(FU2_IMAGE);
	po_Sprite = Sprite::create(PO_IMAGE);
	fu1_Sprite = Sprite::create(FU1_IMAGE);

	spriteSize = weng_Sprite->getContentSize();
	weng_Sprite->setPosition(Vec2(visibleSize.width / 2 - (2 * spriteSize.width), visibleSize.height / 2));
	fu2_Sprite->setPosition(Vec2(visibleSize.width / 2 - spriteSize.width, visibleSize.height / 2));
	po_Sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	fu1_Sprite->setPosition(Vec2(visibleSize.width / 2 + spriteSize.width, visibleSize.height / 2));

	weng_Sprite->setAnchorPoint(Vec2(0, 0.5));
	fu2_Sprite->setAnchorPoint(Vec2(0, 0.5));
	po_Sprite->setAnchorPoint(Vec2(0, 0.5));
	fu1_Sprite->setAnchorPoint(Vec2(0, 0.5));

	this->addChild(weng_Sprite);
	this->addChild(fu2_Sprite);
	this->addChild(po_Sprite);
	this->addChild(fu1_Sprite);
}

void SplashScene::startMoveSprite(float dt)
{
	MoveBy *moveFu1ToLeft1 = MoveBy::create(MOVE_SPEED, Vec2(-spriteSize.width, 0));
	fu1_Sprite->runAction(moveFu1ToLeft1);

	MoveBy *movePoToRight = MoveBy::create(MOVE_SPEED, Vec2(spriteSize.width, 0));
	CallFunc *callFunc = CallFunc::create(CC_CALLBACK_0(SplashScene::moveFu2SpriteToLeft, this));
	po_Sprite->runAction(Sequence::create(movePoToRight, callFunc, NULL));
}

void SplashScene::gotoMenuScene()
{
	log("goto MenuScene");
}

void SplashScene::spriteFadeOut()
{
	FadeOut *fadeOut1 = FadeOut::create(ONE_SECOND * 2);
	FadeOut *fadeOut2 = FadeOut::create(ONE_SECOND * 2);
	FadeOut *fadeOut3 = FadeOut::create(ONE_SECOND * 2);
	FadeOut *fadeOut4 = FadeOut::create(ONE_SECOND * 2);
	weng_Sprite->runAction(fadeOut1);
	fu2_Sprite->runAction(fadeOut2);
	po_Sprite->runAction(fadeOut3);


	CallFunc* callFunc4 = CallFunc::create(CC_CALLBACK_0(SplashScene::gotoMenuScene, this));
	fu1_Sprite->runAction(Sequence::create(fadeOut4, callFunc4, NULL));
}

