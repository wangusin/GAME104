#include "GameEnd.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;
USING_NS_CC_EXT;

GameEnd::GameEnd():mAnimationManager(NULL), score(NULL), theBestScore(NULL), againButton(NULL), giveUpButton(NULL), partyPopper(NULL), imageCache(NULL), scoreText(NULL), theBestScoreText(NULL)
{
    target = NULL;
    playAgainCallBack = NULL;
    giveUpCallBack = NULL;
    callbackFunc = NULL;
}
GameEnd::~GameEnd()
{
    CCLog("~GameEnd()");
    
    CC_SAFE_RELEASE_NULL(mAnimationManager);
    
    CC_SAFE_RELEASE_NULL(score);
    CC_SAFE_RELEASE_NULL(theBestScore);
    CC_SAFE_RELEASE_NULL(againButton);
    CC_SAFE_RELEASE_NULL(giveUpButton);
    
    CC_SAFE_RELEASE_NULL(partyPopper);
    
    CC_SAFE_RELEASE_NULL(scoreText);
    CC_SAFE_RELEASE_NULL(theBestScoreText);
    
    target = NULL;
    playAgainCallBack = NULL;
    giveUpCallBack = NULL;
    callbackFunc = NULL;
}

CCNode* GameEnd::node()
{
    CCNode* thisNode = CCNode::create();
    
    CCNodeLoaderLibrary* lib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    lib->registerCCNodeLoader("GameEnd", GameEndLoader::loader());
    CCBReader* reader = new CCBReader(lib);
    GameEnd* gameEndNode = (GameEnd*)reader->readNodeGraphFromFile("GameEnd", thisNode);
    
    if (NULL!=gameEndNode) {
        gameEndNode->setTag(nodeNumber);
        gameEndNode->setAnimationManager(reader->getAnimationManager());
        thisNode->addChild(gameEndNode);
    }
    
    reader->release();
    
    gameEndNode->imageCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    gameEndNode->imageCache->addSpriteFramesWithFile("GameShareObject.plist");
    
    SimpleAudioEngine::sharedEngine()->preloadEffect(VICTORY_MUSIC);
    SimpleAudioEngine::sharedEngine()->preloadEffect(BREAK_RECORD_SOUND);
    
    
    return thisNode;
}

bool GameEnd::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCNode::init() )
    {
        return false;
    }
    
    return true;
}

bool GameEnd::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "score", CCSprite*, this->score);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "theBestScore", CCSprite*, this->theBestScore);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "againButton", CCMenuItemImage*, this->againButton);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "giveUpButton", CCMenuItemImage*, this->giveUpButton);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "partyPopper", CCSprite*, this->partyPopper);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "scoreText", CCLabelBMFont*, this->scoreText);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "theBestScoreText", CCLabelBMFont*, this->theBestScoreText);
    
    return true;
}

SEL_MenuHandler GameEnd::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onAgainClicked", GameEnd::onAgainClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onGiveUpClicked", GameEnd::onGiveUpClicked);
    
    return NULL;
}

void GameEnd::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    
}

SEL_CCControlHandler GameEnd::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{

    return NULL;
}

void GameEnd::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
    CC_SAFE_RELEASE_NULL(mAnimationManager);
    
    mAnimationManager = pAnimationManager;
    CC_SAFE_RETAIN(mAnimationManager);
    
    mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(GameEnd::animationCompleteCallBack));

}

void GameEnd::runAnimation(const char* animationName, float delayTime)
{
    GameEnd* gameEndNode = ((GameEnd*)this->getChildByTag(nodeNumber));
    
    if (!gameEndNode)
    {
        gameEndNode = this;
    }
    
    gameEndNode->mAnimationManager->runAnimationsForSequenceNamedTweenDuration(animationName, delayTime);
}

void GameEnd::setAnimationCompletedCallback(CCObject *target, SEL_CallFunc callbackFunc)
{
    GameEnd* gameEndNode = ((GameEnd*)this->getChildByTag(nodeNumber));
    
    gameEndNode->target = NULL;
    gameEndNode->callbackFunc = NULL;
    
    gameEndNode->target = target;
    gameEndNode->callbackFunc = callbackFunc;
}

