#pragma once
#include "cocos2d.h"
#include "conf.h"
#include "SimpleAudioEngine.h"

class MainMenu : public cocos2d::CCLayer
{
public:
    virtual bool init();  
    static cocos2d::CCScene* scene();
    void exitClick(CCObject* pSender);
	void keyBackClicked();
	cocos2d::CCLayer* menusLayer;
	cocos2d::CCLayer* mmL;
	void backClicked(CCObject* pSender);
	void newGameClicked(CCObject* pSender);
	void optionsClicked(CCObject* pSender);
	cocos2d::CCLayer* omL;
	void optSetVolume(CCObject* pSender);
	void optSetMusic(CCObject* pSender);
	void optSetControls(CCObject* pSender);
	cocos2d::CCLayer* gmL;
	void gameStartClicked(CCObject* pSender);
	void moveMenuToNode(CCNode* pNode);
	void scalemmL();
	void onEnter();
	void onExit();
	void update(float dt);
	cocos2d::CCLabelTTF* scoreT;
    CREATE_FUNC(MainMenu);
private:
	cocos2d::CCParallaxNode* bgSpace;
	cocos2d::CCSprite* stars1;
	cocos2d::CCSprite* stars2;
	cocos2d::CCSprite* planet;
	cocos2d::CCSprite* garbage;
	cocos2d::CCSprite* fog;
	int crystals;
	int hiScore;
};
