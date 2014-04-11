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

    this->schedule(schedule_selector(StageOne::shoot), 0.1);

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
    CCArray* bulletToDelete = new CCArray;
    CCObject* iterBullet = NULL;
    CCObject* iterEnemy = NULL;

    CCARRAY_FOREACH(m_bullets, iterBullet)
    {
        CCSprite* pBullet = dynamic_cast<CCSprite*>(iterBullet);

        float fX = 0;
        float fY = 0;
        float fWidth = 0;
        float fHeight = 0;

        fX = pBullet->getPosition().x - (pBullet->getContentSize().width / 2);
        if (fX < 0)
        {
            if (pBullet->getPosition().x < 0)
            {
                fWidth = pBullet->getContentSize().width + pBullet->getPosition().x;
            }
            else
            {
                fWidth = pBullet->getContentSize().width / 2 + pBullet->getPosition().x;
            }
            fX = 0;
        }
        else
        {
            fWidth = pBullet->getContentSize().width;
        }

        fY = pBullet->getPosition().y - (pBullet->getContentSize().height / 2);
        if (fY < 0)
        {
            if (pBullet->getPosition().y < 0)
            {
                fWidth = pBullet->getContentSize().height + pBullet->getPosition().y;
            }
            else
            {
                fWidth = pBullet->getContentSize().height / 2 + pBullet->getPosition().y;
            }
            fY = 0;
        }
        else
        {
            fHeight = pBullet->getContentSize().height;
        }


        CCRect bulletRect = CCRectMake(fX, fY, fWidth, fHeight);

        CCArray* targetsToDelete = new CCArray;

        CCARRAY_FOREACH(m_targets, iterEnemy)
        {
            CCSprite* pEnemy = dynamic_cast<CCSprite*>(iterEnemy);
            CCRect enemyRect = CCRectMake(
                pEnemy->getPosition().x - (pEnemy->getContentSize().width / 2),
                pEnemy->getPosition().y - (pEnemy->getContentSize().height / 2),
                pEnemy->getContentSize().width,
                pEnemy->getContentSize().height);

            if (bulletRect.intersectsRect(enemyRect))
            {
                targetsToDelete->addObject(iterEnemy);
            }
        }

        CCARRAY_FOREACH(targetsToDelete, iterEnemy)
        {
            CCSprite* pEnemy = dynamic_cast<CCSprite*>(iterEnemy);
            m_targets->removeObject(pEnemy);
            this->removeChild(pEnemy, true);
        }

        if (targetsToDelete->count()>0)
        {
            bulletToDelete->addObject(pBullet);
        }
        targetsToDelete->release();
    }

    CCARRAY_FOREACH(bulletToDelete, iterBullet)
    {
        CCSprite* pBullet = dynamic_cast<CCSprite*>(iterBullet);
        m_targets->removeObject(pBullet);
        this->removeChild(pBullet, true);
    }
    bulletToDelete->release();
}

void StageOne::shoot(float dt)
{
    // Set up initial location of projectile
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCSprite *bullet = CCSprite::create("bullet_soap.png");

    bullet->setPosition(ccp(m_pSelf->getPosition().x - m_pSelf->getContentSize().width/2 - bullet->getContentSize().width/2,
                            m_pSelf->getPosition().y));

    float length = bullet->getPosition().x + bullet->getContentSize().width / 2;
    float velocity = winSize.width / 1; // winSize.width/1sec
    float realMoveDuration = length / velocity;
    bullet->runAction(CCSequence::create(CCMoveTo::create(realMoveDuration, ccp(0, bullet->getPosition().y)),
                                         CCCallFuncN::create(this, callfuncN_selector(StageOne::spriteMoveFinished)),
                                         NULL));
//     bullet->runAction(CCSequence::create(CCMoveBy::create(realMoveDuration, ccp(-winSize.width, 0)),
//                                          CCCallFuncN::create(this, callfuncN_selector(StageOne::spriteMoveFinished)),
//                                          NULL));
    bullet->setTag(TAG_MY_BULLET);
    m_bullets->addObject(bullet);
    this->addChild(bullet);
}

void StageOne::spriteMoveFinished(CCNode* sender)
{
    CCSprite* pSprite = (CCSprite*)sender;
    this->removeChild(pSprite);

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
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
    // Choose one of the touches to work with
    CCTouch* touch = (CCTouch*)(pTouches->anyObject());
    CCPoint location = touch->getLocation();
    float fX = 0;
    float fY = 0;
    if (location.x < m_pSelf->getContentSize().width / 2)
    {
        fX = m_pSelf->getContentSize().width / 2;
    }
    else if (winSize.width - m_pSelf->getContentSize().width / 2 < location.x)
    {
        fX = winSize.width - m_pSelf->getContentSize().width / 2;
    }
    else
    {
        fX = location.x;
    }

    if (location.y < m_pSelf->getContentSize().height / 2)
    {
        fY = m_pSelf->getContentSize().height / 2;
    }
    else if (winSize.height - m_pSelf->getContentSize().height / 2 < location.y)
    {
        fY = winSize.height - m_pSelf->getContentSize().height / 2;
    }
    else
    {
        fY = location.y;
    }
    m_pSelf->setPosition(ccp(fX, fY));
}

void StageOne::ccTouchesEnded(CCSet* pTouches, CCEvent* pEvent)
{
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
    // Choose one of the touches to work with
    CCTouch* touch = (CCTouch*)(pTouches->anyObject());
    CCPoint location = touch->getLocation();
    float fX = 0;
    float fY = 0;
    if (location.x < m_pSelf->getContentSize().width / 2)
    {
        fX = m_pSelf->getContentSize().width / 2;
    }
    else if (winSize.width - m_pSelf->getContentSize().width / 2 < location.x)
    {
        fX = winSize.width - m_pSelf->getContentSize().width / 2;
    }
    else
    {
        fX = location.x;
    }

    if (location.y < m_pSelf->getContentSize().height / 2)
    {
        fY = m_pSelf->getContentSize().height / 2;
    }
    else if (winSize.height - m_pSelf->getContentSize().height / 2 < location.y)
    {
        fY = winSize.height - m_pSelf->getContentSize().height / 2;
    }
    else
    {
        fY = location.y;
    }
    m_pSelf->setPosition(ccp(fX, fY));
}

void StageOne::ccTouchesMoved(CCSet* pTouches, CCEvent* pEvent)
{
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
    // Choose one of the touches to work with
    CCTouch* touch = (CCTouch*)(pTouches->anyObject());
    CCPoint location = touch->getLocation();
    float fX = 0;
    float fY = 0;
    if (location.x < m_pSelf->getContentSize().width/2)
    {
        fX = m_pSelf->getContentSize().width/2;
    }
    else if (winSize.width - m_pSelf->getContentSize().width/2 < location.x)
    {
        fX = winSize.width - m_pSelf->getContentSize().width/2;
    }
    else
    {
        fX = location.x;
    }

    if (location.y < m_pSelf->getContentSize().height/2)
    {
        fY = m_pSelf->getContentSize().height/2;
    }
    else if (winSize.height - m_pSelf->getContentSize().height/2 < location.y)
    {
        fY = winSize.height - m_pSelf->getContentSize().height/2;
    }
    else
    {
        fY = location.y;
    }
    m_pSelf->setPosition(ccp(fX, fY));
}

