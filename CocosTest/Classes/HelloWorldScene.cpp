#include "HelloWorldScene.h"

using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
    {
		
        CC_BREAK_IF(! CCLayer::init());

        CCSize size = CCDirector::sharedDirector()->getWinSize();

		sprite = CCSprite::create("player.png");
		sprite ->setAnchorPoint(ccp(0.5,0.5));
		sprite ->setPosition(ccp(size.width/2,size.height/2));
		this->addChild(sprite,10);

		label = CCLabelTTF::create();
		label->setFontSize(20.0f);
		label->setPosition(ccp(size.width/2, 100));
		label->setAnchorPoint(ccp(0.5f,0.5f));
		this->addChild(label,12);

		spaceD1 = CCSprite::create("Backgrounds/bg_front_spacedust.png");
		spaceD2 = CCSprite::create("Backgrounds/bg_front_spacedust.png");
		planet = CCSprite::create("Backgrounds/bg_planetsunrise.png");
		galaxy = CCSprite::create("Backgrounds/bg_galaxy.png");
		anom1 = CCSprite::create("Backgrounds/bg_spacialanomaly.png");
		anom2 = CCSprite::create("Backgrounds/bg_spacialanomaly2.png");

		CCPoint dspead = ccp(0.1,0.1);
		CCPoint bgSpead = ccp(0.05,0.05);

		bgParallax = CCParallaxNode::create();
		bgParallax->addChild(spaceD1,0,dspead,ccp(0,size.height/2));
		bgParallax->addChild(spaceD2,0,dspead,ccp(spaceD1->getContentSize().width,size.height/2));
		bgParallax->addChild(galaxy,-1,bgSpead,ccp(0,size.height * 0.7));
		bgParallax->addChild(planet,-1,bgSpead,ccp(0,size.height * 0));
		bgParallax->addChild(anom1,-1,bgSpead,ccp(900,size.height * 0.3));
		bgParallax->addChild(anom2,-1,bgSpead,ccp(1500,size.height * 0.9));
		this->addChild(bgParallax,-1);

		this->scheduleUpdate();
        bRet = true;
    } while (0);

    return bRet;
}

void HelloWorld::onEnter()
{
	this->setAccelerometerEnabled(true);
}

void HelloWorld::didAccelerate(CCAcceleration* pAcceleration)
{
	float x,y,z;
	x = pAcceleration->x;
	y = pAcceleration->y;
	z = pAcceleration->z;
	CCPoint p = sprite->getPosition();
	label->setString(CCString::createWithFormat("x %f, y %f, z %f",x,y,z)->getCString());
	if(p.x > 0 && p.x < 1024)
	{
		p.x += x;
	}
	else
	{
		p.x = CCDirector::sharedDirector()->getWinSize().width/2;
	}
	if(p.y > 0 && p.y < 728)
	{
		p.y +=y;
	}
	else
	{
		p.y = CCDirector::sharedDirector()->getWinSize().height/2;
	}
	sprite->setPosition(p);
}

void HelloWorld::draw()
{
	//CCLog("draw");
}

void HelloWorld::update(float dt)
{
	CCLog("update");
	//CCLayer::update(dt);
	//CCPoint bgVel = ccp(-1000,0);
	//bgParallax->setPosition( ccpAdd(bgParallax->getPosition(), ccpMult(bgVel,dt)) );
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

