#include "GameScene4.h"

using namespace cocos2d;
using namespace CocosDenshion;

using namespace cocos2d;

#define joyStickPoint ccp(40,30)
#define joyStickRadius 30

GameScene4::GameScene4():imageCache(NULL), g4PictureMatchingNode(NULL), gameEndNode(NULL), gameOperationNode(NULL), g4RedHatNode(NULL), allMenu(NULL), boxLayer(NULL), selectedTile(NULL), firstOne(NULL)
{
    
}

GameScene4::~GameScene4()
{
    CCLog("~GameScene4");
    
    CC_SAFE_RELEASE_NULL(box);

}

CCScene* GameScene4::scene()
{
    CCScene * scene = NULL;
    do
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);
        
        // 'layer' is an autorelease object
        GameScene4 *layer = GameScene4::create();
        CC_BREAK_IF(! layer);
        
        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene4::init()
{
    //init
    isOpening = true;
    music = 0;
    isShowingScore = false;
    isActting = false;
    isFirst = true;
    totalScore = 0;
    g4PictureMatchingStatus = G4_IDLE;
    //end
    
    selectedTile = GameTile::create(-10, -10);
    firstOne = GameTile::create(-10, -10);
    
    selectedTile->retain();
    firstOne->retain();
    
    imageCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    imageCache->addSpriteFramesWithFile("GameShareObject.plist");
    imageCache->addSpriteFramesWithFile("G4PictureMatching.plist");
    imageCache->addSpriteFramesWithFile("GameScore.plist");

    SimpleAudioEngine::sharedEngine()->preloadEffect(G4_INTRODUCE);
    SimpleAudioEngine::sharedEngine()->preloadEffect(G4_INTRODUCE_EN);
    
    SimpleAudioEngine::sharedEngine()->preloadEffect(G4_BACKGROUND_MUSIC);
    SimpleAudioEngine::sharedEngine()->preloadEffect(G4_COUNT_DOWN_SOUND);
    SimpleAudioEngine::sharedEngine()->preloadEffect(G4_MATCHING_SOUND);
    SimpleAudioEngine::sharedEngine()->preloadEffect(G4_RESETING_SOUND);

    
    CCUserDefault *dataRecord = CCUserDefault::sharedUserDefault();
    int languageType = dataRecord->getIntegerForKey("Record_Language");
    
    const char* introduceOS = G4_INTRODUCE;
    CCSpriteFrame* logoFrame;
    
    if (languageType == TRADITIONAL_CHINESE)
    {
        logoFrame = imageCache->spriteFrameByName("g03_top0001.png");
        
    }
    else if (languageType == SIMPLE_CHINESE)
    {
        logoFrame = imageCache->spriteFrameByName("g03_top0002.png");
        
    }
    else if (languageType == ENGLISH)
    {
        introduceOS = G4_INTRODUCE_EN;
        logoFrame = imageCache->spriteFrameByName("g03_top0003.png");
        
    }
    
    boxLayer = CCLayer::create();
    
    this->addChild(boxLayer);
    
    box = new GameBox(CCSize(kBoxWidth, kBoxHeight), 6);
    box->setEventCallBack(this, callfuncND_selector(GameScene4::matchedCallBack), callfunc_selector(GameScene4::allActionDoneCallBack));
    box->layer = boxLayer;
    box->setLock(true);
    
    //關卡的CCB
    g4PictureMatchingNode = (G4PictureMatching*)G4PictureMatching::node();
    g4PictureMatchingNode->setAnchorPoint(ccp(0, 0));
    this->addChild(g4PictureMatchingNode, -5);
    
    g4PictureMatchingNode->setAnimationCompletedCallback(this, callfunc_selector(GameScene4::countDownCallBack));
    
    g4PictureMatchingNode->setInitializeItem(logoFrame);
    
    //小紅帽
    g4RedHatNode = (G4RedHat*)G4RedHat::node();
    g4RedHatNode->setAnchorPoint(ccp(0, 0));
    this->addChild(g4RedHatNode, 1);
    
    //開頭
//    gameOpenNode = (GameOpen*)GameOpen::node(introduceOS);
//    gameOpenNode->setAnchorPoint(ccp(0, 0));
//    
//    gameOpenNode->setInitilize(this, callfunc_selector(GameScene4::gameOpenIsEnd), logoFrame);
//    
//    this->addChild(gameOpenNode, 50);
    
    //操作介紹
    gameOperationNode = (GameOperation*)GameOperation::node(languageType, 4);
    gameOperationNode->setAnchorPoint(ccp(0, 0));
    this->addChild(gameOperationNode, 10);
    
    gameOperationNode->setInitializeItem(this, callfunc_selector(GameScene4::onOperated), callfunc_selector(GameScene4::onReadyGoOver));
    
    //遊戲結束畫面
    gameEndNode = (GameEnd*)GameEnd::node();
    gameEndNode->setAnchorPoint(ccp(0, 0));
    gameEndNode->setVisible(false);
    
    gameEndNode->setAllEventCallBack(this, callfunc_selector(GameScene4::playAgain), callfunc_selector(GameScene4::goBackStoryCallBack));
    
    this->addChild(gameEndNode, 30);
    
    //遊戲按鈕
//    CCSprite* gameButton = CCSprite::create();
//    CCRect gameZoneSize = CCRectMake(0, 0, 65, 155);
//    gameButton->setTextureRect(gameZoneSize);
//    gameButton->setOpacity(0);
//    
//    CCMenuItemSprite* spriteItemGame = CCMenuItemSprite::create(gameButton, gameButton, this, menu_selector(GameScene4::goBackStoryCallBack));
//    spriteItemGame->setPosition(ccp(0, 611));
//    spriteItemGame->setAnchorPoint(ccp(0.0f, 0));
    
    CCSprite* gameButton = CCSprite::create("exit_btn.png");
    
    CCMenuItemSprite* spriteItemGame = CCMenuItemSprite::create(gameButton, gameButton, this, menu_selector(GameScene4::goBackStoryCallBack));
    spriteItemGame->setPosition(ccp(0, 768));
    spriteItemGame->setAnchorPoint(ccp(0.0f, 1));
    
    allMenu = CCMenu::create(spriteItemGame, NULL);
    allMenu->setPosition(ccp(0, 0));
    allMenu->setZOrder(40);
    allMenu->setTouchPriority(-127);
    this->addChild(allMenu);
    
    playBackgroundMusic();
    
    //scheduleUpdate();
    return true;
}

