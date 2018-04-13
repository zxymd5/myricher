#include "PopupLayer.h"
#include "ConstUtil.h"

bool PopupLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	m__pMenu = NULL;
	m_callbackListener = NULL;
	m_callback = NULL;
	m__sfBackGround = NULL;
	m__s9BackGround = NULL;
	m__ltContentText = NULL;
	m__ltTitle = NULL;
	this->setContentSize(Size::ZERO);

	Menu *menu = Menu::create();
	menu->setPosition(Point::ZERO);
	setMenuButton(menu);

	return true;
}

void PopupLayer::setPopModalDialog(bool mD)
{
	if (mD)
	{
		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);

		listener->onTouchBegan = [](Touch *t, Event *e) {
			log("PopupLayer touch");
			return true;
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	}
}

PopupLayer * PopupLayer::create(const char *backgroundImage)
{
	PopupLayer *ml = PopupLayer::create();
	ml->setSprite9BackGround(cocos2d::ui::Scale9Sprite::create(backgroundImage));
	return ml;
}

void PopupLayer::setPopType(POP_TYPE type)
{
	pop_type = type;
}

void PopupLayer::setTitle(const char *title, int fontSize /*= Pop_FontSize*/)
{
	Label *ltfTitle = Label::createWithTTF(title, "fonts/Marker Felt.ttf", fontSize);
	setLabelTitle(ltfTitle);
}

void PopupLayer::setContentText(const char *text, int fontSize /*= Pop_FontSize*/, int padding /*= 50*/, int paddingTop /*= 100*/)
{
	Label *ltf = Label::createWithTTF(text, "fonts/Marker Felt.ttf", fontSize);
	setLabelContentText(ltf);
	m_contentPadding = padding;
	m_contentPaddingTop = paddingTop;
}

void PopupLayer::setCallbackFunc(Ref *target, SEL_CallFuncN callfun)
{
	m_callbackListener = target;
	m_callback = callfun;
}

bool PopupLayer::addButton(const char *normalImage, const char *selectImage, const char *title, int tag /*= 0*/)
{
	Size winSize = Director::getInstance()->getWinSize();
	Point pCenter = Vec2(winSize.width / 2, winSize.height / 2);
	
	MenuItemImage *menuImage = MenuItemImage::create(normalImage, selectImage, CC_CALLBACK_1(PopupLayer::buttonCallback, this));
	menuImage->setTag(tag);
	menuImage->setPosition(pCenter);
	
	Size imenu = menuImage->getContentSize();
	Label *ttf = Label::createWithTTF(title, FONT_MENU, 20);
	ttf->setColor(Color3B(0, 0, 0));
	ttf->setPosition(Vec2(imenu.width / 2, imenu.height / 2));
	menuImage->addChild(ttf);

	getMenuButton()->addChild(menuImage);
	return true;
}

void PopupLayer::onEnter()
{
	Layer::onEnter();
	Size winSize = Director::getInstance()->getWinSize();
	Point pCenter = Vec2(winSize.width / 2, winSize.height / 2);
	Size contentSize;
	Scale9Sprite *background = getSprite9BackGround();
	background->setContentSize(getContentSize());
	background->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(background, 0, 0);
	contentSize = getContentSize();

	this->addChild(getMenuButton());
	float btnWidth = contentSize.width / (getMenuButton()->getChildrenCount() + 1);
	Vector<Node *> vecArray = getMenuButton()->getChildren();

	int j = 0;
	for (auto it = vecArray.begin(); it != vecArray.end(); it++)
	{
		Node *node = dynamic_cast<Node *>(*it);
		node->setPosition(Point(winSize.width / 2 - contentSize.width / 2 + btnWidth * (j + 1),
			winSize.height / 2 - contentSize.height / 3));
		j++;
	}

	if (getLabelTitle())
	{
		getLabelTitle()->setPosition(pCenter + Vec2(0, contentSize.height / 2 - 20));
		getLabelTitle()->setColor(Color3B(0, 0, 0));
		this->addChild(getLabelTitle());
	}

	switch (pop_type)
	{
	default:
	{
		if (getLabelContentText())
		{
			Label *ltf = getLabelContentText();
			ltf->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
			ltf->setDimensions(contentSize.width - m_contentPadding * 2, contentSize.height - m_contentPaddingTop);
			ltf->setHorizontalAlignment(TextHAlignment::LEFT);
			ltf->setColor(Color3B(0, 0, 0));
			this->addChild(ltf);
		}
	}
	break;
	}

	Action *popupLayer = Sequence::create(ScaleTo::create(0.0, 0.0), 
										  ScaleTo::create(0.15, 1.05),
										  ScaleTo::create(0.08, 0.95),
										 ScaleTo::create(0.08, 1.0),
										NULL);
	this->runAction(popupLayer);
}

void PopupLayer::onExit()
{
	Layer::onExit();
	log("popup on exit");
	CC_SAFE_RELEASE(m__pMenu);
	CC_SAFE_RELEASE(m__sfBackGround);
	CC_SAFE_RELEASE(m__ltContentText);
	CC_SAFE_RELEASE(m__ltTitle);
	CC_SAFE_RELEASE(m__s9BackGround);
}

void PopupLayer::buttonCallback(Ref *pSender)
{
	Node *node = dynamic_cast<Node *>(pSender);
	log("touch tag: %d", node->getTag());
	if (m_callback && m_callbackListener)
	{
		(m_callbackListener->*m_callback)(node);
	}
}