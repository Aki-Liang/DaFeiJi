#include "Self.h"

USING_NS_CC;


Self::Self()
: m_spSelf(NULL)
, m_iKidneyForce(0)
{
}


Self::~Self()
{
}

bool Self::init()
{
    bool bRet = false;

    do 
    {
        //create sprite by png
        m_spSelf = CCSprite::create("self_gay.png");
        if (NULL == m_spSelf)
        {
            //creat failed
            break;
        }
        bRet = true;
    } while (0);
    
    return bRet;
}

void Self::setPosition(const  CCPoint& pos)
{
    m_spSelf->setPosition(pos);
}
const CCSize& Self::getContentSize()
{
    return m_spSelf->getContentSize();
}

// CCSprite*& Self::getSprite()
// {
//     return m_spSelf;
// }

void Self::addChildToLayer(CCLayer* pLayer)
{
    pLayer->addChild(m_spSelf);
}

void Self::shoot()
{
    //TODO
}

Self* Self::create()
{
    Self* pRet = new Self;
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

void addKidneyForce(int iForce)
{
    //TODO
}

