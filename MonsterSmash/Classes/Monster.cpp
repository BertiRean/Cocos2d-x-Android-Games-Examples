#include "Monster.h"

Monster::Monster()
{

}


Monster::~Monster()
{

}

const int & Monster::getMovement() const
{
    return this->_movement;
}

const int & Monster::getKillMethod() const
{
    return this->_killMethod;
}

const float & Monster::getMinVelocity() const
{
    return this->_minVelocity;
}

const float & Monster::getMaxVelocity() const
{
    return this->_maxVelocity;
}

const char* Monster::getSpriteName()
{
    return this->_spriteName;
}

const char* Monster::getSplashName()
{
    return this->_splashName;
}

void Monster::setSpriteName(const char* spriteName)
{
    this->_spriteName = spriteName;
}

void Monster::setSplashName(const char* splashName)
{
    this->_splashName = splashName;
}

void Monster::setMovement(int movement)
{
    this->_movement = movement;
}

void Monster::setMinVelocity(float minVelocity)
{
    this->_minVelocity = minVelocity;
}

void Monster::setMaxVelocity(float maxVelocity)
{
    this->_maxVelocity = maxVelocity;
}

void Monster::setKillMethod(int killMethod)
{
    this->_killMethod = killMethod;
}



