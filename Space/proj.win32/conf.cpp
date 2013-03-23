#include "conf.h"

void setSoundOpt(bool en)
{
	cocos2d::CCUserDefault::sharedUserDefault()->setBoolForKey("sound",en);
}

void setMusicOpt(bool en)
{
	cocos2d::CCUserDefault::sharedUserDefault()->setBoolForKey("music",en);
}

void setControls(bool en)
{
	cocos2d::CCUserDefault::sharedUserDefault()->setBoolForKey("accel",en);
}

void setHiScore(int score)
{
	cocos2d::CCUserDefault::sharedUserDefault()->setIntegerForKey("hiScore",score);
}

void addCrystals(int cry)
{
	int crystals = cocos2d::CCUserDefault::sharedUserDefault()->getIntegerForKey("crystals",0);
	crystals += cry;
	cocos2d::CCUserDefault::sharedUserDefault()->setIntegerForKey("crystals",crystals);
}

bool isSoundEnabled()
{
	bool en = false;
	en = cocos2d::CCUserDefault::sharedUserDefault()->getBoolForKey("sound",true);
	return en;
}

bool isMusicEnabled()
{
	bool en = false;
	en = cocos2d::CCUserDefault::sharedUserDefault()->getBoolForKey("music",true);
	return en;
}

int getHightScore()
{
	int score = 0;
	score = cocos2d::CCUserDefault::sharedUserDefault()->getIntegerForKey("hiScore",0);
	return score;
}

int getCrystals()
{
	int crystals = cocos2d::CCUserDefault::sharedUserDefault()->getIntegerForKey("crystals",0);
	return crystals;
}

bool isAccelerometrControl()
{
	bool opt = false;
	opt = cocos2d::CCUserDefault::sharedUserDefault()->getBoolForKey("accel",false);
	return opt;
}

void saveUD()
{
	cocos2d::CCUserDefault::sharedUserDefault()->flush();
}