void GameScene4::onEnterTransitionDidFinish()
{
    box->check(true);
//    gameOpenNode->opening(FOURTH_GAME_LOGO);
    scheduleOnce(schedule_selector(GameScene4::gameOpenIsEnd), 2.0f);
}

void GameScene4::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    if (isActting)
        return;
    if(box->isLocked())
        return;
	CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL( location );
    
    if (location.x < kStartX || location.y < kStartY || location.x > kStartX + kTileSize * kBoxWidth || location.y > kStartY + kTileSize * kBoxHeight)
    {
        return;
    }
    
    int x = (location.x - kStartX) / kTileSize;
	int y = (location.y - kStartY) / kTileSize;
    
    
	if (selectedTile->isUsed && selectedTile->x == x && selectedTile->y == y)
		return;
    
//    CCLog("ccTouchesBegan x, y = %d, %d", x, y);
    
    this->unschedule(schedule_selector(GameScene4::showHint));
    
    this->scheduleOnce(schedule_selector(GameScene4::showHint), 5.0f);
    
    GameTile *tile = box->objectAtXandY(x, y);
    if(selectedTile->isUsed && selectedTile->nearTile(tile))
    {
        box->setLock(true);
        
//        CCLog("selectedTile(x, y) = %d, %d", selectedTile->x, selectedTile->y);
//        CCLog("tile(x, y) = %d, %d", tile->x, tile->y);
        
        this->changeWithTileABandSel(selectedTile, tile, callfuncND_selector(GameScene4::checkSenderandData));
        selectedTile->isUsed = false;
    }
    else
    {
        if (selectedTile->isUsed)
        {
            selectedTile->sprite->stopAllActions();
            selectedTile->sprite->setScale(1);
        }
        
        selectedTile = tile;
        selectedTile->isUsed = true;
        this->afterOneShineTrun(tile->sprite);
    }
    
    isFirst = false;
}

void GameScene4::changeWithTileABandSel(GameTile* a,GameTile* b,SEL_CallFuncND sel)
{
    CCLog("changeWithTileABandSel");
    
    CCFiniteTimeAction* actionA = CCSequence::create(CCMoveTo::create(kMoveTileTime, b->pixPosition()), CCCallFuncND::create(this, sel, a), NULL);
    CCFiniteTimeAction* actionB = CCSequence::create(CCMoveTo::create(kMoveTileTime, a->pixPosition()), CCCallFuncND::create(this, sel, b), NULL);
    
    a->sprite->runAction(actionA);
    b->sprite->runAction(actionB);
    a->trade(b);
}

