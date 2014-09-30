//
//  ShareData.cpp
//  RedHat
//
//  Created by Mac-8 on 13/7/2.
//
//

#include "ShareData.h"

using namespace cocos2d;

static ShareData* _instance = NULL;

ShareData* ShareData::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new ShareData();
        
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

void ShareData::init()
{
    s2NowBackground = 0;
    s3NowBackground = 0;
    s4NowBackground = 0;
    
    musicSwitch = true;
    
    CCString* languageInit;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //ios
    const char* plistPath = "InfoPlist.strings";
    const char* fullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile("InfoPlist.strings", plistPath);
    CCDictionary* plistDic = CCDictionary::createWithContentsOfFile(fullPath);
    languageInit = dynamic_cast<CCString*>(plistDic->objectForKey("LanguageInit"));
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //android
    
    ccLanguageType languagType=CCApplication::sharedApplication()->getCurrentLanguage();
    
    CCLOG("languagType = %d", languagType);
    
    switch (languagType)
    {
        case cocos2d::kLanguageChinese:
            languageInit = CCString::createWithFormat("1");
            CCLOG("kLanguageChinese");
            break;
        case cocos2d::kLanguageEnglish:
            languageInit = CCString::createWithFormat("2");
            CCLOG("kLanguageEnglish");
            break;
        case cocos2d::kLanguageTraditional:
            languageInit = CCString::createWithFormat("0");
            CCLOG("kLanguageTraditional");
            break;
        default:
            languageInit = CCString::createWithFormat("2");
            CCLOG("default");
            break;
    }
#endif
    
    languageSetting = (GameLanguageType)languageInit->intValue();
    
    CCLOG("languageSetting = %d", languageSetting);

    
    //語系初始化
//    languageSetting = TRADITIONAL_CHINESE;
}

void ShareData::setS2Background(int setting)
{
    s2NowBackground = setting;
}

int ShareData::getS2Background()
{
    return s2NowBackground;
}

void ShareData::setS3Background(int setting)
{
    s3NowBackground = setting;
}

int ShareData::getS3Background()
{
    return s3NowBackground;
}

void ShareData::setS4Background(int setting)
{
    s4NowBackground = setting;
}

int ShareData::getS4Background()
{
    return s4NowBackground;
}

void ShareData::setLanguageOfScene(int sceneIndex, GameLanguageType languageType)
{
    languageSetting = languageType;
}

GameLanguageType ShareData::getLanguageOfScene(int sceneIndex)
{
    return languageSetting;
}

void ShareData::setMusicSwitch(bool setting)
{
    musicSwitch = setting;
}

bool ShareData::getMusicSwitch()
{
    return musicSwitch;
}

void ShareData::setFirstGameTheBestData(int index, int totalSecond)
{
    const char* key = CCString::createWithFormat(BEST_TIME, index)->getCString();
    int bestTime = CCUserDefault::sharedUserDefault()->getIntegerForKey(key);
    
    if (totalSecond < bestTime || bestTime == 0)
    {
        CCUserDefault::sharedUserDefault()->setIntegerForKey(key, totalSecond);
        CCUserDefault::sharedUserDefault()->flush();
    }
}

int ShareData::getFirstGameTheBestData(int index)
{
    const char* key = CCString::createWithFormat(BEST_TIME, index)->getCString();
    int bestTime = CCUserDefault::sharedUserDefault()->getIntegerForKey(key);
    
    return bestTime;
}

bool ShareData::setNinethGameTheBestData(int totalScore)
{
    bool isBreakRecord = false;
    int bestScore = CCUserDefault::sharedUserDefault()->getIntegerForKey(NINETH_BEST_SCORE);
    
    if (totalScore > 100)
    {
        totalScore = 0;
    }
    
    if (totalScore > bestScore)
    {
        CCUserDefault::sharedUserDefault()->setIntegerForKey(NINETH_BEST_SCORE, totalScore);
        CCUserDefault::sharedUserDefault()->flush();
        isBreakRecord = true;
    }
    return isBreakRecord;
}

int ShareData::getNineGameTheBestData()
{
    int bestScore = CCUserDefault::sharedUserDefault()->getIntegerForKey(NINETH_BEST_SCORE);
    
    return bestScore;
}

bool ShareData::setElevenGameTheBestData(int totalScore)
{
    bool isBreakRecord = false;
    int bestScore = CCUserDefault::sharedUserDefault()->getIntegerForKey(ELEVENTH_BEST_SCORE);
    
    if (totalScore > bestScore)
    {
        CCUserDefault::sharedUserDefault()->setIntegerForKey(ELEVENTH_BEST_SCORE, totalScore);
        CCUserDefault::sharedUserDefault()->flush();
        isBreakRecord = true;
    }
    return isBreakRecord;
}

int ShareData::getElevenGameTheBestData()
{
    int bestScore = CCUserDefault::sharedUserDefault()->getIntegerForKey(ELEVENTH_BEST_SCORE);
    
    return bestScore;
}

bool ShareData::setFourthGameTheBestData(int totalScore)
{
    bool isBreakRecord = false;
    int bestScore = CCUserDefault::sharedUserDefault()->getIntegerForKey(FOURTH_BEST_SCORE);
    
    if (totalScore > bestScore)
    {
        CCUserDefault::sharedUserDefault()->setIntegerForKey(FOURTH_BEST_SCORE, totalScore);
        CCUserDefault::sharedUserDefault()->flush();
        isBreakRecord = true;
    }
    return isBreakRecord;
}

int ShareData::getFourthGameTheBestData()
{
    int bestScore = CCUserDefault::sharedUserDefault()->getIntegerForKey(FOURTH_BEST_SCORE);
    
    return bestScore;
}

bool ShareData::isProUpgradePurchased()
{
    return CCUserDefault::sharedUserDefault()->getBoolForKey("isProUpgradePurchased");
}

void ShareData::setProUpgradePurchased(bool proUpgradePurchased)
{
    CCUserDefault::sharedUserDefault()->setBoolForKey("isProUpgradePurchased", proUpgradePurchased);
}
