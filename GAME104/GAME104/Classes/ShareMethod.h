//
//  ShareMethod.h
//  RedHat
//
//  Created by Mac-8 on 13/7/2.
//
//

#ifndef __RedHat__ShareMethod__
#define __RedHat__ShareMethod__

#include <iostream>
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//IOS
#include "ObjCCalls.h"

#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//Android
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

#endif

#include "constants.h"

#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

class ShareMethod
{
public:
    // 加入一個member function用來取得獨身
    static ShareMethod* getInstance();
    // 這個function必須是static function
    // 如此才可以不宣告物件實體取用這個函式
    
    void init();
    
    //以1504*896為大小，都以中心點為主的
    CCPoint getOffsetOfCenter(CCPoint position);
    
    void createMenuWithNoPictrue(CCMenu*& menu, CCPoint position, int level, CCNode* carrier, CCRect checkZoneSize, SEL_MenuHandler selector, CCNode* target);
    
    void createMenuWithNoPictrueWithTag(CCMenu*& menu, CCPoint position, int level, CCNode* carrier, CCRect checkZoneSize, SEL_MenuHandler selector, CCNode* target, int tag);
    
    void actionSettingWithBeginNumber(CCActionInterval*& targetAction, const char* name, int count, int repeatCount, float delayPerUnit, int beginNumber, CCSpriteFrameCache* imageCache);
    
    void getRandomAndNoRepeat(int *randomArray, int xCount, int yCount, int size);
    
    bool isContainNumber(int targetNumber, int* array, int size);
    
    void createMenuWithPicture(CCMenu*& menu, CCPoint position, int level, CCNode* carrier, const char* imageName, CCSpriteFrameCache* imageCache, SEL_MenuHandler selector, CCNode* target, int tag);
    
    void actionSettingWithBeginNumberDecrement(CCActionInterval*& targetAction, const char* name, int count, int repeatCount, float delayPerUnit, int beginNumber, CCSpriteFrameCache* imageCache);
    
    void createMenuWithPictureAddSelectImage(cocos2d::CCMenu *&menu, cocos2d::CCPoint position, int level, cocos2d::CCNode *carrier, const char* normalImageName, const char* selectImageName, CCSpriteFrameCache* imageCache, SEL_MenuHandler selector, cocos2d::CCNode *target, int tag);
    
    void createMenuWithSprite(cocos2d::CCMenu *&menu, cocos2d::CCPoint position, int level, cocos2d::CCNode *carrier, CCSprite* button, CCSprite* selectedButton, SEL_MenuHandler selector, cocos2d::CCNode *target, int tag);
    
    bool ccpIsEqual(cocos2d::CCPoint pos1, cocos2d::CCPoint pos2);
    
    void createMenuWithSpriteAndHasSelected(cocos2d::CCMenu *&menu, cocos2d::CCPoint position, int level, cocos2d::CCNode *carrier, const char* normalImageName, SEL_MenuHandler selector, cocos2d::CCNode *target, int tag);
    
    void createMenuWithPictureAndRoate(cocos2d::CCMenu *&menu, cocos2d::CCPoint position, int level, cocos2d::CCNode *carrier, const char* imageName, CCSpriteFrameCache* imageCache, SEL_MenuHandler selector, cocos2d::CCNode *target, int tag, float rotation);
    
    void createMenuWithNoPictrueWithTagAndSetAlpha(cocos2d::CCMenu *&menu, cocos2d::CCPoint position, int level, cocos2d::CCNode *carrier, cocos2d::CCRect checkZoneSize, SEL_MenuHandler selector, cocos2d::CCNode *target, int tag, int alpha);
    
    CCNode* cloneCCNode(CCNode * sender);
    
    bool colorIsEqual(cocos2d::ccColor4B color1, cocos2d::ccColor4B color2);
    
    void saveScreen();
    
    CCMenu* createSingleTouchMenu(const char *pszSpriteName,CCObject *rec, SEL_MenuHandler selector,int tag, float scale);
    
    CCMenu* createTouchMenu(CCSprite *sprite,CCSprite *touchspite,CCObject *rec, SEL_MenuHandler selector,int tag);
    
    int playLongSound(const char *soundName);
    
    void stopLongSound(int soundId);
    
    void pauseLongSound(int soundId);
    
    void resumeLongSound(int soundId);
    
private:
    
    CCPoint centralPoint;
    
};

#endif /* defined(__RedHat__ShareMethod__) */
