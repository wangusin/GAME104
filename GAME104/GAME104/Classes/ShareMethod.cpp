//
//  ShareMethod.cpp
//  RedHat
//
//  Created by Mac-8 on 13/7/2.
//
//

#include "ShareMethod.h"

using namespace cocos2d;

static ShareMethod* _instance = NULL;

ShareMethod* ShareMethod::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new ShareMethod();
        
        if (_instance)
        {
            _instance->init();
        }
        else
        {
            CC_SAFE_DELETE(_instance);
            
            return NULL;
        }
    }
    return _instance;
};

void ShareMethod::init()
{
    centralPoint = CCPoint(752, 448);
}

CCPoint ShareMethod::getOffsetOfCenter(cocos2d::CCPoint position)
{
    CCPoint offset = ccpSub(position, centralPoint);
    
    return offset;
}

void ShareMethod::createMenuWithNoPictrue(cocos2d::CCMenu*& menu, cocos2d::CCPoint position, int level, cocos2d::CCNode *carrier, CCRect checkZoneSize, SEL_MenuHandler selector, CCNode* target)
{

    createMenuWithNoPictrueWithTag(menu, position, level, carrier, checkZoneSize, selector, target, 0);
    
}

void ShareMethod::createMenuWithNoPictrueWithTag(cocos2d::CCMenu *&menu, cocos2d::CCPoint position, int level, cocos2d::CCNode *carrier, cocos2d::CCRect checkZoneSize, SEL_MenuHandler selector, cocos2d::CCNode *target, int tag)
{
    
    createMenuWithNoPictrueWithTagAndSetAlpha(menu, position, level, carrier, checkZoneSize, selector, target, tag, 0);
}

void ShareMethod::createMenuWithNoPictrueWithTagAndSetAlpha(cocos2d::CCMenu *&menu, cocos2d::CCPoint position, int level, cocos2d::CCNode *carrier, cocos2d::CCRect checkZoneSize, SEL_MenuHandler selector, cocos2d::CCNode *target, int tag, int alpha)
{
    CCSprite *checkZoneSpr = CCSprite::create();
    checkZoneSpr->setTextureRect(checkZoneSize);
    checkZoneSpr->setOpacity(alpha);
    CCMenuItemSprite *checkZoneItem = CCMenuItemSprite::create(checkZoneSpr, NULL);
    checkZoneItem->setAnchorPoint(ccp(0.5, 0.5));
    menu = CCMenu::createWithItem(checkZoneItem);
    menu->setPosition(position);
    carrier->addChild(menu,level);
    checkZoneItem->setTarget(target, selector);
    checkZoneItem->setTag(tag);
}

void ShareMethod::actionSettingWithBeginNumber(CCActionInterval*& targetAction, const char* name, int count, int repeatCount, float delayPerUnit, int beginNumber, CCSpriteFrameCache* imageCache)
{
    CCAnimation* targetAnimation = CCAnimation::create();
    for (int i = beginNumber ; i < count + beginNumber; i++) {
        const char* tempString = CCString::createWithFormat(name, i)->getCString();
        
        if (!imageCache->spriteFrameByName(tempString))
        {
            CCLog("missing tempString = %s", tempString);
        }
        
        targetAnimation->addSpriteFrame(imageCache->spriteFrameByName(tempString));
    }
    
    targetAnimation->setDelayPerUnit(delayPerUnit);
    
    targetAction = (CCRepeat::create(CCAnimate::create(targetAnimation), repeatCount));
    
}

void ShareMethod::actionSettingWithBeginNumberDecrement(CCActionInterval*& targetAction, const char* name, int count, int repeatCount, float delayPerUnit, int beginNumber, CCSpriteFrameCache* imageCache)
{
    CCAnimation* targetAnimation = CCAnimation::create();
    for (int i = beginNumber ; i > beginNumber - count; i--) {
        const char* tempString = CCString::createWithFormat(name, i)->getCString();
        
        if (!imageCache->spriteFrameByName(tempString))
        {
            CCLog("missing tempString = %s", tempString);
        }
        
        targetAnimation->addSpriteFrame(imageCache->spriteFrameByName(tempString));
    }
    
    targetAnimation->setDelayPerUnit(delayPerUnit);
    
    targetAction = (CCRepeat::create(CCAnimate::create(targetAnimation), repeatCount));
    
}