void GameScene4::checkSenderandData(GameTile* sender,GameTile* data)
{
    CCLog("checkSenderandData");
    
	if(!firstOne->isUsed){
		firstOne = data;
        firstOne->isUsed = true;
		return;
	}
    
    CCLog("firstOne = %d, %d", firstOne->x, firstOne->y);
    
	bool result = box->check(false);
	if (result)
    {
        box->setLock(false);
    }
	else
    {
        changeWithTileABandSel(data, firstOne, callfuncND_selector(GameScene4::afterCheckSenderandData));
	}
    
    firstOne->isUsed = false;
}

void GameScene4::afterCheckSenderandData(GameTile* sender,GameTile* data)
{
    CCLog("backcheckSenderandData");
    if(!firstOne->isUsed)
    {
        firstOne = data;
        firstOne->isUsed = true;
    }
    else
    {
        firstOne->isUsed = false;
        box->setLock(false);
    }
}

void GameScene4::afterOneShineTrun(CCSprite* asprite)
{
    CCLog("afterOneShineTrun");
    if(selectedTile->isUsed && asprite == selectedTile->sprite)
    {
        CCLog("afterOneShineTrun selectedTile(x, y) = %d, %d", selectedTile->x, selectedTile->y);
        
        oneShineTrun(asprite, true);
    }
}

void GameScene4::oneShineTrun(cocos2d::CCSprite *asprite, bool isRepeatWithJudge)
{
    SEL_CallFuncN sel;
    
    if (isRepeatWithJudge)
    {
        sel = callfuncN_selector(GameScene4::afterOneShineTrun);
    }
    else
    {
        sel = callfuncN_selector(GameScene4::oneShineTrun);
    }
    
    CCSprite* sprite = asprite;
    CCFiniteTimeAction* someAction =
    CCSequence::create(CCScaleBy::create(kMoveTileTime, 0.5f),
                       CCScaleBy::create(kMoveTileTime, 2.0f),
                       CCCallFuncN::create(this, sel), NULL);
    sprite->runAction(someAction);
}

#pragma mark -
#pragma mark 內部函數

void GameScene4::showScore(int score)
{
    isShowingScore = true;
    
    int index = 1;
    if (score == FIRST_SCORE_LEVEL)
    {
        index = 3;
        g4RedHatNode->runAnimation("Smile", 0);
    }
    else if (score == SECONE_SCORE_LEVEL)
    {
        index = 2;
        g4RedHatNode->runAnimation("Laugh", 0);
    }
    else if (score == THIRD_SCORE_LEVEL)
    {
        index = 1;
        g4RedHatNode->runAnimation("LaughHeartily", 0);
    }
    else
    {
        return;
    }
    
    CCString* name = CCString::createWithFormat("g03_+000%d.png", index);
    CCSprite* scoreShow = CCSprite::createWithSpriteFrame(imageCache->spriteFrameByName(name->getCString()));
    
    scoreShow->setAnchorPoint(ccp(0.5f, 0));
    scoreShow->setPosition(ccp(760, 500));
    scoreShow->setZOrder(45);
    
    addChild(scoreShow);
    
    CCMoveBy* move = CCMoveBy::create(2.0f, ccp(0,50));
    
    CCFadeOut* fadeOut = CCFadeOut::create(2.0f);
    
    CCActionInterval* fadeOutAndMove = CCSpawn::create(move,fadeOut,NULL);
    
    CCAction* fadeOutAct = CCSequence::create(fadeOutAndMove, CCCallFuncN::create(this, callfuncN_selector(GameScene4::deleteScoreObject)), NULL);
    
    scoreShow->runAction(fadeOutAct);
    
//    playSoundEffect(G11_ROCK_CAUGHT_SOUND);
}

void GameScene4::showDisappear(CCSprite* target)
{
    CCSprite* scoreShow = CCSprite::createWithSpriteFrame(imageCache->spriteFrameByName("g03_start0001.png"));
    
    scoreShow->setAnchorPoint(ccp(0.5f, 0.5f));
    scoreShow->setZOrder(45);
    
    addChild(scoreShow);
    
    CCAnimation* bigScoreAnimation = CCAnimation::create();
    for (int i = 1 ; i <= 10 ; i++)
    {
        CCString* tempString = CCString::createWithFormat("g03_start00%02d.png", i);
        bigScoreAnimation->addSpriteFrame(imageCache->spriteFrameByName(tempString->getCString()));
    }
    
    bigScoreAnimation->setDelayPerUnit(0.083f);
    
    CCFiniteTimeAction* bigScoreAction = CCRepeat::create(CCAnimate::create(bigScoreAnimation), 1);
    
    CCAction* bigScoreShowing = CCSequence::create(bigScoreAction, CCCallFuncN::create(this, callfuncN_selector(GameScene4::deleteScoreObject)), NULL);
    
    scoreShow->setPosition(ccp(target->getPositionX(), target->getPositionY()));
    
    scoreShow->runAction(bigScoreShowing);
    
//    playSoundEffect(G11_JEWEL_CAUGHT_SOUND);
}

