#include "GameLevel.h"
#include "MainMenu.h"
using namespace cocos2d;

CCScene* GameLevel::scene()
{
    CCScene * scene = NULL;
    do 
    {

        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        GameLevel *layer = GameLevel::create();
        CC_BREAK_IF(! layer);

        scene->addChild(layer);
    } while (0);

    return scene;
}

bool GameLevel::init()
{
	bool bRet = false;
	if(CCLayer::init())
	{
		wSize = CCDirector::sharedDirector()->getWinSize();
		touchOnPlayer = false;
		shoots = new std::list<CCParticleFire*>();
		enemys = new std::list<CCSprite*>();
		upgrades = new std::list<CCSprite*>();
		touchID = -1;
		wave = 1;
		weaponLvl = 1;
		startX = 100500.0f;
		startY = 100500.0f;
		gameover = false;
		player = Player::create();
		player->setAnchorPoint(ccp(0.5,0.5));
		player->setPosition(ccp(100,wSize.height/2));
		this->addChild(player,2);
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		
		stars1 = CCSprite::create("Backgrounds/stars.png");
		stars2 = CCSprite::create("Backgrounds/stars.png");
		fog = CCSprite::create("Backgrounds/fog.png");
		garbage = CCSprite::create("Backgrounds/garbage.png");
		planet = CCSprite::create("Backgrounds/planet.png");
		planet2 = CCSprite::create("Backgrounds/planet2.png");
		planet3 = CCSprite::create("Backgrounds/planet3.png");
		planet4 = CCSprite::create("Backgrounds/planet4.png");

		bgSpace = CCParallaxNode::create();
		bgSpace->addChild(stars1,-1,ccp(0.01f,0.01f),ccp(0,size.height/2));
		bgSpace->addChild(stars2,-1,ccp(0.01f,0.01f),ccp(stars1->getContentSize().width,size.height/2));
		bgSpace->addChild(fog,1,ccp(0.05f,0.05f),ccp(1000,size.height/2));
		bgSpace->addChild(garbage,1,ccp(0.08f,0.08f),ccp(3000,size.height/2));
		bgSpace->addChild(planet,0,ccp(0.03f,0.03f),ccp(600,size.height/2));
		bgSpace->addChild(planet2,0,ccp(0.05f,0.05f),ccp(800,size.height/2));
		bgSpace->addChild(planet3,0,ccp(0.05f,0.05f),ccp(1500,size.height/3));
		bgSpace->addChild(planet4,0,ccp(0.05f,0.05f),ccp(2100,size.height/2));
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
		this->addChild(bgSpace,0);

		pause = CCLayer::create();
		CCSprite* bg = CCSprite::create("Menu/tabled.png");
		bg->setAnchorPoint(CCPointZero);
		bg->setPosition(CCPointZero);

		CCMenuItemImage* toMenu = CCMenuItemImage::create(
			"Menu/button_pushed.png",
			"Menu/button_pushed.png",
			this,
			menu_selector(GameLevel::menuClick)
			);
		toMenu->setPosition(size.width/2,180);

		scoreText = CCLabelTTF::create("gfd","",40.0f);
		scoreText->setAnchorPoint(ccp(0.5,0.5));
		scoreText->setPosition(ccp(size.width/2,500));
		scoreText->setHorizontalAlignment(kCCTextAlignmentCenter);
		pause->addChild(scoreText);

		totalscore = CCLabelTTF::create("","",35.0f);
		totalscore->setAnchorPoint(ccp(0.5,0.5));
		totalscore->setPosition(ccp(size.width/2,400));
		totalscore->setHorizontalAlignment(kCCTextAlignmentCenter);
		pause->addChild(totalscore);

		CCLabelTTF* menuL = CCLabelTTF::create("MENU","",40.0f);
		menuL->setPosition(ccp(200,110));
		menuL->setAnchorPoint(ccp(0.5,0.5));
		menuL->setHorizontalAlignment(kCCTextAlignmentCenter);
		toMenu->addChild(menuL);

		CCMenu* menu = CCMenu::create(toMenu,NULL);
		menu->setPosition(CCPointZero);
		menu->setAnchorPoint(CCPointZero);
		pause->addChild(bg);
		pause->addChild(menu);
		pause->setTouchEnabled(false);
		pause->setVisible(false);
		this->addChild(pause,12);
		this->scheduleUpdate();
		this->schedule(SEL_SCHEDULE(&GameLevel::spawnEnemy),15.0f);
		this->schedule(SEL_SCHEDULE(&GameLevel::spawnAsteroid),10.0f);
		//this->schedule(SEL_SCHEDULE(&GameLevel::gameOver),90.0f);

		currentScore = CCLabelTTF::create("SCORE :","",40.0f);
		currentScore->setPosition(ccp(size.width-300,size.height-100));
		currentScore->setAnchorPoint(ccp(0,0));
		currentScore->setHorizontalAlignment(kCCTextAlignmentCenter);
		this->addChild(currentScore,14);

		hpBar = CCParticleFire::create();
		hpBar->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
		hpBar->setAnchorPoint(ccp(0,0.5));
		hpBar->setPosition(ccp(30,570));
		hpBar->setDuration(-1);
		hpBar->setLife(1.0f);
		hpBar->setScaleY(0.1f);
		hpBar->setScaleX(0.01f);
		hpBar->setStartColor(ccc4f(1.0f,1.0f,1.0f,1.0f));
		hpBar->setEndColor(ccc4f(1.0f,0.5f,0.5f,1.0f));
		hpBar->setGravity(ccp(100,0));
		hpBar->setStartSize(100.0f);
		hpBar->setEndSize(100.0f);
		this->addChild(hpBar,14);
		if(isMusicEnabled())
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sound/theme_2.mp3",true);
		}
		bRet = true;
	}
	return bRet;
}

