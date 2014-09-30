#ifndef __ShakeForFood2__GameScene4__
#define __ShakeForFood2__GameScene4__

#include "cocos2d.h"
#import "GameBox.h"

#include "SimpleAudioEngine.h"
#include "G4PictureMatching.h"
#include "RemoveMatchingData.h"
#include "ShareData.h"

#include "GameEnd.h"
#include "GameOperation.h"
#include "G4RedHat.h"

#include "ShareMethod.h"

#include "StartScene.h"

using namespace cocos2d;

#define G4_INTRODUCE                               "B0177G04.mp3"      //介紹遊戲
#define G4_INTRODUCE_EN                            "EB0129G04.mp3"     //介紹遊戲(EN)

#define G4_BACKGROUND_MUSIC                        "B0177BGv.mp3"      //背景音樂

#define G4_COUNT_DOWN_SOUND                     "B0177G07SE01.mp3"  //倒數聲
#define G4_MATCHING_SOUND                       "B0177G01SE05.mp3"  //連線聲
#define G4_RESETING_SOUND                       "B0177G01SE08.mp3"  //重置聲

enum ScoreLevel
{
    FIRST_SCORE_LEVEL = 10,
    SECONE_SCORE_LEVEL = 20,
    THIRD_SCORE_LEVEL = 50,
};

class GameScene4 :public CCLayer
{
private:
	GameBox *box;
	GameTile *selectedTile;
	GameTile *firstOne;
    
    G4PictureMatching* g4PictureMatchingNode;
    
    GameEnd* gameEndNode;
    
    GameOperation* gameOperationNode;
    
    void matchedCallBack(CCSprite *pSender, RemoveMatchingData* removeObjects);
    
    bool isFirst;
    
    CCSpriteFrameCache* imageCache;
    
    void showScore(int score);
    
    void showDisappear(CCSprite* target);
    
    int convertToScore(int count);
    
    void deleteScoreObject(cocos2d::CCNode *pSender);
    
    void ObjectsShowDisappear(CCArray* removeObjects);
    
    void countScore(int score);
    
    int totalScore;
    
    void countDownCallBack();
    
    G4PictureMatchingStatus g4PictureMatchingStatus;
    
    void gameOpenIsEnd();
    
    void onOperated();
    
    void onReadyGoOver();
    
    void playAgain();
    
    void gameEnd();
    
    void goBackStoryCallBack();
    
    void gameStarting();
    
    bool isOpening;
    
    void playOperation();
    
    void oneShineTrun(CCSprite* asprite, bool isRepeatWithJudge);
    
    void playOperationAnother();
    
    void playSoundEffect(const char *soundName);
    
    void playBackgroundMusic();
    
    int music;
    
    void playCountDownAlert();
    
    void playReadyGo();
    
    G4RedHat* g4RedHatNode;
    
    CCMenu* allMenu;
    
    void whenLeaving();
    
    bool isShowingScore;
    
    void showHint();
    
    bool isActting;
    
    void allActionDoneCallBack();
    
public:
    ~GameScene4();
    GameScene4();
    
	virtual bool init();
	static cocos2d::CCScene* scene();
    void changeWithTileABandSel(GameTile* a,GameTile* b,SEL_CallFuncND sel);
    void checkSenderandData(GameTile* sender,GameTile* data);
    void afterCheckSenderandData(GameTile* sender,GameTile* data);
    void onEnterTransitionDidFinish();
    void afterOneShineTrun(CCSprite* sprite);
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    CREATE_FUNC(GameScene4);
    
    CCLayer* boxLayer;
};

#endif