void GameScene4::gameStarting()
{
    totalScore = 0;
    g4PictureMatchingNode->setScoreFont(totalScore);
    g4PictureMatchingNode->runAnimation("CountDown", 0);
    g4PictureMatchingStatus = G4_COUNT_DOWN;

    scheduleOnce(schedule_selector(GameScene4::playCountDownAlert), 50);
    
    setTouchEnabled(true);
}

int GameScene4::convertToScore(int count)
{
    int score = 0;
    if (count == 3)
    {
        score = FIRST_SCORE_LEVEL;
    }
    else if (count == 4)
    {
        score = SECONE_SCORE_LEVEL;
    }
    else if (count == 5)
    {
        score = THIRD_SCORE_LEVEL;
    }
    
    return score;
}

void GameScene4::ObjectsShowDisappear(cocos2d::CCArray *removeObjects)
{
    CCObject* temp;
    
    CCARRAY_FOREACH_REVERSE(removeObjects, temp)
    {
        showDisappear(((GameTile*)temp)->sprite);
    }
}

void GameScene4::playOperation()
{
    CCLog("playOperation");
    GameTile *tile = box->objectAtXandY(5, 6);
    
    oneShineTrun(tile->sprite, false);
    
    scheduleOnce(schedule_selector(GameScene4::playOperationAnother), 7);
}

void GameScene4::playOperationAnother()
{
    GameTile *tile = box->objectAtXandY(6, 6);
    
    oneShineTrun(tile->sprite, false);
}

void GameScene4::playSoundEffect(const char *soundName)
{
    int soundId =  SimpleAudioEngine::sharedEngine()->playEffect(soundName, false);
    
    if (music == soundId)
    {
        playBackgroundMusic();
    }
}

void GameScene4::playBackgroundMusic()
{
    if((ShareData::getInstance())->getMusicSwitch())
    {
        if (music != 0)
        {
//            SimpleAudioEngine::sharedEngine()->stopEffect(music);
            ShareMethod::getInstance()->stopLongSound(music);
        }
        
//        music = SimpleAudioEngine::sharedEngine()->playEffect(G4_BACKGROUND_MUSIC, true);
        music = ShareMethod::getInstance()->playLongSound(G4_BACKGROUND_MUSIC);
    }
}

void GameScene4::gameEnd()
{
    this->unschedule(schedule_selector(GameScene4::showHint));
    
    SimpleAudioEngine::sharedEngine()->stopAllEffects();
    ShareMethod::getInstance()->stopLongSound(music);
    CCLOG("total score = %d", totalScore);
    
    bool isBreakRecord = (ShareData::getInstance())->setFourthGameTheBestData(totalScore);
    int theBestScore = (ShareData::getInstance())->getFourthGameTheBestData();
    
    GameLanguageType languageType = (ShareData::getInstance())->getLanguageOfScene(4);
    gameEndNode->starting(languageType, totalScore, theBestScore, isBreakRecord);
    
    gameEndNode->setVisible(true);
    
}

void GameScene4::playCountDownAlert()
{
    playSoundEffect(G4_COUNT_DOWN_SOUND);
}

void GameScene4::playReadyGo()
{
    totalScore = 0;
    g4PictureMatchingNode->setScoreFont(totalScore);
    
    g4PictureMatchingNode->runAnimation("Default Timeline", 0);
    g4PictureMatchingStatus = G4_IDLE;
    gameOperationNode->playReadyGo();
}

