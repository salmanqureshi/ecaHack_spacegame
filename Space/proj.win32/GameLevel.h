#pragma once
#include "cocos2d.h"
#include "Player.h"
#include "conf.h"
#include "SimpleAudioEngine.h"
class GameLevel :
	public cocos2d::CCLayer
{
public:
	GameLevel(void);
	bool init();
	CREATE_FUNC(GameLevel);
	void keyBackClicked();
	//void ccTouchesBegan(cocos2d::CCTouch* _touch, cocos2d::CCEvent* e);
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	static cocos2d::CCScene* scene();
	void onEnter();
	void onExit();
	void update(float dt);
	void menuClick(CCObject* pSender);
	void resumeClick(CCObject* pSender);
	Player* player;
	cocos2d::CCSize wSize;
	virtual void didAccelerate(cocos2d::CCAcceleration* pAccel);
	void spawnEnemy(float dt);
	void spawnAsteroid(float dt);
	void gameOver(float dt);
	~GameLevel(void);
private:
	cocos2d::CCParallaxNode* bgSpace;
	cocos2d::CCSprite* stars1;
	cocos2d::CCSprite* stars2;
	cocos2d::CCSprite* planet;
	cocos2d::CCSprite* planet2;
	cocos2d::CCSprite* planet3;
	cocos2d::CCSprite* planet4;
	cocos2d::CCSprite* garbage;
	cocos2d::CCSprite* fog;
	cocos2d::CCLayer* pause;
	cocos2d::CCLabelTTF* scoreText;
	cocos2d::CCLabelTTF* totalscore;
	cocos2d::CCParticleFire* hpBar;
	cocos2d::CCLabelTTF* currentScore;
	std::list<cocos2d::CCParticleFire*>* shoots;
	std::list<cocos2d::CCSprite*>* enemys;
	std::list<cocos2d::CCSprite*>* upgrades;
	bool touchOnPlayer;
	bool accel;
	bool gameover;
	float startY;
	float startX;
	int touchID;
	cocos2d::CCPoint startTouch;
	void Shoot();
	int weaponLvl;
	int wave;
};

