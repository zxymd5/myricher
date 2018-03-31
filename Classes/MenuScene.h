#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ConstUtil.h"
#include "popupLayer/PopupLayer.h"
#include "MapChooseScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

const int Btn_Width = 222;
const int Btn_Height = 50;
const int Btn_FontSize = 20;
const int Quit_Dialog_Size_Width = 400;
const int Quit_Dialog_Size_Height = 220;
const int Btn_Single_Game_TAG = 10001;
const int Btn_Multi_Game_TAG = 10002;
const int Btn_Music_TAG = 10003;
const int Btn_Quit_Game_TAG = 10004;
const int Btn_Quit_OK_TAG = 10005;
const int Btn_Quit_Cancel_TAG = 10006;
const int Btn_Load_Game_TAG = 10007;

class MenuScene : public LayerColor
{
public:
	static Scene *createScene();
	virtual bool init();
	CREATE_FUNC(MenuScene);

private:
	Size visibleSize;
	void menuTouchDown(Ref *pSender, Control::EventType event);
	void addBackgroundSprite();
	void addMenuSprites();
	void popupQuitLayer();
	void quitButtonCallback(Node *pNode);
};


#endif // !__MENU_SCENE_H__
