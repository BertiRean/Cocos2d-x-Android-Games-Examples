#include "PauseScene.h"
#include "SimpleAudioEngine.h"
#include "MainScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

PauseScene::PauseScene()
{

}

PauseScene::~PauseScene()
{

}

Scene* PauseScene::scene()
{
    auto scene = Scene::create();

    auto layer = PauseScene::create();

    scene->addChild(layer);

    return scene;
}

bool PauseScene::init()
{
    if(!Layer::init())
        return false;

    settingScreen();

    return true;
}

void PauseScene::settingScreen()
{
    const Size & winSize = Director::getInstance()->getWinSize();

    Sprite* background = Sprite::create("WoodRetroApple_iPad_HomeScreen.jpg");

    background->setPosition(winSize.width * 0.5f, winSize.height * 0.5f);

    this->addChild(background, -2);

    auto logo = Sprite::create("MonsterSmashing.png");

    if(logo != nullptr)
    {
        logo->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.8f));
        this->addChild(logo);
    }

    MenuItem* resumeButton = MenuItemImage::create("resume.png", "resume.png", CC_CALLBACK_1(PauseScene::onResumePressed, this));
    MenuItem* exitButton = MenuItemImage::create("exit.png", "exit.png", CC_CALLBACK_1(PauseScene::onExitPressed, this));

    Menu* menu = Menu::create(resumeButton, exitButton, NULL);

    menu->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.4f));
    menu->alignItemsVerticallyWithPadding(1.5f);

    this->addChild(menu);
}

void PauseScene::onResumePressed(Ref* sender)
{
    Director::getInstance()->popScene();
}

void PauseScene::onExitPressed(Ref* sender)
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    auto initialScene = MainScene::scene();

    Director::getInstance()->replaceScene(initialScene);
}