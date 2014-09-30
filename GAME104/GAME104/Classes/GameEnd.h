#ifndef __ccb_helloworld__GameEnd__
#define __ccb_helloworld__GameEnd__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ShareData.h"
#include "ScoreData.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define VICTORY_MUSIC                           "B0177BGu.mp3"      //勝利音樂
#define BREAK_RECORD_SOUND                      "B0177G00SE02.mp3"  //破紀錄的聲音

class GameEnd:
public CCLayer,
public CCBMemberVariableAssigner,
public CCNodeLoaderListener,
public CCBSelectorResolver
{
    
public:
    GameEnd();
    ~GameEnd();
    
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    static cocos2d::CCNode* node();

    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(GameEnd, create);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    void setAnimationManager(CCBAnimationManager *pAnimationManager);
    
    void runAnimation(const char* animationName, float delayTime);
    
    void setAnimationCompletedCallback(CCObject *target, SEL_CallFunc callbackFunc);
    
    void setAllEventCallBack(CCObject *targetListener, SEL_CallFunc playAgainCallBack, SEL_CallFunc giveUpCallBack);
    
    int starting(GameLanguageType language, int scoreNumber, int theBestScoreNumber, bool isBreakRecord);//, ScoreData* scoreData);
    
    void releaseObject();

private:
    CCBAnimationManager* mAnimationManager;
    
    void changeImage(GameLanguageType language);
    
    CCSprite* score;
    CCSprite* theBestScore;
    CCMenuItemImage* againButton;
    CCMenuItemImage* giveUpButton;
    
    CCSprite* partyPopper;
    
    CCSpriteFrameCache* imageCache;
    
    CCLabelBMFont* scoreText;
    CCLabelBMFont* theBestScoreText;
    
    SEL_CallFunc playAgainCallBack;
    SEL_CallFunc giveUpCallBack;
    CCObject *target;
    
    void onAgainClicked();
    void onGiveUpClicked();
    
    void animationCompleteCallBack();
    
    SEL_CallFunc callbackFunc;
    
    static const int nodeNumber = 1683;

};

class GameEndLoader:public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GameEndLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GameEnd);
};

#endif