void ShareMethod::createMenuWithPicture(cocos2d::CCMenu *&menu, cocos2d::CCPoint position, int level, cocos2d::CCNode *carrier, const char* imageName, CCSpriteFrameCache* imageCache, SEL_MenuHandler selector, cocos2d::CCNode *target, int tag)
{
    CCSprite *checkZoneSpr = CCSprite::createWithSpriteFrameName(imageName);
    CCMenuItemSprite *checkZoneItem = CCMenuItemSprite::create(checkZoneSpr, NULL);
    checkZoneItem->setAnchorPoint(ccp(0.5, 0.5));
    menu = CCMenu::createWithItem(checkZoneItem);
    menu->setPosition(position);
    carrier->addChild(menu,level);
    checkZoneItem->setTarget(target, selector);
    checkZoneItem->setTag(tag);
    menu->setUserData(checkZoneSpr);
}

void ShareMethod::createMenuWithPictureAddSelectImage(cocos2d::CCMenu *&menu, cocos2d::CCPoint position, int level, cocos2d::CCNode *carrier, const char* normalImageName, const char* selectImageName, CCSpriteFrameCache* imageCache, SEL_MenuHandler selector, cocos2d::CCNode *target, int tag)
{
    CCSprite *checkZoneSpr = CCSprite::createWithSpriteFrameName(normalImageName);
    CCSprite *selectSpr = CCSprite::createWithSpriteFrameName(selectImageName);
    CCMenuItemSprite *checkZoneItem = CCMenuItemSprite::create(checkZoneSpr, selectSpr);
    checkZoneItem->setAnchorPoint(ccp(0.5, 0.5));
    menu = CCMenu::createWithItem(checkZoneItem);
    menu->setPosition(position);
    carrier->addChild(menu,level);
    checkZoneItem->setTarget(target, selector);
    checkZoneItem->setTag(tag);
}

void ShareMethod::createMenuWithSprite(cocos2d::CCMenu *&menu, cocos2d::CCPoint position, int level, cocos2d::CCNode *carrier, CCSprite* button, CCSprite* selectedButton, SEL_MenuHandler selector, cocos2d::CCNode *target, int tag)
{
    CCMenuItemSprite *checkZoneItem = CCMenuItemSprite::create(button, selectedButton);
//    checkZoneItem->setAnchorPoint(ccp(0, 0));
    menu = CCMenu::createWithItem(checkZoneItem);
    menu->setPosition(position);
    carrier->addChild(menu,level);
    checkZoneItem->setTarget(target, selector);
    checkZoneItem->setTag(tag);
    checkZoneItem->setUserData(button);
}

void ShareMethod::createMenuWithSpriteAndHasSelected(cocos2d::CCMenu *&menu, cocos2d::CCPoint position, int level, cocos2d::CCNode *carrier, const char* normalImageName, SEL_MenuHandler selector, cocos2d::CCNode *target, int tag)
{
    CCSprite* button = CCSprite::createWithSpriteFrameName(normalImageName);
    
    CCSprite* selectedButton = CCSprite::createWithSpriteFrameName(normalImageName);
    selectedButton->setScale(0.9);
    CCSprite* buttonFather = CCSprite::createWithSpriteFrameName(normalImageName);
    
    buttonFather->setOpacity(0);
    selectedButton->setPosition(ccp(button->getContentSize().width / 2, button->getContentSize().height / 2));
    buttonFather->addChild(selectedButton);
    
    CCMenuItemSprite *checkZoneItem = CCMenuItemSprite::create(button, buttonFather);
    //    checkZoneItem->setAnchorPoint(ccp(0, 0));
    menu = CCMenu::createWithItem(checkZoneItem);
    menu->setPosition(position);
    carrier->addChild(menu,level);
    checkZoneItem->setTarget(target, selector);
    checkZoneItem->setTag(tag);
}

