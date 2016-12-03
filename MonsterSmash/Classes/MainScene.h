#ifndef _GAME_LAYER_H
#define _GAME_LAYER_H

#include "cocos2d.h"

class MainScene : public cocos2d::Layer
{
    public:
        MainScene();
        virtual ~MainScene();
        CREATE_FUNC(MainScene);
        static cocos2d::Scene* scene();
        virtual bool init() override;

    private:
        void settingScreen();
        void settingMenu();
        void onPlayPress(cocos2d::Ref*);
        void onSoundPress(cocos2d::Ref*);
};



#endif // !_GAME_LAYER_H