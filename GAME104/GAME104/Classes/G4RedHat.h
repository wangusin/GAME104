#ifndef __ccb_helloworld__G4RedHat__
#define __ccb_helloworld__G4RedHat__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;


class G4RedHat:
public CCLayer,
public CCBMemberVariableAssigner,
public CCNodeLoaderListener,
public CCBSelectorResolver
{
    
public:
    G4RedHat();
    ~G4RedHat();
    
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    static cocos2d::CCNode* node();

    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(G4RedHat, create);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    void setAnimationManager(CCBAnimationManager *pAnimationManager);
    
    void runAnimation(const char* animationName, float delayTime);
    
    void setAnimationCompletedCallback(CCObject *target, SEL_CallFunc callbackFunc);
    
    void releaseObject();

private:
    CCBAnimationManager* mAnimationManager;
    
    void animationCompleteCallBack();
    
    CCObject *target;
    SEL_CallFunc callbackFunc;
    
    static const int nodeNumber = 1683;
};

class G4RedHatLoader:public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(G4RedHatLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(G4RedHat);
};

#endif