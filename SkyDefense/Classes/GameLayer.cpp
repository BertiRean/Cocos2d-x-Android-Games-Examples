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

  addGameElements();

  SimpleAudioEngine::getInstance()->playBackgroundMusic("background.mp3", true);

  return true;
}

void GameLayer::addGameElements()
{
  Size visibleSize = Director::getInstance()->getVisibleSize();

  Sprite* background = Sprite::create("bg.png");

  background->setPosition(visibleSize.width / 2, visibleSize.height / 2);

  this->addChild(background);

  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_sheet.plist");
  
  _gameBatchNode = SpriteBatchNode::create("sprite_sheet.png");

  this->addChild(_gameBatchNode);

  for (uint8_t i = 0; i < 2; ++i)
  {
    Sprite* gameElement = Sprite::createWithSpriteFrameName("city_dark.png");

    gameElement->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);

    gameElement->setPosition(visibleSize.width * (0.25f + i * 0.5f), 0);

    _gameBatchNode->addChild(gameElement, FOREGROUND);

    gameElement = Sprite::createWithSpriteFrameName("city_light.png");

    gameElement->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);

    gameElement->setPosition(Vec2(visibleSize.width * (0.25f + i * 0.5f),
                                  visibleSize.height * 0.1f));

    _gameBatchNode->addChild(gameElement, BACKGROUND);
  }

  // Drawing the trees for the background

  for (int i = 0; i < 3; ++i)
  {
    Sprite* tree = Sprite::createWithSpriteFrameName("trees.png");

    tree->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);

    tree->setPosition(Vec2(visibleSize.width * (0.2f + i * 0.3f), 
                           0));

    _gameBatchNode->addChild(tree, FOREGROUND);
  }
}