CCMenu* ShareMethod::createSingleTouchMenu(const char *pszSpriteName,CCObject *rec, SEL_MenuHandler selector,int tag, float scale){
    CCSprite *spr = CCSprite::createWithSpriteFrameName(pszSpriteName);
    
    CCSize size = spr -> boundingBox().size;
    
    CCSprite *sprT = CCSprite::createWithSpriteFrameName(pszSpriteName);
    
    sprT -> setScale(scale);
    sprT -> setPosition(ccp(size.width * (1.0 - scale) / 2, size.height * (1.0 - scale) / 2));
    
    return createTouchMenu(spr, sprT, rec, selector, tag);
}
CCMenu* ShareMethod::createTouchMenu(CCSprite *sprite,CCSprite *touchspite,CCObject *rec, SEL_MenuHandler selector,int tag){
    
    CCMenuItemSprite *theItem = CCMenuItemSprite::create(sprite, touchspite, rec, selector);
    CCMenu *theMenu = CCMenu::createWithItem(theItem);
    theItem->setTag(tag);
    return theMenu;
}

void ShareMethod::createMenuWithPictureAndRoate(cocos2d::CCMenu *&menu, cocos2d::CCPoint position, int level, cocos2d::CCNode *carrier, const char* imageName, CCSpriteFrameCache* imageCache, SEL_MenuHandler selector, cocos2d::CCNode *target, int tag, float rotation)
{
    CCSprite *checkZoneSpr = CCSprite::createWithSpriteFrameName(imageName);
    CCMenuItemSprite *checkZoneItem = CCMenuItemSprite::create(checkZoneSpr, NULL);
    checkZoneItem->setAnchorPoint(ccp(0.5, 0.5));
    checkZoneItem->setRotation(rotation);
    menu = CCMenu::createWithItem(checkZoneItem);
    menu->setPosition(position);
    carrier->addChild(menu,level);
    checkZoneItem->setTarget(target, selector);
    checkZoneItem->setTag(tag);
    menu->setUserData(checkZoneSpr);
}

CCNode * ShareMethod::cloneCCNode(CCNode * sender)
{
    CCNode* clone = CCSprite::createWithTexture(((CCSprite*)sender) -> getTexture());
    ((CCSprite*)clone) -> setDisplayFrame(((CCSprite*)sender) -> displayFrame());
    
    CCObject* pObj = NULL;
    CCArray* pChildren = sender->getChildren();
    
    CCARRAY_FOREACH(pChildren, pObj)
    {
        CCNode* pChild = (CCNode*)pObj;
        CCNode* subnode;
        if (dynamic_cast<CCSprite*>(pChild)) {
            CCSprite* srcSprite = (CCSprite*)pChild;
            subnode = CCSprite::createWithTexture(srcSprite -> getTexture());
            ((CCSprite*)subnode) -> setDisplayFrame(srcSprite -> displayFrame());
            
        }else{
            subnode = this -> cloneCCNode(pChild);
        }
        
        subnode -> setRotation(pChild -> getRotation());
        subnode -> setPosition(pChild -> getPosition());
        subnode -> setAnchorPoint(pChild -> getAnchorPoint());
        subnode -> setZOrder(pChild -> getZOrder());
        clone -> addChild(subnode);
    }
    
    return clone;
}

