#include "G4PictureMatching.h"
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;


G4PictureMatching::G4PictureMatching():mAnimationManager(NULL), scoreFont(NULL), logo(NULL), littlePullRope(NULL)
{
    target = NULL;
    callbackFunc = NULL;
}
G4PictureMatching::~G4PictureMatching()
{
    CCLog("~G4PictureMatching()");
    
    CC_SAFE_RELEASE_NULL(mAnimationManager);
    
    CC_SAFE_RELEASE_NULL(scoreFont);
    CC_SAFE_RELEASE_NULL(logo);
    CC_SAFE_RELEASE_NULL(littlePullRope);
    
    target = NULL;
    callbackFunc = NULL;
}

CCNode* G4PictureMatching::node()
{
    CCNode* thisNode = CCNode::create();
    
    CCNodeLoaderLibrary* lib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    lib->registerCCNodeLoader("G4PictureMatching", G4PictureMatchingLoader::loader());
    CCBReader* reader = new CCBReader(lib);
    G4PictureMatching* g4PictureMatchingNode = (G4PictureMatching*)reader->readNodeGraphFromFile("G4PictureMatching", thisNode);
    
    if (NULL!=g4PictureMatchingNode) {
        g4PictureMatchingNode->setTag(nodeNumber);
        g4PictureMatchingNode->setAnimationManager(reader->getAnimationManager());
        thisNode->addChild(g4PictureMatchingNode);
    }
    
    g4PictureMatchingNode->littlePullRope->setVisible(false);
    
    reader->release();
    
    return thisNode;
}

bool G4PictureMatching::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCNode::init() )
    {
        return false;
    }
    
    return true;
}

bool G4PictureMatching::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCLOG("pMemberVariableName = %s", pMemberVariableName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "scoreFont", CCLabelBMFont*, this->scoreFont);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "logo", CCSprite*, this->logo);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "littlePullRope", CCSprite*, this->littlePullRope);
    
    return true;
}

SEL_MenuHandler G4PictureMatching::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    //CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClicked", Scene1::onClicked);
    
    return NULL;
}

void G4PictureMatching::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    
}

SEL_CCControlHandler G4PictureMatching::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{

    return NULL;
}

void G4PictureMatching::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
    CC_SAFE_RELEASE_NULL(mAnimationManager);
    
    mAnimationManager = pAnimationManager;
    CC_SAFE_RETAIN(mAnimationManager);
    
//    mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(G4PictureMatching::animationCompleteCallBack));

}

void G4PictureMatching::runAnimation(const char* animationName, float delayTime)
{
    G4PictureMatching* g4PictureMatchingNode = ((G4PictureMatching*)this->getChildByTag(nodeNumber));
    
    if (!g4PictureMatchingNode)
    {
        g4PictureMatchingNode = this;
    }
    
    if (strcmp(animationName, "CountDown") == 0)
    {
        CCLog("CountDown");
        
        float delayTime = 60.0f;
        
        g4PictureMatchingNode->scheduleOnce(schedule_selector(G4PictureMatching::animationCompleteCallBack), delayTime);
    }
    
    g4PictureMatchingNode->mAnimationManager->runAnimationsForSequenceNamedTweenDuration(animationName, delayTime);
}

void G4PictureMatching::setAnimationCompletedCallback(CCObject *target, SEL_CallFunc callbackFunc)
{
    G4PictureMatching* g4PictureMatchingNode = ((G4PictureMatching*)this->getChildByTag(nodeNumber));
    
    g4PictureMatchingNode->target = NULL;
    g4PictureMatchingNode->callbackFunc = NULL;
    
    g4PictureMatchingNode->target = target;
    g4PictureMatchingNode->callbackFunc = callbackFunc;
}

void G4PictureMatching::animationCompleteCallBack()
{
    if (target && callbackFunc) {
        (target->*callbackFunc)();
    }
}

#pragma mark -
#pragma mark 外部函數

void G4PictureMatching::setScoreFont(int score)
{
    G4PictureMatching* g4PictureMatchingNode = ((G4PictureMatching*)this->getChildByTag(nodeNumber));
    
    if (!g4PictureMatchingNode)
    {
        g4PictureMatchingNode = this;
    }
    
    CCString* scoreNumber = CCString::createWithFormat("%d", score);
    
    g4PictureMatchingNode->scoreFont->setString(scoreNumber->getCString());
}

void G4PictureMatching::setInitializeItem(cocos2d::CCSpriteFrame *logoFrame)
{
    G4PictureMatching* g4PictureMatchingNode = ((G4PictureMatching*)this->getChildByTag(nodeNumber));
    
    if (!g4PictureMatchingNode)
    {
        g4PictureMatchingNode = this;
    }
    
    g4PictureMatchingNode->logo->setDisplayFrame(logoFrame);
}

void G4PictureMatching::releaseObject()
{
    G4PictureMatching* g4PictureMatchingNode = ((G4PictureMatching*)this->getChildByTag(nodeNumber));
    
    if (!g4PictureMatchingNode)
    {
        g4PictureMatchingNode = this;
    }
    
    g4PictureMatchingNode->runAnimation("Default Timeline", 0);
    
    g4PictureMatchingNode->unscheduleAllSelectors();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("G4PictureMatching.plist");
    
    CCTextureCache::sharedTextureCache()->removeTextureForKey("G4PictureMatching.png");
    
}