void GameLevel::gameOver(float dt)
{
	gameover = true;
	if(!pause->isVisible())
	{
		pause->setVisible(true);
		pause->setTouchEnabled(true);
	}
	totalscore->setString(CCString::createWithFormat("TOTAL SCORE : %d",player->GetScore())->getCString());
	scoreText->setString("YOU WIN!");
	if(getHightScore() < player->GetScore())
	{
		setHiScore(player->GetScore());
	}
}

void GameLevel::didAccelerate(CCAcceleration* pAccel)
{
	float y,y2,x,x2;
	y = pAccel->y;
	x = pAccel->x;
	if(startX == 100500.0f)
	{
		startX = pAccel->x;
	}
	if(startY == 100500.0f)
	{
		startY = pAccel->y;
	}
	y -= startY;
	x -= startX;
	y*=20;
	x*=20;
	y2 = player->getPositionY();
	y2+= y;
	x2 = player->getPositionX();
	x2 += x;
	if(y2 > 50 && y2 < 560)
	{
		player->setPositionY(y2);
	}
	else if(y2 <= 50)
	{
		player->setPositionY(51);
	}
	else
	{
		player->setPositionY(549);
	}
	if(x2 > 50 && x2 < 512)
	{
		player->setPositionX(x2);
	}
	else if(x2 <= 50)
	{
		player->setPositionX(51);
	}
	else
	{
		player->setPositionX(511);
	}
}

