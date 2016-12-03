#include "GameBoard.h"
#include "Monster.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "PauseScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

GameBoard::GameBoard()
{

}

GameBoard::~GameBoard()
{
    _monsters.clear();
    _monstersOnScreen.clear();
    _healths.clear();
}

Scene* GameBoard::scene()
{
    auto scene = Scene::create();

    auto layer = GameBoard::create();

    scene->addChild(layer);

    return scene;
}

bool GameBoard::init()
{
    if(!Layer::init())
        return false;

    settingScreen();
    createMonsters();

    this->schedule(schedule_selector(GameBoard::spawnMonsters), 1.0f);

    return true;
    
}

void GameBoard::onTouchesBegan(const Touches & touches, Event* event)
{
    Vector<Node*> monstersToKill;

    Touch* touch = touches.front();

    Point tap = this->convertTouchToNodeSpace(touch);

    for(auto & itr : _monstersOnScreen)
    {
        if(itr->getBoundingBox().containsPoint(tap))
        {
            monstersToKill.pushBack(itr);

            if(itr->getTag() == 1)
                createSplash("splashMonsterGreen.png", itr->getPosition());
            else if(itr->getTag() == 2)
                createSplash("splashMonsterBlue.png", itr->getPosition());
            else if(itr->getTag() == 3)
                createSplash("splashMonsterRed.png", itr->getPosition());
            break;
        }
    }
    
    killMonsters(monstersToKill);
}

