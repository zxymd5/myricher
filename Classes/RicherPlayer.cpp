#include "RicherPlayer.h"

RicherPlayer::RicherPlayer()
{
	_comeFromeRow = -1;
	_comeFromCol = -1;
}

RicherPlayer::~RicherPlayer()
{

}

RicherPlayer * RicherPlayer::create(char *name, int tag, int money /*= 50000*/, int strength /*= 100*/)
{
	RicherPlayer *player = new RicherPlayer();
	player->init(name, tag, money, strength);
	player->autorelease();
	return player;
}

bool RicherPlayer::init(char *name, int tag, int money, int strength)
{
	this->setTag(tag);
	addPlayerAnimation();
	SpriteFrame* spf;
	switch (tag)
	{
	case PLAYER_1_TAG:
	{
		spf = player_spriteFrameCache->getSpriteFrameByName("player1_anim_01.png");
		break;
	}
	case PLAYER_2_TAG:
	{
		spf = player_spriteFrameCache->getSpriteFrameByName("player2_anim_02.png");
		break;
	}
	}

	setPlayerAnimate();
	Sprite::initWithSpriteFrame(spf);
	_playerName = name;
	_money = money;
	_strength = strength;
	_isMyTurn = true;

	return true;
}

void RicherPlayer::startGo(std::vector<int> rowVector, std::vector<int> colVector)
{

}

void RicherPlayer::addPlayerAnimation()
{
	player_spriteFrameCache = SpriteFrameCache::getInstance();
	int tag = getTag();
	switch (tag)
	{
	case PLAYER_1_TAG:
	{
		player_spriteFrameCache->addSpriteFramesWithFile(PLAYER1_ANIM_PLIST, PLAYER1_ANIM_PNG);
		break;
	}
	case PLAYER_2_TAG:
	{
		player_spriteFrameCache->addSpriteFramesWithFile(PLAYER2_ANIM_PLIST, PLAYER2_ANIM_PNG);
		break;
	}
	}

	char name[20];
	memset(name, 0, 20);

	for (int i = 1; i <= 4; i++)
	{
		sprintf(name, "player%d_anim_%02d.png", tag, i);
		player_anim_left_vector.pushBack(player_spriteFrameCache->getSpriteFrameByName(name));
	}

	for (int i = 5; i <= 8; i++)
	{
		sprintf(name, "player%d_anim_%02d.png", tag, i);
		player_anim_right_vector.pushBack(player_spriteFrameCache->getSpriteFrameByName(name));
	}

	for (int i = 9; i <= 12; i++)
	{
		sprintf(name, "player%d_anim_%02d.png", tag, i);
		player_anim_down_vector.pushBack(player_spriteFrameCache->getSpriteFrameByName(name));
	}

	for (int i = 13; i <= 16; i++)
	{
		sprintf(name, "player%d_anim_%02d.png", tag, i);
		player_anim_up_vector.pushBack(player_spriteFrameCache->getSpriteFrameByName(name));
	}
}

void RicherPlayer::setPlayerAnimate()
{
	int tag = getTag();
	char left_animation[20];
	memset(left_animation, 0, 20);
	sprintf(left_animation, "left_animation_%d", tag);

	char right_animation[20];
	memset(right_animation, 0, 20);
	sprintf(right_animation, "right_animation_%d", tag);

	char down_animation[20];
	memset(down_animation, 0, 20);
	sprintf(down_animation, "down_animation_%d", tag);

	char up_animation[20];
	memset(up_animation, 0, 20);
	sprintf(up_animation, "up_animation_%d", tag);

	if (!AnimationCache::getInstance()->getAnimation(left_animation))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(player_anim_left_vector, playerGoPerframeTime), left_animation);
	}
	if (!AnimationCache::getInstance()->getAnimation(right_animation))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(player_anim_right_vector, playerGoPerframeTime), right_animation);
	}
	if (!AnimationCache::getInstance()->getAnimation(down_animation))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(player_anim_down_vector, playerGoPerframeTime), down_animation);
	}
	if (!AnimationCache::getInstance()->getAnimation(up_animation))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(player_anim_up_vector, playerGoPerframeTime), up_animation);
	}

	left = Animate::create(AnimationCache::getInstance()->getAnimation(left_animation));
	right = Animate::create(AnimationCache::getInstance()->getAnimation(right_animation));
	down = Animate::create(AnimationCache::getInstance()->getAnimation(down_animation));
	up = Animate::create(AnimationCache::getInstance()->getAnimation(up_animation));

	left->retain();
	right->retain();
	down->retain();
	up->retain();
}