void GameLevel::spawnEnemy(float dt)
{
	if(gameover)
		return;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	for(int i = 0; i < wave * 2; i ++)
	{
		CCString* str = CCString::createWithFormat("enemy_%d.png",rand()%3);
		CCSprite* enemy = CCSprite::create(str->getCString());
		enemy->setPosition(ccp(1200 + i * 200,rand()%500+50));
		enemy->setAnchorPoint(ccp(0.5f,0.5f));
		CCParticleMeteor* fire = CCParticleMeteor::create();
		fire->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
		fire->setDuration(-1);
		fire->setLife(1.0f);
		fire->setScale(0.5f);
		fire->setStartColor(ccc4f(1.0f,0.0f,0.6f,1.0f));
		fire->setAnchorPoint(ccp(0.5,0.5));
		fire->setPosition(ccp(enemy->getContentSize().width/2,enemy->getContentSize().height/2));
		fire->setGravity(ccp(1000,0));
		enemy->addChild(fire,0);
		this->addChild(enemy,2);
		int r = rand()%3;
		switch(r)
		{
		case 0:
			{
			enemy->runAction(CCSequence::create(
				CCMoveTo::create(4.0f + i * 0.5f,ccp(-200,enemy->getPositionY())),
				CCHide::create(), NULL
				));
			} break;
		case 1:{
			enemy->runAction(CCSequence::create(
				CCMoveTo::create(2.0f + i * 0.5f,ccp(size.width/2,enemy->getPositionY())),
				CCMoveTo::create(2.0f, ccp(-200,-1200)),
				CCHide::create(), NULL
				)); 
			} break;
		case 2:{
			enemy->runAction(CCSequence::create(
				CCMoveTo::create(2.0f + i * 0.5f,ccp(size.width/2,enemy->getPositionY())),
				CCMoveTo::create(2.0f,ccp(-200,1200)),
				CCHide::create(), NULL
				));	
			} break;
		}
		enemys->push_back(enemy);
	}
	if(wave < 6)
		wave ++;
	//this->scheduleOnce(SEL_SCHEDULE(&GameLevel::spawnEnemy),2.0f);
}

void GameLevel::spawnAsteroid(float dt)
{
	if(gameover)
		return;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	for(int i = 0; i < wave * 2; i++)
	{
		CCSprite* asteroid = CCSprite::create("asteroid.png");
		asteroid->setPosition(ccp(1200 + i * 200,rand()%500+50));
		asteroid->setAnchorPoint(ccp(0.5,0.5));
		this->addChild(asteroid,2);
		asteroid->runAction(CCSequence::create(
			CCMoveTo::create(3.0f + 0.5f * i,ccp(- 300,asteroid->getPositionY())),
			CCHide::create(),
			NULL
			));
		enemys->push_back(asteroid);
	}
	//this->scheduleOnce(SEL_SCHEDULE(&GameLevel::spawnAsteroid),15.0f);
}

