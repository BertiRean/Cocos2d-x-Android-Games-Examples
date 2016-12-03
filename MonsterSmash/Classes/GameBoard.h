#ifndef _GAME_BOARD_H
#define _GAME_BOARD_H

#include "cocos2d.h"
#include "Monster.h"

using Touches = std::vector<cocos2d::Touch*>;

static constexpr int MAX_LIVES = 3;

class GameBoard : public cocos2d::Layer
{
    public:
        GameBoard();
        virtual ~GameBoard();
        CREATE_FUNC(GameBoard);
        static cocos2d::Scene* scene();
        virtual bool init() override;
        void onTouchesBegan(const Touches & , cocos2d::Event*) override;
        void onEnter() override;

    private:
        void settingScreen();
        void createMonsters();
        void spawnMonsters(float dt);
        void killMonsters(cocos2d::Vector<Node*> & monsters);
        void removeMonster(cocos2d::Node*, bool);
        void createSplash(const char*, const cocos2d::Vec2 &);
        void createLabels();
        void decreaseLive();
        void onPausePressed(cocos2d::Ref* );

        cocos2d::Vector<Monster*> _monsters;
        cocos2d::Vector<cocos2d::Node*> _monstersOnScreen;
        cocos2d::Vector<cocos2d::Sprite*> _healths;

        uint8_t _lives;
};



#endif // !_GAME_LAYER_H