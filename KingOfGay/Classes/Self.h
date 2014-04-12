#ifndef __SELF_H__
#define __SELF_H__

#include "cocos2d.h"

class Self : public cocos2d::CCObject
{
public:
    Self();
    ~Self();

    virtual bool init();

    void setPosition(const  cocos2d::CCPoint& pos);

    const cocos2d::CCSize& getContentSize();

    //cocos2d::CCSprite*& getSprite();
    void addChildToLayer(cocos2d::CCLayer* pLayer);

    void shoot();

    void addKidneyForce(int iForce);

public:
    static Self* create();

private:
    cocos2d::CCSprite* m_spSelf;
    int m_iKidneyForce;
};


#endif // !__SELF_H__
