#include "Test.h"


using namespace cocos2d;

CCScene* Test::scene()
{
	CCScene* scene = NULL;
	do{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);
		Test *layer = Test::create();
		CC_BREAK_IF(! layer);

		scene->addChild(layer);
	}while(0);
	return scene;
}

bool Test::init()
{
	bool bRet = false;
	if(CCLayer::init())
	{
		 CCSize size = CCDirector::sharedDirector()->getWinSize();
		 scaled = false;
		//sprite = CCSprite::create("player.png");
		//sprite ->setAnchorPoint(ccp(0.5,0.5));
		//sprite ->setPosition(ccp(size.width/2,size.height/2));
		//this->addChild(sprite,10);

		menusLayer = CCLayer::create();
		this->addChild(menusLayer);

		//MainMenu
		mainMenu = CCLayerGradient::create(ccc4(0.0f,180.0f,0.0f,60.0f),ccc4(0.0f,0.0f,0.0f,0.0f),ccp(-100,0));
		//mainMenu->setAnchorPoint(ccp(0.5,0.5));
		mainMenu->setPosition(0,0);
		menusLayer->addChild(mainMenu);

		CCMenuItemLabel* gameB = CCMenuItemLabel::create(
			CCLabelTTF::create("New Game","",40.0f),
			this,
			menu_selector(Test::gameClick)
			);
		CCMenuItemLabel* optB = CCMenuItemLabel::create(
			CCLabelTTF::create("Options","",40.0f),
			this,
			menu_selector(Test::optionsClick)
			);
		CCMenuItemLabel* abouB = CCMenuItemLabel::create(
			CCLabelTTF::create("About","",40.0f),
			this,
			menu_selector(Test::aboutClick)
			);
		gameB->setPosition(size.width/2,400);
		optB->setPosition(size.width/2,300);
		abouB->setPosition(size.width/2,200);
		CCMenu* mainM = CCMenu::create(gameB, optB,abouB,NULL);
		mainM->setAnchorPoint(ccp(0.0f,0.0f));
		mainM->setPosition(0,0);
		mainMenu->addChild(mainM);

		//OptionsMenu
		optionsMenu = CCLayerGradient::create(ccc4(0.0f,180.0f,0.0f,60.0f),ccc4(0.0f,0.0f,0.0f,0.0f),ccp(-100,0));
		optionsMenu->setPosition(960,0);
		//optionsMenu->setAnchorPoint(ccp(0.5,0.5));
		optionsMenu->setScale(0.5f);
		menusLayer->addChild(optionsMenu);
		CCMenuItemLabel* backOptB = CCMenuItemLabel::create(
			CCLabelTTF::create("Back","",40.0f),
			this,
			menu_selector(Test::backClicked)
			);
		backOptB->setAnchorPoint(ccp(0.5,0.5));
		backOptB->setPosition(size.width/2,size.height/2);
		CCMenu* optM = CCMenu::create(backOptB,NULL);
		optM->setAnchorPoint(CCPointZero);
		optM->setPosition(0,0);
		optionsMenu->addChild(optM);

		//AboutMenu
		aboutMenu = CCLayerGradient::create(ccc4(0.0f,180.0f,0.0f,60.0f),ccc4(0.0f,0.0f,0.0f,0.0f),ccp(-100,0));
		aboutMenu->setPosition(1920,0);
		aboutMenu->setScale(0.5f);
	//	aboutMenu->setAnchorPoint(ccp(0.5,0.5));
		menusLayer->addChild(aboutMenu);
		CCMenuItemLabel* backAboB = CCMenuItemLabel::create(
			CCLabelTTF::create("Back","",40.0f),
			this,
			menu_selector(Test::backClicked)
			);
		backAboB->setAnchorPoint(ccp(0.5,0.5));
		backAboB->setPosition(size.width/2,size.height/2);
		CCMenu* aboM = CCMenu::create(backAboB,NULL);
		aboM->setAnchorPoint(CCPointZero);
		aboM->setPosition(0,0);
		aboutMenu->addChild(aboM);

		//GameMenu
		gameMenu = CCLayerGradient::create(ccc4(0.0f,180.0f,0.0f,60.0f),ccc4(0.0f,0.0f,0.0f,0.0f),ccp(-100,0));
		gameMenu->setPosition(2880,0);
		gameMenu->setScale(0.5f);
		//gameMenu->setAnchorPoint(ccp(0.5,0.5));
		menusLayer->addChild(gameMenu);
		CCMenuItemLabel* backGamB = CCMenuItemLabel::create(
			CCLabelTTF::create("Back","",40.0f),
			this,
			menu_selector(Test::backClicked)
			);
		backGamB->setAnchorPoint(ccp(0.5,0.5));
		backGamB->setPosition(size.width/2,size.height/2);
		CCMenu* gamM = CCMenu::create(backGamB,NULL);
		gamM->setAnchorPoint(CCPointZero);
		gamM->setPosition(0,0);
		gameMenu->addChild(gamM);

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

		//CCMenuItemLabel* but = CCMenuItemLabel::create(CCLabelTTF::create("scale","",40.0f),
		//	this,menu_selector(Test::scale1));

		//but->setPosition(ccp(size.width/2,size.height/2));
		//CCMenu* menu = CCMenu::create(but, NULL);
		//menu->setAnchorPoint(CCPointZero);
		//menu->setPosition(CCPointZero);
		//this->addChild(menu,12);


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
	}
	return bRet;
}

