//
//  ShareData.h
//  RedHat
//
//  Created by Mac-8 on 13/7/2.
//
//

#ifndef __RedHat__ShareData__
#define __RedHat__ShareData__

#include <iostream>
#include "cocos2d.h"

#define BEST_TIME   "BestTime%d"
#define NINETH_BEST_SCORE   "NinethBestData"
#define ELEVENTH_BEST_SCORE   "EleventhBestData"
#define FOURTH_BEST_SCORE   "FourthBestData"

enum GameLanguageType
{
    TRADITIONAL_CHINESE = 0,
    SIMPLE_CHINESE,
    ENGLISH,
};

class ShareData
{
public:
    // 加入一個member function用來取得獨身
    static ShareData* getInstance();
    // 這個function必須是static function
    // 如此才可以不宣告物件實體取用這個函式
    
    void init();
    
    void setS2Background(int setting);
    int getS2Background();
    
    void setS3Background(int setting);
    int getS3Background();
    
    void setS4Background(int setting);
    int getS4Background();
    
    void setLanguageOfScene(int sceneIndex, GameLanguageType languageType);
    
    GameLanguageType getLanguageOfScene(int sceneIndex);
    
    void setMusicSwitch(bool setting);
    
    bool getMusicSwitch();
    
    void setFirstGameTheBestData(int index, int totalSecond);
    
    int getFirstGameTheBestData(int index);
    
    bool setNinethGameTheBestData(int totalScore);
    
    int getNineGameTheBestData();
    
    bool setElevenGameTheBestData(int totalScore);
    
    int getElevenGameTheBestData();
    
    bool setFourthGameTheBestData(int totalScore);
    
    int getFourthGameTheBestData();
    
    bool isProUpgradePurchased();
    
    void setProUpgradePurchased(bool proUpgradePurchased);
    
private:
    static const int allSceneCount = 12;
    
    int s2NowBackground;
    int s3NowBackground;
    int s4NowBackground;
    
    GameLanguageType languageSetting;
    
    bool musicSwitch;
    
};

#endif /* defined(__RedHat__ShareData__) */
