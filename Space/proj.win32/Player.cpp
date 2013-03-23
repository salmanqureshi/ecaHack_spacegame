#include "Player.h"

using namespace cocos2d;

bool Player::init()
{
	bool bRet = false;
	if(CCSprite::init())
	{
		hp = 100;
		score = 0;
		crystals = 0;
		CCSprite* ship = CCSprite::create("player.png");
		/*ship = Ship::create();*/
		ship->setAnchorPoint(ccp(0.5,0.5));
		ship->setPosition(CCPointZero);
		this->addChild(ship,1);
		CCParticleMeteor* fire = CCParticleMeteor::create();
		fire->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
		fire->setDuration(-1);
		fire->setLife(1.0f);
		fire->setAnchorPoint(ccp(0.5,0.5));
		fire->setPosition(ccp(-20,0));
		fire->setGravity(ccp(-10000,0));
		this->addChild(fire,0);

		bRet = true;
	}
	return bRet;
}

void Player::damage(int _d)
{
	hp -= _d;
}

void Player::addCrystals(int _cry)
{
	crystals += _cry;
}

void Player::addScore(int _scor)
{
	score += _scor;
}

int Player::GetHP()
{
	return hp;
}

int Player::GetScore()
{
	return score;
}

int Player::GetCrystals()
{
	return crystals;
}

Player::Player(void)
{
}


Player::~Player(void)
{
}
