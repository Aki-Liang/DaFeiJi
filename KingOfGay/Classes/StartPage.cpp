#include "StartPage.h"
#include "StageOne.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

StartPage::StartPage()
:m_pLabel(NULL)
{

}

StartPage::~StartPage()
{

}

CCScene* StartPage::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();

    // 'layer' is an autorelease object
    StartPage *layer = StartPage::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartPage::init()
{
    //////////////////////////////
    // 1. super init first
    if (!CCLayer::init())
    {
        return false;
    }

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
//     CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
//         "CloseNormal.png",
//         "CloseSelected.png",
//         this,
//         menu_selector(StartPage::menuCloseCallback));
// 
//     pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width / 2,
//         origin.y + pCloseItem->getContentSize().height / 2));
// 
//     // create menu, it's an autorelease object
//     CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
//     pMenu->setPosition(CCPointZero);
//     this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    m_pLabel = CCLabelTTF::create("Touch to start", "Arial", 24);

    // position the label on the center of the screen
    m_pLabel->setPosition(ccp(origin.x + visibleSize.width / 2,
        origin.y + m_pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(m_pLabel, 1);

    this->schedule(schedule_selector(StartPage::Blink), 1.0);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("StartPage.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);

    this->setTouchEnabled(true);

    //play BGM
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("startpage_bgm.mp3", true);

    return true;
}


// void StartPage::menuCloseCallback(CCObject* pSender)
// {
// // #if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
// //     CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
// // #else
// //     CCDirector::sharedDirector()->end();
// // #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
// //     exit(0);
// // #endif
// // #endif
//     
// }

void StartPage::ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("GameStart.wav");
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, StageOne::scene()));
}

void StartPage::Blink(float dt)
{
    CCBlink* pBlink = CCBlink::create(1.0f, 1);
    m_pLabel->runAction(pBlink);
}