void Test::optionsClick(CCObject* pSender)
{
	mainMenu->runAction(
		CCScaleTo::create(0.5f,0.5f)
		);
	moveMenuToNode(optionsMenu);
}

void Test::gameClick(CCObject* pSender)
{
	mainMenu->runAction(
		CCScaleTo::create(0.5f,0.5f)
		);
	moveMenuToNode(gameMenu);
}

void Test::aboutClick(CCObject* pSender)
{
	mainMenu->runAction(
		CCScaleTo::create(0.5f,0.5f)
		);
	moveMenuToNode(aboutMenu);	
}

void Test::backClicked(CCObject* pSender)
{
	CCNode* node = (CCNode*) pSender;
	CCNode* parent = node->getParent()->getParent();
	parent->runAction(CCScaleTo::create(0.5f,0.5f));
	mainMenu->runAction(
		CCScaleTo::create(0.5f,0.5f)
		);
	moveMenuToNode(mainMenu);
}

void Test::moveMenuToNode(CCNode* _node)
{
	CCPoint p =_node->getPosition();
	CCPoint desP = ccp(0 - p.x,0);
	menusLayer->runAction(CCSequence::create(
		CCDelayTime::create(0.5f),CCMoveTo::create(0.4f,desP),NULL
		));
	_node->setScale(0.5f);
	_node->runAction(CCSequence::create(
		CCDelayTime::create(0.9f),CCScaleTo::create(0.4f,1.0f),NULL
		));
}

void Test::scale1(CCObject* pSender)
{
	if(scaled)
	{
		this->runAction(CCScaleTo::create(0.5f,1.0f));
		scaled = false;
	}
	else
	{
		this->runAction(CCScaleTo::create(0.5f,0.5f));
		scaled = true;
	}
}

void Test::update(float dt)
{
	CCLayer::update(dt);
	CCPoint bgVel = ccp(-1000,0);
	bgParallax->setPosition( ccpAdd(bgParallax->getPosition(), ccpMult(bgVel,dt)) );
	CCArray* bgs = CCArray::create(spaceD1,spaceD2,NULL);
	CCObject* obj = NULL;
	CCARRAY_FOREACH(bgs,obj)
	{
		CCNode* node = (CCNode*)obj;
		if(bgParallax->convertToWorldSpace(node->getPosition()).x < -node->getContentSize().width/2)
		{
			bgParallax->incrementOffset(ccp(2*node->getContentSize().width,0),node);
		}
	}
	obj = NULL;
	CCArray* custs = CCArray::create(galaxy,planet,anom1,anom2,NULL);
	CCARRAY_FOREACH(custs,obj)
	{
		CCNode* node =(CCNode*) obj;
		if(bgParallax->convertToWorldSpace(node->getPosition()).x < - node->getContentSize().width)
		{
			bgParallax->incrementOffset(ccp(2000,0),node);
		}
	}
}

Test::Test(void)
{
}


Test::~Test(void)
{
}
