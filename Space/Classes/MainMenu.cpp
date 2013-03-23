#include "MainMenu.h"
#include "GameLevel.h"
using namespace cocos2d;

CCScene* MainMenu::scene()
{
    CCScene * scene = NULL;
    do 
    {

        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        MainMenu *layer = MainMenu::create();
        CC_BREAK_IF(! layer);

        scene->addChild(layer);
    } while (0);

    return scene;
}


bool MainMenu::init()
{
    bool bRet = false;
	if(CCLayer::init())
	{

        CCSize size = CCDirector::sharedDirector()->getWinSize();

		hiScore = getHightScore();
		crystals = getCrystals();
		
		CCSprite* scoreBar = CCSprite::create("Menu/scoreBar.png");
		scoreBar->setPosition(ccp(size.width,size.height));
		scoreBar->setAnchorPoint(ccp(1,1));
		this->addChild(scoreBar,10);

		CCSprite* logo = CCSprite::create("logo.png");
		logo->setAnchorPoint(ccp(0,1));
		logo->setPosition(ccp(0,size.height));
		this->addChild(logo,5);

		CCString* hiScoreStr = CCString::createWithFormat("HIGHT SCORE : %d",hiScore);
		scoreT = CCLabelTTF::create(hiScoreStr->getCString(),"",20.0f);
		scoreT->setHorizontalAlignment(kCCTextAlignmentCenter);
		scoreT->setAnchorPoint(ccp(0.5,0.0));
		scoreT->setColor(ccc3(0,255,255));
		scoreT->setPosition(ccp(300,142));
		scoreBar->addChild(scoreT);

		menusLayer = CCLayer::create();
		this->addChild(menusLayer,1);
		mmL = CCLayer::create();
		mmL->setPosition(0,0);
		mmL->setScale(0.5f);
		mmL->runAction(
			CCScaleTo::create(0.5f,1.0f)
			);
		//moveMenuToNode(mmL);
		menusLayer->addChild(mmL,2);
		CCSprite* bgM = CCSprite::create("Menu/tabled.png");
		bgM->setPosition(CCPointZero);
		bgM->setAnchorPoint(CCPointZero);
		mmL->addChild(bgM);

		omL = CCLayer::create();
		omL->setPosition(-1024,0);
		omL->setScale(0.5);
		menusLayer->addChild(omL,2);
		CCSprite* bgO = CCSprite::create("Menu/tabled.png");
		bgO->setPosition(CCPointZero);
		bgO->setAnchorPoint(CCPointZero);
		omL->addChild(bgO);
		gmL = CCLayer::create();
		gmL->setPosition(1024,0);
		gmL->setScale(0.5);
		menusLayer->addChild(gmL,2);
		CCSprite* bgG = CCSprite::create("Menu/tabled.png");
		bgG->setPosition(CCPointZero);
		bgG->setAnchorPoint(CCPointZero);
		gmL->addChild(bgG);
		CCMenuItemImage* ngB = CCMenuItemImage::create(
			"Menu/button_normal.png",
			"Menu/button_pushed.png",
			this,
			menu_selector(MainMenu::newGameClicked)
			);
		CCLabelTTF* ngL = CCLabelTTF::create("NEW GAME","",40.0f);
		ngL->setPosition(ccp(200,110));
		ngL->setAnchorPoint(ccp(0.5,0.5));
		ngL->setHorizontalAlignment(kCCTextAlignmentCenter);
		//ngL->setColor(ccc3(119,207,7));
		ngB->addChild(ngL);
		CCMenuItemImage* opB = CCMenuItemImage::create(
			"Menu/button_normal.png",
			"Menu/button_pushed.png",
			this,
			menu_selector(MainMenu::optionsClicked)
			);
		CCLabelTTF* opL = CCLabelTTF::create("OPTIONS","",40.0f);
		opL->setPosition(ccp(200,110));
		opL->setAnchorPoint(ccp(0.5,0.5));
		opL->setHorizontalAlignment(kCCTextAlignmentCenter);
		//opL->setColor(ccc3(119,207,7));
		opB->addChild(opL);
		CCMenuItemImage* exB = CCMenuItemImage::create(
			"Menu/button_normal.png",
			"Menu/button_pushed.png",
			this,
			menu_selector(MainMenu::exitClick)
			);
		CCLabelTTF* exL = CCLabelTTF::create("EXIT","",40.0f);
		exL->setPosition(ccp(200,110));
		exL->setAnchorPoint(ccp(0.5,0.5));
		exL->setHorizontalAlignment(kCCTextAlignmentCenter);
		//exL->setColor(ccc3(119,207,7));
		exB->addChild(exL);
		ngB->setPosition(size.width/2,350);
		opB->setPosition(size.width/2,220);
		exB->setPosition(size.width/2,90);

		CCMenu* mmM = CCMenu::create(ngB,opB,exB,NULL);
		mmM->setPosition(0,0);
		mmM->setAnchorPoint(CCPointZero);
		mmL->addChild(mmM);


		CCMenuItemImage* obackB = CCMenuItemImage::create(
			"Menu/back_normal.png",
			"Menu/back_pushedl.png",
			this,
			menu_selector(MainMenu::backClicked)
			);
		bool isS = isSoundEnabled();
		bool isM = isMusicEnabled();
		bool isA = isAccelerometrControl();

		CCMenuItemImage* oS = CCMenuItemImage::create(
			isS == true ? "Menu/tick_active.png" : "Menu/tick_deactive.png" ,
			isS == true ? "Menu/tick_deactive.png" : "Menu/tick_active.png",
			this,
			menu_selector(MainMenu::optSetVolume)
			);
		CCMenuItemImage* oM = CCMenuItemImage::create(
			isM == true ? "Menu/tick_active.png" : "Menu/tick_deactive.png" ,
			isM == true ? "Menu/tick_deactive.png" : "Menu/tick_active.png",
			this,
			menu_selector(MainMenu::optSetMusic)
			);
		CCMenuItemImage* oC = CCMenuItemImage::create(
			isA == true ? "Menu/tick_active.png" : "Menu/tick_deactive.png" ,
			isA == true ? "Menu/tick_deactive.png" : "Menu/tick_active.png",
			this,
			menu_selector(MainMenu::optSetControls)
			);

	/*	CCSprite* line1 = CCSprite::create("Menu/line.png");
		line1->setPosition(ccp(size.width/2,320));
		line1->setAnchorPoint(ccp(0.5,0.5));
		omL->addChild(line1);*/

		CCLabelTTF* osL = CCLabelTTF::create("SOUND","",30.0f);
		osL->setAnchorPoint(ccp(0.5,0.5));
		osL->setPosition(ccp(size.width/2 - 100,360));
		osL->setColor(ccc3(255,196,0));
		osL->setHorizontalAlignment(kCCTextAlignmentCenter);
		omL->addChild(osL);

		CCLabelTTF* omuL = CCLabelTTF::create("MUSIC","",30.0f);
		omuL->setAnchorPoint(ccp(0.5,0.5));
		omuL->setPosition(ccp(size.width/2 - 100,230));
		omuL->setColor(ccc3(255,196,0));
		omuL->setHorizontalAlignment(kCCTextAlignmentCenter);
		omL->addChild(omuL);
		
		CCLabelTTF* ocL = CCLabelTTF::create("ACCELEROMETR","",30.0f);
		ocL->setAnchorPoint(ccp(0.5,0.5));
		ocL->setPosition(ccp(size.width/2 - 100,100));
		ocL->setColor(ccc3(255,196,0));
		ocL->setHorizontalAlignment(kCCTextAlignmentCenter);
		omL->addChild(ocL);

		obackB->setPosition(850,150);
		oS->setPosition(size.width/2 + 100,370);
		oM->setPosition(size.width/2 + 100,240);
		oC->setPosition(size.width/2 + 100,110);

		CCMenu* opM = CCMenu::create(obackB,oS,oM,oC,NULL);
		opM->setAnchorPoint(CCPointZero);
		opM->setPosition(0,0);
		omL->addChild(opM);

		CCMenuItemImage* gbackB = CCMenuItemImage::create(
			"Menu/back_normal.png",
			"Menu/back_pushedl.png",
			this,
			menu_selector(MainMenu::backClicked)
			);
		CCMenuItemImage* gPlay = CCMenuItemImage::create(
			"Menu/button_normal.png",
			"Menu/button_pushed.png",
			this,
			menu_selector(MainMenu::gameStartClicked)
			);
		CCLabelTTF* plL = CCLabelTTF::create("PLAY","",40.0f);
		plL->setPosition(ccp(200,110));
		plL->setAnchorPoint(ccp(0.5,0.5));
		plL->setHorizontalAlignment(kCCTextAlignmentCenter);
		gPlay->addChild(plL);

		gbackB->setPosition(850,150);
		gPlay->setPosition(size.width/2,300);
		CCMenu* ngM = CCMenu::create(gbackB,gPlay,NULL);
		ngM->setPosition(0,0);
		ngM->setAnchorPoint(CCPointZero);
		gmL->addChild(ngM);

		stars1 = CCSprite::create("Backgrounds/stars.png");
		stars2 = CCSprite::create("Backgrounds/stars.png");
		fog = CCSprite::create("Backgrounds/fog.png");
		garbage = CCSprite::create("Backgrounds/garbage.png");
		planet = CCSprite::create("Backgrounds/planet.png");

		bgSpace = CCParallaxNode::create();
		bgSpace->addChild(stars1,-1,ccp(0.01f,0.01f),ccp(0,size.height/2));
		bgSpace->addChild(stars2,-1,ccp(0.01f,0.01f),ccp(stars1->getContentSize().width,size.height/2));
		bgSpace->addChild(fog,1,ccp(0.05f,0.05f),ccp(1000,size.height/2));
		bgSpace->addChild(garbage,1,ccp(0.08f,0.08f),ccp(3000,size.height/2));
		bgSpace->addChild(planet,0,ccp(0.03f,0.03f),ccp(600,size.height/2));
		this->addChild(bgSpace,0);

		CCSprite* art = CCSprite::create("art.png");
		art->setAnchorPoint(CCPointZero);
		art->setPosition(CCPointZero);
		this->addChild(art,15);
		art->runAction(CCSequence::create(
			CCDelayTime::create(3.0f),CCHide::create(), NULL
			));
		this->scheduleUpdate();
        bRet = true;
    } 

    return bRet;
}

