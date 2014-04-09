#include "StageOne.h"

USING_NS_CC;

CCScene* StageOne::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();

    // 'layer' is an autorelease object
    StageOne *layer = StageOne::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StageOne::init()
{
    // 1. super init first
    if (!CCLayer::init())
    {
        return false;
    }

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();


    // add a label
    // create and initialize a label

    CCLabelTTF* pLabel = CCLabelTTF::create("STAGE 1", "Arial", 24);

    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

//     // add "HelloWorld" splash screen"
//     CCSprite* pSprite = CCSprite::create("StartPage.png");
// 
//     // position the sprite on the center of the screen
//     pSprite->setPosition(ccp(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
// 
//     // add the sprite as a child to this layer
//     this->addChild(pSprite, 0);

    return true;
}


void StageOne::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
