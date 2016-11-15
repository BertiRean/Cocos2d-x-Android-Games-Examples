#ifndef __GAME_LAYER__H
#define __GAME_LAYER__H

#include "cocos2d.h"


enum BackgroundScreens
{
  BACKGROUND,
  MIDDLEGROUND,
  FOREGROUND
};



class GameLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    
    CREATE_FUNC(GameLayer)

private:
    void addGameElements();
    void createBackgroundElements();
    void createLabels();

    cocos2d::SpriteBatchNode* _gameBatchNode;
    
    cocos2d::Label* _scoreLabel; 
    cocos2d::Label* _energyLabel;

    cocos2d::Vector<cocos2d::Sprite*> _clouds;

    cocos2d::Sprite* _bomb;
    cocos2d::Sprite* _introMessage;
    cocos2d::Sprite* _gameOverMessage;

};

#endif // !__GAME_LAYER__H
