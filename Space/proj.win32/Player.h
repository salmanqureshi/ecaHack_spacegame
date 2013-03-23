#pragma once
#include "cocos2d.h"
//#include "Ship.h"

class Player :
	public cocos2d::CCSprite
{
public:
	Player(void);
	bool init();
	int GetHP();
	int GetScore();
	int GetCrystals();
	void damage(int _d);
	void addCrystals(int _cry);
	void addScore(int _scor);
	CREATE_FUNC(Player);
	~Player(void);
private:
	//Ship* ship;
	int hp;
	int crystals;
	int score;
	int armor;
	int atack;

};

