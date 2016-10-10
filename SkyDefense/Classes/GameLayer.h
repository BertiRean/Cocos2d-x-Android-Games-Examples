#ifndef __GAME_LAYER__H
#define __GAME_LAYER__H

#include "cocos2d.h"


class GameLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameLayer)

private:
    void settingScreen();

};

#endif // !__GAME_LAYER__H