void GameLevel::update(float dt)
{
	CCLayer::update(dt);
	CCPoint bgVel = ccp(-1000,0);
	CCString* txt = CCString::createWithFormat("SCORE : %d",player->GetScore());
	currentScore->setString(txt->getCString());
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
	CCArray* custs = CCArray::create(fog,planet,garbage,planet2,planet3,planet4,NULL);
	CCARRAY_FOREACH(custs,obj)
	{
		CCNode* node =(CCNode*) obj;
		if(bgSpace->convertToWorldSpace(node->getPosition()).x < - node->getContentSize().width)
		{
			bgSpace->incrementOffset(ccp(3000,0),node);
		}
	}
	float hpScale = player->GetHP();
	hpBar->setScaleX(3.0f *( hpScale / 100));
	if(player->GetHP() > 0)
	{
		for(std::list<CCSprite*>::iterator it = upgrades->begin(); it != upgrades->end(); ++it)
		{
			CCSprite* s = *it;
			if(!s->isVisible())
			{
				upgrades->remove(s);
				break;
			}
			CCRect pRect = CCRectMake(player->getPositionX() - 50, player->getPositionY() - 50,
				100,100);
			CCRect rect = CCRectMake(s->getPositionX() - s->getContentSize().width/2, s->getPositionY() - s->getContentSize().height/2,
				s->getContentSize().width,s->getContentSize().height);
			if(pRect.intersectsRect(rect))
			{
				if(isSoundEnabled())
				{
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/click.mp3");
				}
				if(weaponLvl < 3)
					weaponLvl ++;
				s->setVisible(false);
			}
		}

		for(std::list<CCSprite*>::iterator it = enemys->begin(); it != enemys->end(); ++it)
		{
			CCSprite* s = *it;
			if(!s->isVisible())
			{
				enemys->remove(s);
				break;
			}
			CCRect rect = CCRectMake(s->getPositionX() - s->getContentSize().width/2, s->getPositionY() - s->getContentSize().height/2,
				s->getContentSize().width,s->getContentSize().height);
			for(std::list<CCParticleFire*>::iterator f_it = shoots->begin(); f_it != shoots->end(); ++ f_it)
			{
				CCParticleFire* fire = *f_it;
				if(!fire->isVisible())
				{
					shoots->remove(fire);
					break;
				}
				CCPoint fir_rect = fire->getPosition();

				if(rect.containsPoint(fir_rect))
				{
					if(isSoundEnabled())
					{
						CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/enemy_destr.mp3");
					}
					s->setVisible(false);
					fire->setVisible(false);
					CCParticleExplosion* expl = CCParticleExplosion::create();
					expl -> setPosition(fire->getPosition());
					expl -> setAnchorPoint(ccp(0.5,0.5));
					expl -> setDuration(0.5f);
					expl -> setLife(1.0f);
					expl->setStartSize(1.0f);
					expl->setEndSize(2.0f);
					expl->setStartColor(ccc4f(1.0f,0.1f,0.0f,1.0f));
					expl->setEndColor(ccc4f(0.4f,0.0f,0.0f,0.5f));
					expl -> setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
					this -> addChild(expl,2);
					expl -> runAction(CCSequence::create(
						CCMoveTo::create(2.5f,ccp(-200,s->getPositionY())),
						CCHide::create(),
						NULL
						));
					player->addScore(1);
					int rd = rand()%10;
					if(rd == 0)
					{
						CCSprite* upgr = CCSprite::create("upgr.png");
						upgr->setAnchorPoint(ccp(0.5,0.5));
						upgr->setPosition(s->getPosition());
						upgr->runAction(CCSequence::create(
							CCMoveTo::create(2.5f,ccp(-200,upgr->getPositionY())),CCHide::create(), NULL
							));
						this->addChild(upgr,2);
						upgrades->push_back(upgr);
					}
				}
			}	
			CCRect pRect = CCRectMake(player->getPositionX() - 50, player->getPositionY() - 50,
				100,100);
			if(pRect.intersectsRect(rect))
			{
				if(isSoundEnabled())
				{
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/enemy_destr.mp3");
				}
				player->damage(30);
				CCParticleExplosion* expl = CCParticleExplosion::create();
				expl -> setPosition(s->getPosition());
				expl -> setAnchorPoint(ccp(0.5,0.5));
				expl -> setDuration(0.5f);
				expl -> setLife(1.0f);
				expl->setStartSize(1.0f);
				expl->setEndSize(2.0f);
				expl->setStartColor(ccc4f(1.0f,0.1f,0.0f,1.0f));
				expl->setEndColor(ccc4f(0.4f,0.0f,0.0f,0.5f));
				expl -> setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
				this -> addChild(expl,2);
				expl -> runAction(CCSequence::create(
					CCMoveTo::create(0.5f,ccp(-200,s->getPositionY())),
					CCHide::create(),
					NULL
					));
				player->runAction(
					CCBlink::create(0.5f,4)
					);
				s->setVisible(false);
			}
		}
	}
	else
	{
		if(!pause->isVisible())
		{
			pause->setVisible(true);
			pause->setTouchEnabled(true);
			totalscore->setString(CCString::createWithFormat("TOTAL SCORE : %d",player->GetScore())->getCString());
			scoreText->setString("YOU LOSE");
			gameover = true;
			if(getHightScore() < player->GetScore())
			{
				setHiScore(player->GetScore());
			}
		}
	}
}

void GameLevel::resumeClick(CCObject* pSender)
{
	pause->setVisible(false);
	pause->setTouchEnabled(false);
	CCDirector::sharedDirector()->resume();
}

void GameLevel::menuClick(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionProgressHorizontal::create(0.5f,MainMenu::scene()));
}

void GameLevel::keyBackClicked()
{
	if(pause->isVisible())
	{
		pause->setVisible(false);
		pause->setTouchEnabled(false);
		CCDirector::sharedDirector()->resume();
	}
	else
	{
		pause->setVisible(true);
		pause->setTouchEnabled(true);
		CCDirector::sharedDirector()->pause();
	}
}

