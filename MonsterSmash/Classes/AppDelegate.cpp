#include "AppDelegate.h"
#include "MainScene.h"

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("MonsterSmash");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    settingScreen();

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = MainScene::scene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void AppDelegate::settingScreen()
{
    Director* director = Director::getInstance();
    GLView* glview = director->getOpenGLView();

    Size designSize(2048, 1536);

    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::EXACT_FIT);

    const Size & screenSize = glview->getFrameSize();

    // If the device is a Tablet
    if (screenSize.height > 768)
    {
        director->setContentScaleFactor(largeResolutionSize.height/designSize.height);
    }
    // If the device is a Phone with Hd Screen.
    else if (screenSize.height > 320)
    {
		    director->setContentScaleFactor(mediumResolutionSize.height / designSize.height);
    }
    // The device screen is a phone, with Simple Screen
    else
    {
        director->setContentScaleFactor(smallResolutionSize.height/designSize.height);
    }
}
