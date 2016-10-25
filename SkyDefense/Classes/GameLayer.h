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

    cocos2d::SpriteBatchNode* _gameBatchNode;

};

#endif // !__GAME_LAYER__H
