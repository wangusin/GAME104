#include "G4RedHat.h"
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

G4RedHat::G4RedHat():mAnimationManager(NULL)
{
    target = NULL;
    callbackFunc = NULL;
}
G4RedHat::~G4RedHat()
{
    CCLog("~G4RedHat()");
    
    CC_SAFE_RELEASE_NULL(mAnimationManager);
    
    target = NULL;
    callbackFunc = NULL;
}

CCNode* G4RedHat::node()
{
    CCNode* thisNode = CCNode::create();
    
    CCNodeLoaderLibrary* lib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    lib->registerCCNodeLoader("G4RedHat", G4RedHatLoader::loader());
    CCBReader* reader = new CCBReader(lib);
    G4RedHat* g4RedHatNode = (G4RedHat*)reader->readNodeGraphFromFile("G4RedHat", thisNode);
    
    if (NULL!=g4RedHatNode) {
        g4RedHatNode->setTag(nodeNumber);
        g4RedHatNode->setAnimationManager(reader->getAnimationManager());
        thisNode->addChild(g4RedHatNode);
    }
    
    reader->release();
    
    return thisNode;
}

bool G4RedHat::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCNode::init() )
    {
        return false;
    }
    
    return true;
}

bool G4RedHat::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "little_pull", CCSprite*, this->little_pull);
    
    return true;
}

SEL_MenuHandler G4RedHat::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    //CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClicked", Scene1::onClicked);
    
    return NULL;
}

void G4RedHat::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    
}

SEL_CCControlHandler G4RedHat::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{

    return NULL;
}

void G4RedHat::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
    CC_SAFE_RELEASE_NULL(mAnimationManager);
    
    mAnimationManager = pAnimationManager;
    CC_SAFE_RETAIN(mAnimationManager);
    
//    mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(G4RedHat::animationCompleteCallBack));

}

void G4RedHat::runAnimation(const char* animationName, float delayTime)
{
    G4RedHat* g4RedHatNode = ((G4RedHat*)this->getChildByTag(nodeNumber));
    
    if (!g4RedHatNode)
    {
        g4RedHatNode = this;
    }
    
    g4RedHatNode->mAnimationManager->runAnimationsForSequenceNamedTweenDuration(animationName, delayTime);
}

void G4RedHat::setAnimationCompletedCallback(CCObject *target, SEL_CallFunc callbackFunc)
{
    G4RedHat* g4RedHatNode = ((G4RedHat*)this->getChildByTag(nodeNumber));
    
    g4RedHatNode->target = NULL;
    g4RedHatNode->callbackFunc = NULL;
    
    g4RedHatNode->target = target;
    g4RedHatNode->callbackFunc = callbackFunc;
}

void G4RedHat::animationCompleteCallBack()
{
    if (target && callbackFunc) {
        (target->*callbackFunc)();
    }
}

#pragma mark -
#pragma mark 外部函數

void G4RedHat::releaseObject()
{
    G4RedHat* g4RedHatNode = ((G4RedHat*)this->getChildByTag(nodeNumber));
    
    if (!g4RedHatNode)
    {
        g4RedHatNode = this;
    }
    
    g4RedHatNode->unscheduleAllSelectors();
    
    g4RedHatNode->runAnimation("Default Timeline", 0);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("G4PictureMatching.plist");
    
    CCTextureCache::sharedTextureCache()->removeTextureForKey("G4PictureMatching.png");
    
//    g4RedHatNode->release();
}










