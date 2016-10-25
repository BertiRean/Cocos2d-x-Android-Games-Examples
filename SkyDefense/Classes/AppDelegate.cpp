#include "AppDelegate.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

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

bool AppDelegate::applicationDidFinishLaunching() 
{
    // initialize director
    Director* director = Director::getInstance();
    GLView* glview = director->getOpenGLView();

    if(!glview) 
    {
        glview = GLViewImpl::create("SkyDefense");
        director->setOpenGLView(glview);
    }

    // Set the design resolution and preload the sounds
    settingScreen();
    settingSound();

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = GameLayer::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() 
{
    Director::getInstance()->stopAnimation();
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() 
{
    Director::getInstance()->startAnimation();
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void AppDelegate::settingScreen()
{
    Director* director = Director::getInstance();
    GLView* glview = director->getOpenGLView();
    FileUtils* fileUtils = FileUtils::getInstance();

    Size designSize(2048, 1536);

    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::EXACT_FIT);

    const Size & screenSize = glview->getFrameSize();

    // If the device is a Tablet
    if (screenSize.height > 768)
    {
        fileUtils->addSearchPath("xhd");
        director->setContentScaleFactor(largeResolutionSize.height/designSize.height);
    }
    // If the device is a Phone with Hd Screen.
    else if (screenSize.height > 320)
    {
        fileUtils->addSearchPath("hd");
		    director->setContentScaleFactor(mediumResolutionSize.height / designSize.height);
    }
    // The device screen is a phone, with Simple Screen
    else
    {
        fileUtils->addSearchPath("sd");
        director->setContentScaleFactor(smallResolutionSize.height/designSize.height);
    }
}

void AppDelegate::settingSound()
{
    FileUtils::getInstance()->addSearchPath("sounds");

    SimpleAudioEngine* audioManager = SimpleAudioEngine::getInstance();

    audioManager->preloadBackgroundMusic("background.mp3");
    audioManager->setBackgroundMusicVolume(0.4f);
}
