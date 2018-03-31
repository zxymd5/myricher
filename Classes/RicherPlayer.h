#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ConstUtil.h"

USING_NS_CC;
USING_NS_CC_EXT;
const float playerGoPerframeTime = 0.07f;

class RicherPlayer : public Sprite
{
public:
	RicherPlayer();
	~RicherPlayer();

	SpriteFrameCache *player_spriteFrameCache;
	static RicherPlayer *create(char *name, int tag, int money = 50000, int strength = 100);
	bool init(char *name, int tag, int money, int strength);
	void startGo(std::vector<int> rowVector, std::vector<int> colVector);

	CC_SYNTHESIZE(Vector<SpriteFrame *>, player_anim_left_vector, Anim_left_vector);
	CC_SYNTHESIZE(Vector<SpriteFrame *>, player_anim_right_vector, Anim_right_vector);
	CC_SYNTHESIZE(Vector<SpriteFrame *>, player_anim_down_vector, Anim_down_vector);
	CC_SYNTHESIZE(Vector<SpriteFrame *>, player_anim_up_vector, Anim_up_vector);

	CC_SYNTHESIZE(Animate *, left, Left);
	CC_SYNTHESIZE(Animate *, right, Right);
	CC_SYNTHESIZE(Animate *, down, Down);
	CC_SYNTHESIZE(Animate *, up, Up);

	void addPlayerAnimation();
	void setPlayerAnimate();

private:
	CC_SYNTHESIZE(std::string, _playerName, PlayerName);
	CC_SYNTHESIZE(int, _money, Money);
	CC_SYNTHESIZE(int, _strength, Strength);

	CC_SYNTHESIZE(int, _comeFromeRow, ComeFromeRow);
	CC_SYNTHESIZE(int, _comeFromCol, ComeFromCol);
	CC_SYNTHESIZE(bool, _isMyTurn, IsMyTurn);
};

#endif
