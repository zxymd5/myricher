#ifndef __Richer_PopupLayer__
#define __Richer_PopupLayer__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::ui;
const int Pop_FontSize = 20;

enum POP_TYPE
{
	NORMAL,
};

class PopupLayer : public Layer 
{
public:
	virtual bool init();
	CREATE_FUNC(PopupLayer);
	POP_TYPE pop_type;
	void setPopType(POP_TYPE type);
	static PopupLayer *create(const char *backgroundImage);
	void setTitle(const char *title, int fontSize = Pop_FontSize);
	void setContentText(const char *text, int fontSize = Pop_FontSize, int padding = 50, int paddingTop = 100);
	void setCallbackFunc(Ref *target, SEL_CallFuncN callfun);
	bool addButton(const char *normalImage, const char *selectImage, const char *title, int tag = 0);
	virtual void onEnter();
	virtual void onExit();

private:
	void buttonCallback(Ref *pSender);
	int m_contentPadding = 0;
	int m_contentPaddingTop = 0;
	Ref *m_callbackListener;
	SEL_CallFuncN m_callback;
	CC_SYNTHESIZE_RETAIN(Menu *, m__pMenu, MenuButton);
	CC_SYNTHESIZE_RETAIN(Sprite *, m__sfBackGround, SpriteBackGround);
	CC_SYNTHESIZE_RETAIN(Scale9Sprite *, m__s9BackGround, Sprite9BackGround);
	CC_SYNTHESIZE_RETAIN(Label *, m__ltTitle, LabelTitle);
	CC_SYNTHESIZE_RETAIN(Label *, m__ltContentText, LabelContentText);
};

#endif
