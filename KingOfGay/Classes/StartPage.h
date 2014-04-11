#ifndef __STARTPAGE_H__
#define __STARTPAGE_H__

#include "cocos2d.h"

class StartPage : public cocos2d::CCLayer
{
public:
    StartPage();
    ~StartPage();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();

    // a selector callback
    //void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(StartPage);

    void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);

    void Blink(float dt);

private:
    cocos2d::CCLabelTTF* m_pLabel;
};

#endif // __STARTPAGE_H__

