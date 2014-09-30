#ifndef __ShakeForFood2__Tile__
#define __ShakeForFood2__Tile__

#include <cocos2d.h>
#include "constants.h"

using namespace cocos2d;

class GameTile : public CCNode
{
public:
    int x;
    int y;
    int value;
    CCSprite* sprite;
    bool isUsed;
public:
	GameTile(int ax,int ay);
	~GameTile();
    bool nearTile(GameTile* othertile);
    void trade(GameTile* othertile);
    CCPoint pixPosition();
    
    static GameTile* create(int ax,int ay);
};

#endif
