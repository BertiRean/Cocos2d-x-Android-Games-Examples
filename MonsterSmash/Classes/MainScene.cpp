#include "MainScene.h"
#include "GameBoard.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace cocos2d;


MainScene::MainScene()
{

}

MainScene::~MainScene()
{

}

Scene* MainScene::scene()
{
    auto scene = Scene::create();

    auto layer = MainScene::create();

    scene->addChild(layer);

    return scene;
}

bool MainScene::init()
{
    if(!Layer::init())
        return false;

    settingScreen();
    settingMenu();

    return true;
    
}

void MainScene::settingScreen()
{
    auto screenSize = Director::getInstance()->getWinSize();

    Sprite* background = Sprite::create("backgroundMonsters2.png");
    
    if(background != nullptr)
    {
        background->setPosition(Vec2(screenSize.width * 0.5f, screenSize.height* 0.5f));
        this->addChild(background, -2);
    }
}

void MainScene::settingMenu()
{
    auto screenSize = Director::getInstance()->getWinSize();

    auto logo = Sprite::create("MonsterSmashing.png");

    if(logo != nullptr)
    {
        logo->setPosition(Vec2(screenSize.width * 0.5f, screenSize.height * 0.8f));
        this->addChild(logo);
    }

    auto playButton = MenuItemImage::create("playButton.png", "playButtonSelect.png", CC_CALLBACK_1(MainScene::onPlayPress, this));
    
    auto soundOn = MenuItemImage::create("soundOn.png", "soundOnSelected.png");
    auto soundOff = MenuItemImage::create("soundOff.png", "soundOffSelected.png");

    soundOn->setTag(4);
    soundOff->setTag(5);


    auto toggle = MenuItemToggle::createWithTarget(this,
                menu_selector(MainScene::onSoundPress), soundOn, soundOff, NULL);

    auto menu = Menu::create(playButton, toggle, NULL);

    menu->setPosition(Vec2(screenSize.width * 0.5f, screenSize.height * 0.4f));
    menu->alignItemsVerticallyWithPadding(1.5f);

    this->addChild(menu);

    SimpleAudioEngine::getInstance()->playBackgroundMusic("backgroundSound.caf");
}


void MainScene::onPlayPress(Ref* sender)
{
    Scene* gameScene = GameBoard::scene();

    Director::getInstance()->replaceScene(TransitionFlipAngular::create(1.0f, gameScene));
}

void MainScene::onSoundPress(Ref* sender)
{
    MenuItemToggle* itemSelected = static_cast<MenuItemToggle*>(sender);

    if(itemSelected == nullptr)
        return;

    if(itemSelected->getSelectedIndex() == 0)
    {
        SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);
    }
    else if(itemSelected->getSelectedIndex() == 1)
    {
        SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    }
}