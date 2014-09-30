//
//  Tile.cpp
//  ShakeForFood2
//
//  Created by apple on 12-10-18.
//
//

#include "GameTile.h"
#include <math.h>

GameTile::GameTile(int ax,int ay)
{
    x = ax;
    y = ay;
}

GameTile::~GameTile(void)
{
    sprite = NULL;
}

GameTile* GameTile::create(int ax,int ay)
{
    GameTile* newTile = new GameTile(ax, ay);
    if (newTile && newTile->init())
    {
        newTile->autorelease();
        newTile->isUsed = false;
        return newTile;
    }
    else
    {
        delete newTile;
        newTile = NULL;
        return NULL;
    }
}

bool GameTile::nearTile(GameTile* othertile)
{
	return
	(x == othertile->x && abs(y - othertile->y)==1)||
	(y == othertile->y && abs(x - othertile->x)==1);
}
void GameTile::trade(GameTile* othertile)
{
    CCLog("othertile(x, y) = %d, %d", othertile->x, othertile->y);
    CCLog("original(x, y) = %d, %d", x, y);
    
    CCSprite* tempSprite = sprite;
	int tempValue = value;
	sprite = othertile->sprite;
	value = othertile->value;
	othertile->sprite = tempSprite;
	othertile->value = tempValue;
    tempSprite = NULL;
    
    CCLog("after othertile(x, y) = %d, %d", othertile->x, othertile->y);
    CCLog("after original(x, y) = %d, %d", x, y);
}

CCPoint GameTile::pixPosition()
{
	return ccp(kStartX + x * kTileSize +kTileSize/2.0f,kStartY + y * kTileSize +kTileSize/2.0f);
}