void GameBoard::onEnter()
{
    Layer::onEnter();

    EventListenerTouchAllAtOnce* listener =  EventListenerTouchAllAtOnce::create();

    listener->onTouchesBegan = CC_CALLBACK_2(GameBoard::onTouchesBegan, this);

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameBoard::settingScreen()
{
    const Size & winSize = Director::getInstance()->getWinSize();

    Sprite* background = Sprite::create("WoodRetroApple_iPad_HomeScreen.jpg");

    background->setPosition(winSize.width * 0.5f, winSize.height * 0.5f);

    this->addChild(background, -2);

    createLabels();

    auto pauseButton = MenuItemImage::create("pauseButton.png", "pauseButton.png", CC_CALLBACK_1(GameBoard::onPausePressed, this));

    auto pauseMenu = Menu::create(pauseButton, NULL);

    pauseMenu->setPosition(Vec2(winSize.width * 0.95f, winSize.height * 0.95f));

    this->addChild(pauseMenu);
}

void GameBoard::createMonsters()
{
    Monster* monster1 = Monster::create();
    
    monster1->setSpriteName("monsterGreen.png");
    monster1->setSplashName("splashMonsterGreen.png");
    monster1->setMinVelocity(2.0f);
    monster1->setMaxVelocity(8.0f);
    monster1->setMovement(1);
    monster1->setKillMethod(1);
    monster1->setTag(1);

    Monster* monster2 = Monster::create();
    monster2->setSpriteName("monsterBlue.png");
    monster2->setSplashName("splashMonsterBlue.png");
    monster2->setMinVelocity(2.0f);
    monster2->setMaxVelocity(8.0f);
    monster2->setMovement(1);
    monster2->setKillMethod(2);
    monster2->setTag(2);

    Monster* monster3 = Monster::create();
    monster3->setSpriteName("monsterRed.png");
    monster3->setSplashName("splashMonsterRed.png");
    monster3->setMinVelocity(3.0f);
    monster3->setMaxVelocity(6.0f);
    monster3->setMovement(2);
    monster3->setKillMethod(1);
    monster3->setTag(3);

    _monsters.pushBack(monster1);
    _monsters.pushBack(monster2);
    _monsters.pushBack(monster3);
}

void GameBoard::spawnMonsters(float dt)
{
    int index = cocos2d::RandomHelper::random_int(0, 2);
    Monster* monster = _monsters.at(index);

    Sprite* monsterToSpawn = Sprite::create(monster->getSpriteName());

    monsterToSpawn->setTag(monster->getTag());

    int movementType = monster->getMovement();

    const Size & winSize = Director::getInstance()->getWinSize();

    int minX = monsterToSpawn->getContentSize().width;
    int maxX = winSize.width - monsterToSpawn->getContentSize().width/2;

    int posX = cocos2d::RandomHelper::random_int(minX, maxX);

    int minVelocity = monster->getMinVelocity();
    int maxVelocity = monster->getMaxVelocity();

    int actualDuration = cocos2d::RandomHelper::random_int(minVelocity, maxVelocity);


    if(movementType == 1)
    {
        monsterToSpawn->setPosition(Vec2(posX, winSize.height + monsterToSpawn->getContentSize().height));
        this->addChild(monsterToSpawn);
        
        MoveTo* downMove = MoveTo::create(actualDuration, Vec2(posX, -monsterToSpawn->getContentSize().height/2));

        CallFuncN* disappearOnBottom = CallFuncN::create(CC_CALLBACK_1(GameBoard::removeMonster, this, true));

        monsterToSpawn->runAction(Sequence::create(downMove, disappearOnBottom, NULL));

        _monstersOnScreen.pushBack(monsterToSpawn);
    }
    else if(movementType == 2)
    {
        monsterToSpawn->setPosition(Vec2(posX, winSize.height + monsterToSpawn->getContentSize().height/2));
        
        this->addChild(monsterToSpawn);

        CallFuncN* disappearOnBottom = CallFuncN::create(CC_CALLBACK_1(GameBoard::removeMonster, this, true));

        Vector<FiniteTimeAction*> beziers;

        ccBezierConfig bezier;

        BezierTo* bezierAction;

        float splitDuration = actualDuration / 6.0f ;

        for(u_int8_t i = 0; i < 8; ++i)
        {
            if(i % 2 == 0)
            {
                bezier.controlPoint_1 = Vec2(posX + 100, winSize.height - (100 + (200*i) ) );
                bezier.controlPoint_2 = Vec2(posX + 100, winSize.height - (100 + (200*i) ) );
                bezier.endPosition = Vec2(posX, winSize.height - (200 + (i*200)) );

                bezierAction = BezierTo::create(splitDuration, bezier);
            }
            else
            {
                bezier.controlPoint_1 = Vec2(posX - 100, winSize.height - (100 + (200*i) ) );
                bezier.controlPoint_2 = Vec2(posX - 100, winSize.height - (100 + (200*i) ) );
                bezier.endPosition = Vec2(posX, winSize.height - (200 + (i*200)) );
                
                bezierAction = BezierTo::create(splitDuration, bezier);
            }

            beziers.pushBack(bezierAction);
        }

        beziers.pushBack(disappearOnBottom);

        monsterToSpawn->runAction(Sequence::create(beziers));

        _monstersOnScreen.pushBack(monsterToSpawn);
    }
}

void GameBoard::killMonsters(Vector<Node*> & monsters)
{
    for(auto monster : monsters)
    {
        monster->stopAllActions();
        _monstersOnScreen.erase(_monstersOnScreen.find(monster));
        monster->removeFromParentAndCleanup(true);
    }
}

void GameBoard::removeMonster(Node* sender, bool cleanup)
{
    _monstersOnScreen.erase(_monstersOnScreen.find(sender));
    sender->removeFromParentAndCleanup(true);
    decreaseLive();
}

void GameBoard::createSplash(const char* splashName, const Vec2 & position)
{
    Sprite* splash = Sprite::create(splashName);

    if(splash == nullptr)
        return;
            
    splash->setPosition(position);

    this->addChild(splash);

    FadeOut* fade = FadeOut::create(3.0f);

    CallFuncN* despawn = CallFuncN::create([this] (Node* sender)
    {
        this->removeChild(sender, true);
    });

    Sequence* actionSequence = Sequence::create(fade, despawn, NULL);

    splash->runAction(actionSequence);
    SimpleAudioEngine::getInstance()->playEffect("SplatEffect.caf");
}

void GameBoard::createLabels()
{
    const Size & winSize = Director::getInstance()->getWinSize();

    _lives = MAX_LIVES;

    for(u_int8_t i = 0; i < 3; ++i)
    {
        Sprite* health = Sprite::create("hearth.png");
        _healths.pushBack(health);

        health->setPosition(Vec2(  (i+1) * 75 , winSize.height * 0.95f));
        this->addChild(health);
    }
}

void GameBoard::decreaseLive()
{
    _lives--;
    this->removeChild(_healths.back(), true);
    _healths.popBack();

    if(_lives == 0)
    {
        auto scene = MainScene::scene();
        Director::getInstance()->replaceScene(scene);
    }
}

void GameBoard::onPausePressed(Ref* sender)
{
    auto director = Director::getInstance();

    if(!director->isPaused())
    {
        this->pauseSchedulerAndActions();
        auto scene = PauseScene::scene();
        director->pushScene(scene);        
    }
    else
    {
        director->stopAnimation();
        director->resume();
        director->startAnimation();
    }
}














