#include "StageOne.h"

#define TAG_ENEMY 1
#define TAG_MY_BULLET 2

USING_NS_CC;

StageOne::StageOne()
: m_targets(NULL)
, m_bullets(NULL)
, m_pSelf(NULL)
{

}

StageOne::~StageOne()
{

}
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
    m_pSelf = CCSprite::create("self_gay.png");
    m_pSelf->setPosition(ccp(visibleSize.width + origin.x - m_pSelf->getContentSize().width / 2, visibleSize.height / 2 + origin.y));
    this->addChild(m_pSelf);
    //m_pSelf->addChildToLayer(this);

    this->schedule(schedule_selector(StageOne::gameLogic), 1.0);

    this->setTouchEnabled(true);

    m_targets = new CCArray;
    m_bullets = new CCArray;

    // use updateGame instead of update, otherwise it will conflit with SelectorProtocol::update
    // see http://www.cocos2d-x.org/boards/6/topics/1478
    this->schedule(schedule_selector(StageOne::updateGame));

    this->schedule(schedule_selector(StageOne::shoot), 0.5);

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
    CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create(this,
        callfuncN_selector(StageOne::spriteMoveFinished));
    target->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));

    // Add to targets array
    target->setTag(TAG_ENEMY);
    m_targets->addObject(target);
}

void StageOne::updateGame(float dt)
{

}

void StageOne::shoot(float dt)
{
    // Set up initial location of projectile
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCSprite *bullet = CCSprite::create("bullet_soap.png");
    bullet->setPosition(ccp(m_pSelf->getPosition().x - m_pSelf->getContentSize().width/2 - bullet->getContentSize().width/2,
                            m_pSelf->getPosition().y));

    this->addChild(bullet);

    float length = bullet->getPosition().x - bullet->getContentSize().width/2;
    float velocity = 480 / 1; // 480pixels/1sec
    float realMoveDuration = length / velocity;
    bullet->runAction(CCSequence::create(CCMoveTo::create(realMoveDuration, ccp(0, bullet->getPosition().y)),
                                         CCCallFuncN::create(this, callfuncN_selector(StageOne::spriteMoveFinished)),
                                         NULL));
    bullet->setTag(TAG_MY_BULLET);
    m_bullets->addObject(bullet);
}

void StageOne::spriteMoveFinished(CCNode* sender)
{
    CCSprite* pSprite = (CCSprite*)sender;
    this->removeChild(pSprite);

    if (pSprite->getTag() == TAG_ENEMY)
    {
        m_targets->removeObject(pSprite);
    }
    else if (pSprite)
    {
    }
    switch (pSprite->getTag())
    {
    case TAG_ENEMY:
        {
            m_targets->removeObject(pSprite);
            break;
        }
    case TAG_MY_BULLET:
        {
            m_bullets->removeObject(pSprite);
            break;
        }
    default:
        break;
    }
}

void StageOne::ccTouchesBegin(CCSet* pTouches, CCEvent* pEvent)
{
    // Choose one of the touches to work with
    CCTouch* touch = (CCTouch*)(pTouches->anyObject());
    CCPoint location = touch->getLocation();
    m_pSelf->setPosition(ccp(location.x, location.y));
}

void StageOne::ccTouchesEnded(CCSet* pTouches, CCEvent* pEvent)
{
    // Choose one of the touches to work with
    CCTouch* touch = (CCTouch*)(pTouches->anyObject());
    CCPoint location = touch->getLocation();
    m_pSelf->setPosition(ccp(location.x, location.y));
}

void StageOne::ccTouchesMoved(CCSet* pTouches, CCEvent* pEvent)
{
    // Choose one of the touches to work with
    CCTouch* touch = (CCTouch*)(pTouches->anyObject());
    CCPoint location = touch->getLocation();
    m_pSelf->setPosition(ccp(location.x, location.y));
}