bool GameLevel::ccTouchBegan(CCTouch* touch, CCEvent* e)
{
	CCPoint cur = touch->getLocation();
	//CCLog("id %d",touch->getID());
	if(cur.x < 512)
	{
		if(accel)
			return true;
		touchID = touch->getID();
		float dist = ccpDistance(cur,player->getPosition());
		dist = dist < 0 ? dist * - 1 : dist;
		if(dist < 100)
			touchOnPlayer = true;
		startTouch = cur;
	}
	else
	{
		Shoot();
	}
//	CCLog("touch %f\t%f",startTouch.x,startTouch.y);
	return true;
}

void GameLevel::onEnter()
{
	CCLayer::onEnter();
	accel = false;
	
	if(isAccelerometrControl())
	{
		accel = true;
		this->setAccelerometerEnabled(true);
	}
}

void GameLevel::onExit()
{
	saveUD();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CCLayer::onExit();
}

void GameLevel::ccTouchMoved(CCTouch* touch,CCEvent* e)
{
	if(accel)
		return;
	CCPoint cur;
	if(touch->getID() == touchID)
	{
		cur = touch->getLocation();
		if(touchOnPlayer)
		{
			if(cur.y < 560 && cur.y > 50)
				player->setPositionY(cur.y);
			if(cur.x > 50 && cur.x < 512)
			{
				player->setPositionX(cur.x);
			}
		}
	}
	//return true;
}

void GameLevel::ccTouchEnded(CCTouch* touch,CCEvent* e)
{
	if(accel)
		return;
	if(touch->getID() == touchID)
		touchOnPlayer = false;
	//return true;
}

void GameLevel::ccTouchCancelled(CCTouch* touch, CCEvent* e)
{
	//return true;
}

void GameLevel::Shoot()
{
	if(isSoundEnabled())
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/blaster.mp3");
	}
	CCPoint pP = player->getPosition();
	CCParticleFire* fire = CCParticleFire::create();
	pP.x += 50;
	fire->setPosition(pP);
	fire->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
	fire->setDuration(-1);
	fire->setScaleY(0.05f);
	fire->setScaleX(0.2f);
	switch(weaponLvl)
	{
	case 1:
		fire->setStartColor(ccc4f(1.0f,0.0f,0.0f,1.0f));
		fire->setEndColor(ccc4f(1.0f,0.0f,0.0f,1.0f));
		break;
	case 2:
		fire->setStartColor(ccc4f(0.0f,1.0f,0.0f,1.0f));
		fire->setEndColor(ccc4f(0.0f,1.0f,0.0f,1.0f));
		break;
	case 3: 
		{
			fire->setStartColor(ccc4f(0.0f,0.0f,1.0f,1.0f));
			fire->setEndColor(ccc4f(0.0f,0.0f,1.0f,1.0f));
			fire->setPosition(ccp(pP.x,pP.y - 35));
			CCParticleFire* fire2 = CCParticleFire::create();
			pP.x += 50;
			fire2->setPosition(ccp(pP.x,pP.y + 35));
			fire2->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
			fire2->setDuration(-1);
			fire2->setScaleY(0.05f);
			fire2->setStartColor(ccc4f(0.0f,0.0f,1.0f,1.0f));
			fire2->setEndColor(ccc4f(0.0f,0.0f,1.0f,1.0f));
			fire2->setScaleX(0.2f);
			fire2->setStartSize(300.0f);
			fire2->setEndSize(300.0f);
			fire2->setLife(0.3f);
			this->addChild(fire2);
			CCPoint dP = fire2->getPosition();
			dP.x += 1200;
			fire2->runAction(CCSequence::create(
				CCMoveTo::create(0.5f,dP),
				CCHide::create(),
				NULL
				));
			shoots->push_back(fire2);
		}
		break;
	}
	fire->setStartSize(300.0f);
	fire->setEndSize(300.0f);
	fire->setLife(0.3f);
	CCPoint dP = fire->getPosition();
	dP.x += 1200;
	this->addChild(fire);
	fire->runAction(CCSequence::create(
		CCMoveTo::create(0.5f,dP),
		CCHide::create(),
		NULL
		));
	shoots->push_back(fire);
}

GameLevel::GameLevel(void)
{
}


GameLevel::~GameLevel(void)
{
	delete shoots;
	delete enemys;
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}
