#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "cocos2d.h"
#include "ConstUtil.h"

USING_NS_CC;

const double MOVE_SPEED = 0.5f;
const int ONE_SECOND = 1;

class SplashScene : public Layer {
public:
	static Scene* createScene();
	virtual bool init();

	void moveFu2SpriteToLeft();
	void moveWengSpriteToLeft();
	void initMoveSprite();
	void startMoveSprite(float dt);
	void gotoMenuScene();
	void spriteFadeOut();
	CREATE_FUNC(SplashScene);

private:
	Sprite *weng_Sprite;
	Sprite *fu2_Sprite;
	Sprite *po_Sprite;
	Sprite *fu1_Sprite;
	Size visibleSize;
	Size spriteSize;
};

#endif
