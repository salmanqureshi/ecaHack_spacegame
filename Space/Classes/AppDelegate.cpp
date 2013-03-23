#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "MainMenu.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("Sound/menu_bg.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("Sound/theme_2.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/menu_change.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/click.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/blaster.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/enemy_destr.mp3");
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
	pEGLView->setDesignResolutionSize(1024,600,kResolutionNoBorder);
    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = MainMenu::scene();

    // run
    pDirector->runWithScene(pScene);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