void GameEnd::animationCompleteCallBack()
{
    if (target && callbackFunc) {
        (target->*callbackFunc)();
    }
}

int GameEnd::starting(GameLanguageType language, int scoreNumber, int theBestScoreNumber, bool isBreakRecord)//ScoreData *scoreData)
{
    GameEnd* gameEndNode = ((GameEnd*)this->getChildByTag(nodeNumber));
    
    if (!gameEndNode)
    {
        gameEndNode = this;
    }
    
//    CCLOG("scoreData : t = %d, b = %d", scoreData->score, scoreData->theBestScore);
    
    int music = SimpleAudioEngine::sharedEngine()->playEffect(VICTORY_MUSIC, true);
    
    changeImage(language);
    
    gameEndNode->scoreText->setString(CCString::createWithFormat("%03d", scoreNumber)->getCString());
    
    gameEndNode->theBestScoreText->setString(CCString::createWithFormat("%03d", theBestScoreNumber)->getCString());

    if (isBreakRecord)
        CCLOG("break record");
    else
        CCLOG("keep record");
    
    if (isBreakRecord)
    {
        SimpleAudioEngine::sharedEngine()->playEffect(BREAK_RECORD_SOUND, false);
        gameEndNode->partyPopper->setVisible(true);
        gameEndNode->runAnimation("Popping", 0);
    }
    
    return music;
}

void GameEnd::changeImage(GameLanguageType language)
{
    CCLOG("changeImage language = %d", language);
    
    GameEnd* gameEndNode = ((GameEnd*)this->getChildByTag(nodeNumber));
    
    if (!gameEndNode)
    {
        gameEndNode = this;
    }
    
    int languageIndex = language;

    gameEndNode->score->setDisplayFrame(gameEndNode->imageCache->spriteFrameByName(CCString::createWithFormat("g03_Feedback000%d.png", languageIndex + 1)->getCString()));
    
    gameEndNode->theBestScore->setDisplayFrame(gameEndNode->imageCache->spriteFrameByName(CCString::createWithFormat("g03_Feedback000%d.png", languageIndex + 4)->getCString()));
    
    gameEndNode->againButton->setNormalSpriteFrame(gameEndNode->imageCache->spriteFrameByName(CCString::createWithFormat("g02_btn2000%d.png", languageIndex + 1)->getCString()));
    
    gameEndNode->giveUpButton->setNormalSpriteFrame(gameEndNode->imageCache->spriteFrameByName(CCString::createWithFormat("g02_btn2000%d.png", languageIndex + 4)->getCString()));

}

void GameEnd::setAllEventCallBack(cocos2d::CCObject *targetListener, SEL_CallFunc playAgainCallBack, SEL_CallFunc giveUpCallBack)
{
    GameEnd* gameEndNode = ((GameEnd*)this->getChildByTag(nodeNumber));
    
    gameEndNode->target = targetListener;
    gameEndNode->playAgainCallBack = playAgainCallBack;
    gameEndNode->giveUpCallBack = giveUpCallBack;
}

void GameEnd::onAgainClicked()
{
    CCLOG("onAgainClicked");
    
    GameEnd* gameEndNode = ((GameEnd*)this->getChildByTag(nodeNumber));
    
    if (!gameEndNode)
    {
        gameEndNode = this;
    }
    
    if (gameEndNode->target && gameEndNode->playAgainCallBack) {
        (gameEndNode->target->*gameEndNode->playAgainCallBack)();
    }
}

void GameEnd::onGiveUpClicked()
{
    CCLOG("onGiveUpClicked");
    
    GameEnd* gameEndNode = ((GameEnd*)this->getChildByTag(nodeNumber));
    
    if (!gameEndNode)
    {
        gameEndNode = this;
    }
    
    if (gameEndNode->target && gameEndNode->giveUpCallBack) {
        (gameEndNode->target->*gameEndNode->giveUpCallBack)();
    }
}

void GameEnd::releaseObject()
{
    GameEnd* gameEndNode = ((GameEnd*)this->getChildByTag(nodeNumber));
    
    if (!gameEndNode)
    {
        gameEndNode = this;
    }
    
    gameEndNode->runAnimation("Default Timeline", 0);
    
    gameEndNode->release();
}