void ShareMethod::getRandomAndNoRepeat(int *randomArray, int xCount, int yCount, int size)
{
    
    int quantity = xCount * yCount;
    int start = 0;
    int total = xCount * yCount;
    if (quantity > total) {
        CCLog("随机数错误");
    }
    int sequence[total];  //存放随机数的数组
    //int output[quantity]; //最终生成的不重复一系列随机数
    
    //将sequence 初始化
    for (int i = 0; i < total; i++) {
        sequence[i] = start + i;
    }
    
    //随机数种子
    cc_timeval psv;
    CCTime::gettimeofdayCocos2d(&psv, NULL);
    unsigned long int seed = psv.tv_sec*1000 + psv.tv_usec/1000;
    srand(seed);
    
//    for (int i = 0; i < quantity; i++) {
//        int num = arc4random() % total;//在指定范围下产生随机数
//        randomArray[i] = sequence[num];//将产生的随机数存储
//        sequence[num] = sequence[total-1];//将最后个下标的值填充到随机产生的下标中
//        total--;//在指定范围 向前移
//    }
    
    for (int i = 0; i < size; i++) {
        int num = arc4random() % total;//在指定范围下产生随机数
        randomArray[i] = sequence[num];//将产生的随机数存储
        sequence[num] = sequence[total-1];//将最后个下标的值填充到随机产生的下标中
        total--;//在指定范围 向前移
    }
}

bool ShareMethod::isContainNumber(int targetNumber, int* array, int size)
{    
    for (int i = 0; i < size; i++)
    {
        if (targetNumber == array[i])
            return true;
    }
    
    return false;
}

bool ShareMethod::ccpIsEqual(cocos2d::CCPoint pos1, cocos2d::CCPoint pos2)
{
    //    CCLOG("pos1(%f, %f)    pos2(%f, %f)", pos1.x, pos1.y, pos2.x, pos2.y);
    
    if (pos1.x == pos2.x && pos1.y == pos2.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool ShareMethod::colorIsEqual(cocos2d::ccColor4B color1, cocos2d::ccColor4B color2)
{
    if (color1.r == color2.r && color1.g == color2.g && color1.b == color2.b && color1.a == color2.a)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ShareMethod::saveScreen()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCRenderTexture* screen = CCRenderTexture::create(size.width, size.height);
    CCScene* temp = CCDirector::sharedDirector()->getRunningScene();
    screen->begin();
    temp->visit();
    screen->end();
    screen->saveToFile("screenshot.png", kCCImageFormatPNG);
    CC_SAFE_DELETE(screen);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //IOS
    ObjCCalls::screenShots();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //Android
    //    texture->saveBuffer(kCCImageFormatPNG,"tempscreen.png",0,0,size.width,size.height);
    
    JniMethodInfo minfo;
    bool isHave = JniHelper::getStaticMethodInfo(minfo,CLASS_NAME,"share", "()V");
    if (isHave)
    {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
#endif

}

int ShareMethod::playLongSound(const char *soundName)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    int soundId = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(soundName, true);
    
    return soundId;
    
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //Android
    JniMethodInfo minfo;
    if(JniHelper::getStaticMethodInfo(minfo,
                                      CLASS_NAME,
                                      "playLongSound",
                                      "(Ljava/lang/String;)V"))
    {
        jstring StringArg1 = minfo.env->NewStringUTF(soundName);
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, StringArg1);
        minfo.env->DeleteLocalRef(StringArg1);
        minfo.env->DeleteLocalRef(minfo.classID);
    }
    
    return ANDROID_LONG_SOUND_ID;
#endif
}

void ShareMethod::stopLongSound(int soundId)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopEffect(soundId);
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if(JniHelper::getStaticMethodInfo(minfo,
                                      CLASS_NAME,
                                      "stopLongSound",
                                      "()V"))
    {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
        minfo.env->DeleteLocalRef(minfo.classID);
    }
#endif
}

void ShareMethod::pauseLongSound(int soundId)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //Android
    JniMethodInfo minfo;
    if(JniHelper::getStaticMethodInfo(minfo,
                                      CLASS_NAME,
                                      "pauseLongSound",
                                      "()V"))
    {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
        minfo.env->DeleteLocalRef(minfo.classID);
    }
    
#endif
}

void ShareMethod::resumeLongSound(int soundId)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //Android
    JniMethodInfo minfo;
    if(JniHelper::getStaticMethodInfo(minfo,
                                      CLASS_NAME,
                                      "resumeLongSound",
                                      "()V"))
    {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
        minfo.env->DeleteLocalRef(minfo.classID);
    }
    
#endif
}