void MainMenu::onEnter()
{
	CCLayer::onEnter();
	if(isMusicEnabled())
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sound/menu_bg.mp3",true);
	}
}

void MainMenu::onExit()
{
	saveUD();

	CCLayer::onExit();
}

void MainMenu::update(float dt)
{
	CCLayer::update(dt);
	CCPoint bgVel = ccp(-1000,0);
	bgSpace->setPosition( ccpAdd(bgSpace->getPosition(), ccpMult(bgVel,dt)) );
	CCArray* bgs = CCArray::create(stars1,stars2,NULL);
	CCObject* obj = NULL;
	CCARRAY_FOREACH(bgs,obj)
	{
		CCNode* node = (CCNode*)obj;
		if(bgSpace->convertToWorldSpace(node->getPosition()).x < -node->getContentSize().width/2)
		{
			bgSpace->incrementOffset(ccp(2*node->getContentSize().width,0),node);
		}
	}
	obj = NULL;
	CCArray* custs = CCArray::create(fog,planet,garbage,NULL);
	CCARRAY_FOREACH(custs,obj)
	{
		CCNode* node =(CCNode*) obj;
		if(bgSpace->convertToWorldSpace(node->getPosition()).x < - node->getContentSize().width)
		{
			bgSpace->incrementOffset(ccp(3000,0),node);
		}
	}
}

