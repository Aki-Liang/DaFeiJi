#ifndef __STAGE_ONE_H__
#define __STAGE_ONE_H__

#include "cocos2d.h"
#include "Self.h"

class StageOne : public cocos2d::CCLayer
{
public:

    StageOne();
    ~StageOne();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();

    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(StageOne);

    void gameLogic(float dt);
    void updateGame(float dt);
    void shoot(float dt);

    void spriteMoveFinished(cocos2d::CCNode* sender);

    void ccTouchesEnded(cocos2d::CCSet* pTouches, cocos2d::CCEvent* pEvent);
    void ccTouchesMoved(cocos2d::CCSet* pTouches, cocos2d::CCEvent* pEvent);
    void ccTouchesBegin(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

private:
    cocos2d::CCArray* m_targets;
    cocos2d::CCArray* m_bullets;
    cocos2d::CCSprite* m_pSelf;
};

#endif // __STAGE_ONE_H__

