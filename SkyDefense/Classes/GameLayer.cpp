#include "GameLayer.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

Scene* GameLayer::createScene()
{
    Scene* scene = Scene::create();

    GameLayer* layer = GameLayer::create();

    scene->addChild(layer);

    return scene;
}

bool GameLayer::init()
{
    if (!Layer::init())
        return false;

    settingScreen();

    SimpleAudioEngine::getInstance()->playBackgroundMusic("background.mp3", true);

    return true;
}

void GameLayer::settingScreen()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    Sprite* background = Sprite::create("bg.png");

    background->setPosition(visibleSize.width / 2, visibleSize.height / 2);

    this->addChild(background);
}