#ifndef __ShakeForFood2__Box__
#define __ShakeForFood2__Box__

#include <cocos2d.h>
#include "GameTile.h"
#include "constants.h"
#include "RemoveMatchingData.h"

using namespace cocos2d;

class GameBox: public CCNode
{
public:
    GameTile* first;
    GameTile* second;
    CCSize size;
    CCArray* content;
    CCArray* readyToRemoveTiles;
    CCLayer* layer;
    GameTile* OutBorderTile;
private:
    bool lock;
    CCObject *targetListener;
    SEL_CallFuncND matchedCompeleted;
    SEL_CallFunc allActionDoneCompeleted;
    
public:
	GameBox(CCSize asize,int afactor);
    ~GameBox();
    GameTile* objectAtXandY(int posX,int posY);
    void checkWith(Orientation orient);
    bool check(bool isFirstTime);
    void setLock(bool ff);
    bool isLocked();
    void removeSprite(GameTile* sender);
    void afterAllMoveDone();
    bool haveMore();
    int repair();
    int repairSingleColumn(int columnIndex);
    
    void setEventCallBack(CCObject *targetListener, SEL_CallFuncND matchedCompeleted, SEL_CallFunc allActionDoneCompeleted);
    void reset();
    
    CCSprite* showHint();
};

#endif
