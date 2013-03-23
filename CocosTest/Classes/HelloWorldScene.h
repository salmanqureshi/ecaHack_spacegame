
#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
	void update(float dt);
	void draw();
    // a selector callback
	void onEnter();
    void menuCloseCallback(CCObject* pSender);
	void didAccelerate(cocos2d::CCAcceleration* pAcceleration);
	cocos2d::CCSprite* sprite;
	cocos2d::CCLabelTTF* label;
	cocos2d::CCParallaxNode* bgParallax;
	cocos2d::CCSprite* spaceD1;
	cocos2d::CCSprite* spaceD2;
	cocos2d::CCSprite* planet;
	cocos2d::CCSprite* galaxy;
	cocos2d::CCSprite* anom1;
	cocos2d::CCSprite* anom2;
};
