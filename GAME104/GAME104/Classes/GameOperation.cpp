#include "GameOperation.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

USING_NS_CC;
USING_NS_CC_EXT;


GameOperation::GameOperation():mAnimationManager(NULL)
{
    listener = NULL;
    operationShowHasPlayedCallBack = NULL;
    readyGoHasPlayedCallBack = NULL;
}
GameOperation::~GameOperation()
{
    CCLog("~GameOperation()");
    
    CC_SAFE_RELEASE_NULL(mAnimationManager);
    
    listener = NULL;
    operationShowHasPlayedCallBack = NULL;
    readyGoHasPlayedCallBack = NULL;
}

CCNode* GameOperation::node(int language, int gameIndex)
{
    CCNode* thisNode = CCNode::create();
    
    CCNodeLoaderLibrary* lib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    lib->registerCCNodeLoader("GameOperation", GameOperationLoader::loader());
    CCBReader* reader = new CCBReader(lib);
    GameOperation* gameOperationNode = (GameOperation*)reader->readNodeGraphFromFile("GameOperation", thisNode);
    
    if (NULL!=gameOperationNode) {
        gameOperationNode->setTag(nodeNumber);
        gameOperationNode->setAnimationManager(reader->getAnimationManager());
        thisNode->addChild(gameOperationNode);
    }
    
    reader->release();
    
    //init
    gameOperationNode->operationStatus = GAME_OPERATION_IDLE;
    //end
    
    if (gameIndex == 1)
    {
        gameOperationNode->operationShow = "G1Operation";
        if (language == TRADITIONAL_CHINESE)
        {
            gameOperationNode->operationSound = G1_OPERATION;
        }
        else if (language == SIMPLE_CHINESE)
        {
            gameOperationNode->operationSound = G1_OPERATION;
        }
        else if (language == ENGLISH)
        {
            gameOperationNode->operationSound = G1_OPERATION_EN;
        }
    }
    else if (gameIndex == 2)
    {
        if (language == TRADITIONAL_CHINESE)
        {
            
        }
        else if (language == SIMPLE_CHINESE)
        {
            
        }
        else if (language == ENGLISH)
        {
            
        }
    }
    else if (gameIndex == 4)
    {
        gameOperationNode->operationShow = "G4Operation";
        if (language == TRADITIONAL_CHINESE)
        {
            gameOperationNode->operationSound = G4_OPERATION;
        }
        else if (language == SIMPLE_CHINESE)
        {
            gameOperationNode->operationSound = G4_OPERATION;
        }
        else if (language == ENGLISH)
        {
            gameOperationNode->operationSound = G4_OPERATION_EN;
        }
    }
    else if (gameIndex == 7)
    {
        gameOperationNode->operationShow = "G7Operation";
        if (language == TRADITIONAL_CHINESE)
        {
            gameOperationNode->operationSound = G7_OPERATION;
        }
        else if (language == SIMPLE_CHINESE)
        {
            gameOperationNode->operationSound = G7_OPERATION;
        }
        else if (language == ENGLISH)
        {
            gameOperationNode->operationSound = G7_OPERATION_EN;
        }
    }
    else if (gameIndex == 9)
    {
        gameOperationNode->operationShow = "G9Operation";
        if (language == TRADITIONAL_CHINESE)
        {
            gameOperationNode->operationSound = G9_OPERATION;
        }
        else if (language == SIMPLE_CHINESE)
        {
            gameOperationNode->operationSound = G9_OPERATION;
        }
        else if (language == ENGLISH)
        {
            gameOperationNode->operationSound = G9_OPERATION_EN;
        }
    }
    else if (gameIndex == 11)
    {
        gameOperationNode->operationShow = "G11Operation";
        if (language == TRADITIONAL_CHINESE)
        {
            gameOperationNode->operationSound = G11_OPERATION;
        }
        else if (language == SIMPLE_CHINESE)
        {
            gameOperationNode->operationSound = G11_OPERATION;
        }
        else if (language == ENGLISH)
        {
            gameOperationNode->operationSound = G11_OPERATION_EN;
        }
    }
    
    SimpleAudioEngine::sharedEngine()->preloadEffect(gameOperationNode->operationSound);
    
    SimpleAudioEngine::sharedEngine()->preloadEffect(READY_SOUND);
    SimpleAudioEngine::sharedEngine()->preloadEffect(GO_SOUND);
    
    return thisNode;
}

bool GameOperation::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCNode::init() )
    {
        return false;
    }
    
    return true;
}

bool GameOperation::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "little_pull", CCSprite*, this->little_pull);
    
    return true;
}

SEL_MenuHandler GameOperation::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    //CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClicked", Scene1::onClicked);
    
    return NULL;
}

void GameOperation::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    
}

SEL_CCControlHandler GameOperation::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{

    return NULL;
}

void GameOperation::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
    CC_SAFE_RELEASE_NULL(mAnimationManager);
    
    mAnimationManager = pAnimationManager;
    CC_SAFE_RETAIN(mAnimationManager);
//    setAnimationCompletedCallback();
}

