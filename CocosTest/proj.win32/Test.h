#pragma once
#include "cocos2d.h"
class Test :
	public cocos2d::CCLayer
{
public:
	Test(void);
	static cocos2d::CCScene* scene();
	virtual bool init();
	CREATE_FUNC(Test);
	void update(float dt);
	//void didAccelerate(cocos2d::CCAcceleration* pAcceleration);
	cocos2d::CCSprite* sprite;
	cocos2d::CCLabelTTF* label;
	cocos2d::CCParallaxNode* bgParallax;
	cocos2d::CCSprite* spaceD1;
	cocos2d::CCSprite* spaceD2;
	cocos2d::CCSprite* planet;
	cocos2d::CCSprite* galaxy;
	cocos2d::CCSprite* anom1;
	cocos2d::CCSprite* anom2;
	cocos2d::CCLayerGradient* mainMenu;
	cocos2d::CCLayerGradient* optionsMenu;
	cocos2d::CCLayerGradient* aboutMenu;
	cocos2d::CCLayerGradient* gameMenu;
	cocos2d::CCLayer* menusLayer;
	void optionsClick(cocos2d::CCObject* pSender);
	void gameClick(cocos2d::CCObject* pSender);
	void aboutClick(cocos2d::CCObject* pSender);
	void moveMenuToNode(cocos2d::CCNode* _node);
	void backClicked(cocos2d::CCObject* pSender);
	bool scaled;
	void scale1(cocos2d::CCObject* pSender);
	~Test(void);
};

