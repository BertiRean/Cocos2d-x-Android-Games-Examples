#ifndef _MONSTER_H
#define _MONSTER_H

#include "cocos2d.h"

class Monster : public cocos2d::Node
{
    public:
        Monster();
        virtual ~Monster();

        CREATE_FUNC(Monster)

        const int & getMovement() const;
        const int & getKillMethod() const;
        const float & getMinVelocity() const;
        const float & getMaxVelocity() const;
        const char* getSpriteName();
        const char* getSplashName();

        void setSpriteName(const char*);
        void setSplashName(const char*);
        void setMovement(int movement);
        void setMinVelocity(float minVelocity);
        void setMaxVelocity(float maxVelocity);
        void setKillMethod(int killmethod);
        

    private:
        int _movement;
        float _minVelocity;
        float _maxVelocity;
        int _killMethod;
        const char* _spriteName;
        const char* _splashName;
};

#endif // !