void GameOperation::runAnimation(const char* animationName, float delayTime)
{
    GameOperation* gameOperationNode = ((GameOperation*)this->getChildByTag(nodeNumber));
    
    if (!gameOperationNode)
    {
        gameOperationNode = this;
    }
    
    if (strcmp(animationName, "Ready") == 0)
    {
        float delayTime = (2.0f * 30.0f + 13.0f) / 30.0f;
        
        gameOperationNode->scheduleOnce(schedule_selector(GameOperation::animationCompleteCallBack), delayTime);
    }
    else if (strcmp(animationName, "Go") == 0)
    {
        float delayTime = (1.0f * 30.0f) / 30.0f;
        
        gameOperationNode->scheduleOnce(schedule_selector(GameOperation::animationCompleteCallBack1), delayTime);
    }
    else if (strcmp(animationName, "G7Operation") == 0)
    {
        float delayTime = (8.0f * 30.0f + 15.0f) / 30.0f;
        
        gameOperationNode->scheduleOnce(schedule_selector(GameOperation::animationCompleteCallBack2), delayTime);
    }
    else if (strcmp(animationName, "G11Operation") == 0)
    {
        float delayTime = (11.0f * 30.0f) / 30.0f;
        
        gameOperationNode->scheduleOnce(schedule_selector(GameOperation::animationCompleteCallBack3), delayTime);
    }
    else if (strcmp(animationName, "G4Operation") == 0)
    {
        float delayTime = (12.0f * 30.0f) / 30.0f;
        
        gameOperationNode->scheduleOnce(schedule_selector(GameOperation::animationCompleteCallBack4), delayTime);
    }
    else if (strcmp(animationName, "G1Operation") == 0)
    {
        float delayTime = (11.0f * 30.0f) / 30.0f;
        
        gameOperationNode->scheduleOnce(schedule_selector(GameOperation::animationCompleteCallBack5), delayTime);
    }
    else if (strcmp(animationName, "G9Operation") == 0)
    {
        float delayTime = (11.0f * 30.0f) / 30.0f;
        
        gameOperationNode->scheduleOnce(schedule_selector(GameOperation::animationCompleteCallBack6), delayTime);
    }
    
    gameOperationNode->mAnimationManager->runAnimationsForSequenceNamedTweenDuration(animationName, delayTime);
}

void GameOperation::setAnimationCompletedCallback()
{
    mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(GameOperation::animationCompleteCallBack));
}

void GameOperation::animationCompleteCallBack1()
{
    animationCompleteCallBack();
}

void GameOperation::animationCompleteCallBack2()
{
    animationCompleteCallBack();
}
void GameOperation::animationCompleteCallBack3()
{
    animationCompleteCallBack();
}
void GameOperation::animationCompleteCallBack4()
{
    animationCompleteCallBack();
}
void GameOperation::animationCompleteCallBack5()
{
    animationCompleteCallBack();
}
void GameOperation::animationCompleteCallBack6()
{
    animationCompleteCallBack();
}

#pragma mark -
#pragma mark 事件回傳

void GameOperation::animationCompleteCallBack()
{
    GameOperation* gameOperationNode = ((GameOperation*)this->getChildByTag(nodeNumber));
    
    if (!gameOperationNode)
    {
        gameOperationNode = this;
    }
    
    if (gameOperationNode->operationStatus == OPERTATING)
    {
        if (listener && operationShowHasPlayedCallBack)
        {
            (listener->*operationShowHasPlayedCallBack)();
        }
    }
    else if (gameOperationNode->operationStatus == READY)
    {
        gameOperationNode->runAnimation("Go", 0);
        
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic(GO_SOUND, false);
        
        gameOperationNode->operationStatus = GO;
    }
    else if (gameOperationNode->operationStatus == GO)
    {
        gameOperationNode->operationStatus = GAME_OPERATION_IDLE;
        
        if (listener && readyGoHasPlayedCallBack)
        {
            (listener->*readyGoHasPlayedCallBack)();
        }
    }
}

#pragma mark -
#pragma mark 外部函數

void GameOperation::playOperationShow()
{
    GameOperation* gameOperationNode = ((GameOperation*)this->getChildByTag(nodeNumber));
    
    if (!gameOperationNode)
    {
        gameOperationNode = this;
    }
    
    gameOperationNode->runAnimation(gameOperationNode->operationShow, 0);
    
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(gameOperationNode->operationSound, false);
    
    gameOperationNode->operationStatus = OPERTATING;
}

void GameOperation::setInitializeItem(cocos2d::CCObject *listener, SEL_CallFunc operationShowHasPlayedCallBack, SEL_CallFunc readyGoHasPlayedCallBack)
{
    GameOperation* gameOperationNode = ((GameOperation*)this->getChildByTag(nodeNumber));
    
    gameOperationNode->listener = NULL;
    
    gameOperationNode->listener = listener;
    gameOperationNode->operationShowHasPlayedCallBack = operationShowHasPlayedCallBack;
    gameOperationNode->readyGoHasPlayedCallBack = readyGoHasPlayedCallBack;

}

void GameOperation::playReadyGo()
{
    GameOperation* gameOperationNode = ((GameOperation*)this->getChildByTag(nodeNumber));
    
    if (!gameOperationNode)
    {
        gameOperationNode = this;
    }
    
    gameOperationNode->runAnimation("Ready", 0);
    
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(READY_SOUND, false);
    
    gameOperationNode->operationStatus = READY;
}

void GameOperation::releaseObject()
{
    GameOperation* gameOperationNode = ((GameOperation*)this->getChildByTag(nodeNumber));
    
    if (!gameOperationNode)
    {
        gameOperationNode = this;
    }
    
    gameOperationNode->unscheduleAllSelectors();
    
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
    
    SimpleAudioEngine::sharedEngine()->unloadEffect(gameOperationNode->operationSound);
    
    SimpleAudioEngine::sharedEngine()->unloadEffect(READY_SOUND);
    SimpleAudioEngine::sharedEngine()->unloadEffect(GO_SOUND);
    
//    gameOperationNode->runAnimation("Default Timeline", 0);
    
//    gameOperationNode->release();
    
}

