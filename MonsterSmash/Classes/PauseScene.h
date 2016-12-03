#ifndef _PAUSE_SCENE_H
#define _PAUSE_SCENE_H

#include "cocos2d.h"

class PauseScene : public cocos2d::Layer
{
    public:
        PauseScene();
        virtual ~PauseScene();
        CREATE_FUNC(PauseScene);
        static cocos2d::Scene* scene();
        virtual bool init() override;

    private:
        void settingScreen();
        void onResumePressed(cocos2d::Ref* );
        void onExitPressed(cocos2d::Ref* );
};



#endif // !_PAUSE_SCENE_H