void MainMenu::moveMenuToNode(CCNode* pNode)
{
	if(isSoundEnabled())
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/menu_change.mp3");
	}
	CCPoint p = pNode->getPosition();
	CCPoint desP = ccp(0 - p.x,0);
	menusLayer->runAction(CCSequence::create(
		CCDelayTime::create(0.5f),CCMoveTo::create(0.4f,desP),NULL
		));
	pNode->setScale(0.5f);
	pNode->runAction(CCSequence::create(
		CCDelayTime::create(0.9f),CCScaleTo::create(0.4f,1.0f),NULL
		));
}

void MainMenu::backClicked(CCObject* pSender)
{
	CCNode* node = (CCNode*) pSender;
	CCNode* parent = node->getParent()->getParent();
	parent->runAction(CCScaleTo::create(0.5f,0.5f));
	moveMenuToNode(mmL);
}

void MainMenu::optionsClicked(CCObject* pSender)
{
	scalemmL();
	moveMenuToNode(omL);
}

void MainMenu::scalemmL()
{
	mmL->runAction(
			CCScaleTo::create(0.5f,0.5f)
		);
}

void MainMenu::newGameClicked(CCObject* pSender)
{
	scalemmL();
	moveMenuToNode(gmL);
}

void MainMenu::optSetControls(CCObject* pSender)
{
	CCMenuItemImage* but = (CCMenuItemImage*) pSender;

	if(isAccelerometrControl())
	{
		but->setSelectedImage(CCSprite::create("Menu/tick_active.png"));
		but->setNormalImage(CCSprite::create("Menu/tick_deactive.png"));
		setControls(false);
	}
	else
	{
		but->setSelectedImage(CCSprite::create("Menu/tick_deactive.png"));
		but->setNormalImage(CCSprite::create("Menu/tick_active.png"));
		setControls(true);
	}
}

void MainMenu::optSetMusic(CCObject* pSender)
{
	CCMenuItemImage* but = (CCMenuItemImage*) pSender;
	if(isMusicEnabled())
	{
		but->setSelectedImage(CCSprite::create("Menu/tick_active.png"));
		but->setNormalImage(CCSprite::create("Menu/tick_deactive.png"));
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		setMusicOpt(false);
	}
	else
	{
		but->setSelectedImage(CCSprite::create("Menu/tick_deactive.png"));
		but->setNormalImage(CCSprite::create("Menu/tick_active.png"));
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sound/menu_bg.mp3",true);
		setMusicOpt(true);
	}
}

void MainMenu::optSetVolume(CCObject* pSender)
{
	CCMenuItemImage* but = (CCMenuItemImage*) pSender;
	if(isSoundEnabled())
	{
		but->setSelectedImage(CCSprite::create("Menu/tick_active.png"));
		but->setNormalImage(CCSprite::create("Menu/tick_deactive.png"));
		setSoundOpt(false);
	}
	else
	{
		but->setSelectedImage(CCSprite::create("Menu/tick_deactive.png"));
		but->setNormalImage(CCSprite::create("Menu/tick_active.png"));
		setSoundOpt(true);
	}
}

void MainMenu::gameStartClicked(CCObject* pSender)
{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5f,GameLevel::scene()));
}

void MainMenu::keyBackClicked()
{
	
}

void MainMenu::exitClick(CCObject* pSender)
{
	saveUD();
    CCDirector::sharedDirector()->end();
}

