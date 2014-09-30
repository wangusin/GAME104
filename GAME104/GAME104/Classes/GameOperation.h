#ifndef __ccb_helloworld__GameOperation__
#define __ccb_helloworld__GameOperation__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ShareData.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define G7_OPERATION                               "B0177G0702.mp3"    //操作說明
#define G7_OPERATION_EN                            "EB0129G0702.mp3"    //操作說明(EN)

#define G11_OPERATION                               "B0177G1102.mp3"    //操作說明
#define G11_OPERATION_EN                            "EB0129G1102.mp3"    //操作說明(EN)

#define G4_OPERATION                               "B0177G0402.mp3"    //操作說明
#define G4_OPERATION_EN                            "EB0129G0402.mp3"    //操作說明(EN)

#define G1_OPERATION                               "B0177G0102.mp3"    //操作說明
#define G1_OPERATION_EN                            "EB0129G0102.mp3"    //操作說明(EN)

#define G9_OPERATION                               "B0177G0902.mp3"    //操作說明
#define G9_OPERATION_EN                            "EB0129G0902.mp3"    //操作說明(EN)

#define READY_SOUND                             "B0177G00SE01a-ready.mp3"  //準備的聲音
#define GO_SOUND                                "B0177G00SE01b-go.mp3"  //走的聲音

enum GameOperationStatus
{
    GAME_OPERATION_IDLE = 0,
    OPERTATING,
    READY,
    GO,
};

class GameOperation:
public CCLayer,
public CCBMemberVariableAssigner,
public CCNodeLoaderListener,
public CCBSelectorResolver
{
public:
    GameOperation();
    ~GameOperation();
    
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    static cocos2d::CCNode* node(int language, int gameIndex);

    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(GameOperation, create);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    void setAnimationManager(CCBAnimationManager *pAnimationManager);
    
    void runAnimation(const char* animationName, float delayTime);
    
    void setInitializeItem(CCObject *listener, SEL_CallFunc operationShowHasPlayedCallBack, SEL_CallFunc readyGoHasPlayedCallBack);
    
    void playOperationShow();
    
    void playReadyGo();
    
    void releaseObject();

private:
    CCBAnimationManager* mAnimationManager;
    
    const char* operationSound;
    
    void animationCompleteCallBack();
    
    GameOperationStatus operationStatus;
    
    const char* operationShow;
    
    CCObject *listener;
    SEL_CallFunc operationShowHasPlayedCallBack;
    SEL_CallFunc readyGoHasPlayedCallBack;
    
    void setAnimationCompletedCallback();
    
    static const int nodeNumber = 1683;
    
    void animationCompleteCallBack1();
    void animationCompleteCallBack2();
    void animationCompleteCallBack3();
    void animationCompleteCallBack4();
    void animationCompleteCallBack5();
    void animationCompleteCallBack6();
};

class GameOperationLoader:public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GameOperationLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GameOperation);
};

#endif