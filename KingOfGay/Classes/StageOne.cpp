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

    //add self_gay
    m_spSelf = CCSprite::create("self_gay.png");
    m_spSelf->setPosition(ccp(visibleSize.width + origin.x - m_spSelf->boundingBox().size.width / 2, visibleSize.height / 2 + origin.y));
    this->addChild(m_spSelf, 0);

    this->schedule(schedule_selector(StageOne::gameLogic), 1.0);

    this->setTouchEnabled(true);

    m_targets = new CCArray;

    // use updateGame instead of update, otherwise it will conflit with SelectorProtocol::update
    // see http://www.cocos2d-x.org/boards/6/topics/1478
    this->schedule(schedule_selector(StageOne::updateGame));

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

void StageOne::gameLogic(float dt)
{
    CCSprite *target = CCSprite::create("enemy_sister.png");

    // Determine where to spawn the target along the Y axis
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
    float minY = target->getContentSize().height / 2;
    float maxY = winSize.height - target->getContentSize().height / 2;
    int rangeY = (int)(maxY - minY);
    // srand( TimGetTicks() );
    int actualY = (rand() % rangeY) + (int)minY;

    // Create the target slightly off-screen along the right edge,
    // and along a random position along the Y axis as calculated
    target->setPosition(
        ccp(0 - (target->getContentSize().width / 2),
        CCDirector::sharedDirector()->getVisibleOrigin().y + actualY));
    this->addChild(target);

    // Determine speed of the target
    int minDuration = (int)2.0;
    int maxDuration = (int)4.0;
    int rangeDuration = maxDuration - minDuration;
    // srand( TimGetTicks() );
    int actualDuration = (rand() % rangeDuration) + minDuration;

    // Create the actions
    CCFiniteTimeAction* actionMove = CCMoveTo::create((float)actualDuration,
        ccp(winSize.width + target->getContentSize().width / 2, actualY));
//     CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create(this,
//         callfuncN_selector(HelloWorld::spriteMoveFinished));
//    target->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
    target->runAction(CCSequence::create(actionMove, NULL));

    // Add to targets array
    target->setTag(1);
    m_targets->addObject(target);
}

void StageOne::updateGame(float dt)
{

}

void StageOne::ccTouchesBegin(CCSet* pTouches, CCEvent* pEvent)
{
    // Choose one of the touches to work with
    CCTouch* touch = (CCTouch*)(pTouches->anyObject());
    CCPoint location = touch->getLocation();
    m_spSelf->setPosition(ccp(location.x, location.y));
}

void StageOne::ccTouchesEnded(CCSet* pTouches, CCEvent* pEvent)
{
    // Choose one of the touches to work with
    CCTouch* touch = (CCTouch*)(pTouches->anyObject());
    CCPoint location = touch->getLocation();
    m_spSelf->setPosition(ccp(location.x, location.y));
}

void StageOne::ccTouchesMoved(CCSet* pTouches, CCEvent* pEvent)
{
    // Choose one of the touches to work with
    CCTouch* touch = (CCTouch*)(pTouches->anyObject());
    CCPoint location = touch->getLocation();
    m_spSelf->setPosition(ccp(location.x, location.y));
}