void GameScene4::whenLeaving()
{
//    g4RedHatNode->releaseObject();
//    g4PictureMatchingNode->releaseObject();
//    gameEndNode->releaseObject();
//    gameOperationNode->releaseObject();
    
    
    CCLog("selectedTile retain count = %d", selectedTile->retainCount());
    CCLog("firstOne retain count = %d", firstOne->retainCount());
    
//    if (selectedTile->retainCount() > 0) {
//        selectedTile->release();
//    }
//    
//    if (firstOne->retainCount() > 0) {
//        firstOne->release();
//    }
    
    this->unscheduleAllSelectors();
    
    SimpleAudioEngine::sharedEngine()->unloadEffect(G4_INTRODUCE);
    SimpleAudioEngine::sharedEngine()->unloadEffect(G4_INTRODUCE_EN);
    
    SimpleAudioEngine::sharedEngine()->unloadEffect(G4_BACKGROUND_MUSIC);
    SimpleAudioEngine::sharedEngine()->unloadEffect(G4_COUNT_DOWN_SOUND);
    SimpleAudioEngine::sharedEngine()->unloadEffect(G4_MATCHING_SOUND);
    SimpleAudioEngine::sharedEngine()->unloadEffect(G4_RESETING_SOUND);
    
    CCTextureCache::sharedTextureCache()->removeTextureForKey("g03_flower0001.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("g03_flower0002.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("g03_flower0003.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("g03_flower0004.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("g03_flower0005.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("g03_flower0006.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("g03_flower0007.png");
    
}

#pragma mark -
#pragma mark 事件回傳

void GameScene4::deleteScoreObject(cocos2d::CCNode *pSender)
{
    removeChild(pSender);
    
    isShowingScore = false;
}

void GameScene4::matchedCallBack(cocos2d::CCSprite *pSender, RemoveMatchingData* removeObjects)
{
    if (!isFirst)
    {
        CCLog("tag = %d, count = %d, removeObject count = %d", pSender->getTag(), removeObjects->getCount(), removeObjects->getRemoveObjects()->count());
        
        isActting = true;

        if (removeObjects->getCount() >= 3 && removeObjects->getCount() <= 5)
        {
            playSoundEffect(G4_MATCHING_SOUND);
        }
        else if (removeObjects->getCount() == 7)
        {
            playSoundEffect(G4_RESETING_SOUND);
        }
        
        int score = convertToScore(removeObjects->getCount());
        
        //得分
        showScore(score);
        //消失特效
        ObjectsShowDisappear(removeObjects->getRemoveObjects());
        
        totalScore += score;
        
        g4PictureMatchingNode->setScoreFont(totalScore);
        
    }
}

void GameScene4::countDownCallBack()
{
    if (g4PictureMatchingStatus == G4_COUNT_DOWN)
    {
        setTouchEnabled(false);
        gameEnd();
    }
}

void GameScene4::gameOpenIsEnd()
{
    gameOperationNode->playOperationShow();
    playOperation();
    isOpening = false;
}

void GameScene4::onOperated()
{
    GameTile *tile1 = box->objectAtXandY(5, 6);
    GameTile *tile2 = box->objectAtXandY(6, 6);
    
    tile1->sprite->stopAllActions();
    tile2->sprite->stopAllActions();
    
    tile1->sprite->setScale(1);
    tile2->sprite->setScale(1);

    playReadyGo();
}

void GameScene4::onReadyGoOver()
{
    gameStarting();
    
    this->scheduleOnce(schedule_selector(GameScene4::showHint), 5.0f);
}

void GameScene4::playAgain()
{
    isFirst = true;
    SimpleAudioEngine::sharedEngine()->stopAllEffects();
    ShareMethod::getInstance()->stopLongSound(music);
    gameEndNode->setVisible(false);
    box->reset();
    playReadyGo();
    
    playBackgroundMusic();
}

void GameScene4::goBackStoryCallBack()
{
    CCLOG("goBackStoryCallBack");
    if (!isOpening)
    {
        if (isShowingScore)
            return;
        
        //遮罩
        CCSprite* maskButton = CCSprite::create();
        CCRect maskZoneSize = CCRectMake(0, 0, 1024, 768);
        maskButton->setTextureRect(maskZoneSize);
        maskButton->setOpacity(0);
        
        CCMenuItemSprite* spriteItemMask = CCMenuItemSprite::create(maskButton, maskButton, NULL, NULL);
        spriteItemMask->setAnchorPoint(ccp(0, 0));
        
        CCMenu* mask = CCMenu::create(spriteItemMask, NULL);
        mask->setPosition(ccp(0, 0));
        mask->setZOrder(100);
        this->addChild(mask);
        
        mask->setTouchPriority(-150);
        mask->setVisible(true);
        
        setTouchEnabled(false);
        
        whenLeaving();
        
        SimpleAudioEngine::sharedEngine()->stopAllEffects();
        ShareMethod::getInstance()->stopLongSound(music);
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
        
        CCDirector *pDirector = CCDirector::sharedDirector();
        
        // create a scene. it's an autorelease object
        CCScene *pScene = StartScene::scene();
        
        // replace
        pDirector->replaceScene(pScene);
    }
}

void GameScene4::showHint()
{
    CCSprite* target = box->showHint();
    
    if (target)
    {
        showDisappear(target);
        
    }
}

void GameScene4::allActionDoneCallBack()
{
    isActting = false;
}