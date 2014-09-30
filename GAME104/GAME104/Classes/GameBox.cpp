#include "GameBox.h"
#include <math.h>

GameBox::GameBox(CCSize asize,int afactor)
{
    size = asize;
    
    OutBorderTile = NULL;
    readyToRemoveTiles = NULL;
    
    OutBorderTile = new GameTile(-1,-1);
    content = CCArray::createWithCapacity(size.height);
	content->retain();
    
	for (int y=0; y < size.height; y++) {
		CCArray* rowContent = CCArray::createWithCapacity(size.width);
		for (int x=0; x < size.width; x++) {
			GameTile *tile = new GameTile(x,y);
            tile->value = 0;
            tile->sprite = CCSprite::create();
            rowContent->addObject(tile);
            tile->autorelease();
		}
        content->addObject(rowContent);
	}
    
    readyToRemoveTiles = CCArray::createWithCapacity(size.height);
    readyToRemoveTiles->retain();
    
    first = NULL;
    second = NULL;
    
    targetListener = NULL;
    matchedCompeleted = NULL;
    allActionDoneCompeleted = NULL;
}

GameBox::~GameBox()
{
    CCLog("~GameBox()");
    
    CCObject* temp;
    
    CCARRAY_FOREACH_REVERSE(content, temp)
    {
        CCArray* rowContent = (CCArray*)temp;
        
        rowContent->removeAllObjects();
        
    }
    
    content->removeAllObjects();
    CC_SAFE_RELEASE_NULL(readyToRemoveTiles);
    CC_SAFE_RELEASE_NULL(content);
    
    CC_SAFE_DELETE(OutBorderTile);
    
    targetListener = NULL;
    matchedCompeleted = NULL;
    allActionDoneCompeleted = NULL;
}

GameTile* GameBox::objectAtXandY(int posX,int posY)
{
	if (posX < 0 || posX >= kBoxWidth || posY < 0 || posY >= kBoxHeight)
		return OutBorderTile;
    return (GameTile* )((CCArray*)content->objectAtIndex(posY))->objectAtIndex(posX);
}

void GameBox::checkWith(Orientation orient)
{
	int iMax = (orient == OrientationHori) ? size.width : size.height;
	int jMax = (orient == OrientationVert) ? size.height : size.width;
    
    int removeCount = 0;
	for (int i=0; i<iMax; i++)
    {
		int count = 0;
		int value = -1;
        first = NULL;
        second = NULL;
        GameTile* tile = NULL;
        
        CCArray* removeForOneLine = CCArray::create();

		for (int j=0; j<jMax; j++)
        {
//            CCLog("i, j = %d, %d", i, j);
            
            tile = this->objectAtXandY((orient == OrientationHori) ? i :j,(orient == OrientationHori) ? j :i);
            
//            CCLog("value = %d", value);
//            CCLog("tile value = %d", tile->value);
            
            if (value > kBoxWidth)
            {
                value = 0;
            }
            
			if(tile->value == value)
            {
				count++;
				if (count > 3)
                {
                    removeCount++;
//                    CCLog("count > 3");
                    readyToRemoveTiles->addObject(tile);
                    
                    removeForOneLine->addObject(tile);
				}
                else if (count == 3)
                {
                    removeCount = 3;
//                    CCLog("count == 3");
                    readyToRemoveTiles->addObject(first);
                    readyToRemoveTiles->addObject(second);
                    readyToRemoveTiles->addObject(tile);
                    
                    removeForOneLine->addObject(first);
                    removeForOneLine->addObject(second);
                    removeForOneLine->addObject(tile);
                    
                    first = NULL;
                    second = NULL;
                }
                else if (count == 2) {
                    second = tile;
                }
                else {
                }
				
			}
            else
            {
				count = 1;
				first = tile;
                second = NULL;
				value = tile->value;
			}
            
//            CCLog("after value = %d", value);
		}
        
        if (removeCount >= 3)
        {
//            CCLog("remove object count = %d", removeCount);
            if (tile->sprite)
            {
                if (targetListener && matchedCompeleted)
                {
                    RemoveMatchingData* removeMatchingData = RemoveMatchingData::create(removeForOneLine, removeCount);
                    
                    (targetListener->*matchedCompeleted)((CCSprite*)tile->sprite, (void*) removeMatchingData);
                }
            }
            removeCount = 0;
        }
	}
}

bool GameBox::check(bool isFirstTime)
{
    checkWith(OrientationHori);
    checkWith(OrientationVert);
    
	if (readyToRemoveTiles->count() == 0)
		return false;
	int count = readyToRemoveTiles->count();
	for (int i=0; i < count; i++)
    {
//        CCLog("readyToRemoveTiles index = %d", i);
        GameTile* tile = (GameTile*)readyToRemoveTiles->objectAtIndex(i);
        tile->value = 0;
        if (!isFirstTime)
        {
            if (tile->sprite)
            {
                CCSequence* actionSequence = CCSequence::create(CCScaleTo::create(0.3f, 0.0f),
                                                                CCCallFuncN::create(this, callfuncN_selector(GameBox::removeSprite)),
                                                                NULL);
                tile->sprite->runAction(actionSequence);
            }
        }
	}
    
    readyToRemoveTiles->removeAllObjects();
    int maxCount = this->repair();
    
    layer->runAction(CCSequence::create(CCDelayTime::create(kFallTileTime * maxCount + 0.03f),
                                        CCCallFunc::create(this, callfunc_selector(GameBox::afterAllMoveDone)),
                                        NULL));
	return true;
}

void GameBox::setLock(bool ff)
{
    lock = ff;
}

bool GameBox::isLocked()
{
    return lock;
}

void GameBox::removeSprite(GameTile* sender)
{
    CCLog("removeSprite");
    layer->removeChild(sender, true);
}

void GameBox::afterAllMoveDone()
{
    CCLog("afterAllMoveDone");
    if(check(false))
        return;
    if(haveMore())
    {
        setLock(false);
        if (targetListener && allActionDoneCompeleted)
        {
            (targetListener->*allActionDoneCompeleted)();
        }
    }
    else
    {
        CCLog("is reset");
        for (int y=0; y< kBoxHeight; y++) {
            for (int x=0; x< kBoxWidth; x++) {
                GameTile* tile = objectAtXandY(x, y);
                tile->value = 0;
            }
        }
        check(false);
    }
    
}

int GameBox::repair()
{
    CCLog("repair");
	int maxCount = 0;
	for (int x=0; x<size.width; x++) {
        int count = repairSingleColumn(x);
		if (count > maxCount) {
			maxCount = count;
		}
	}
	return maxCount;
}

int GameBox::repairSingleColumn(int columnIndex)
{
	int extension = 0;
    int y = 0;
	for (y=0; y<size.height; y++)
    {
        GameTile* tile = objectAtXandY(columnIndex, y);
        if(tile->value == 0)
        {
            extension++;
        }
        else if (extension == 0)
        {

        }
        else
        {
            GameTile* destTile = objectAtXandY(columnIndex, y - extension);
            tile->sprite->runAction(CCMoveBy::create(kFallTileTime * extension, ccp(0,-kTileSize*extension)));
            destTile->value = tile->value;
            destTile->sprite = tile->sprite;
        }
	}

	for (int i=0; i<extension; i++)
    {
		int value = (arc4random()%kKindCount+1);
        GameTile* destTile = objectAtXandY(columnIndex, kBoxHeight-extension+i);
        CCString* name = CCString::createWithFormat("g03_flower000%d.png",value);
		CCSprite *sprite = CCSprite::create(name->getCString());
        sprite->setTag(columnIndex * 10 + i);
//        CCLog("%d,%d name = %s", columnIndex, i, name->getCString());
		sprite->setPosition(ccp(kStartX + columnIndex * kTileSize + kTileSize/2, kStartY + (kBoxHeight + i) * kTileSize + kTileSize/2));
        layer->addChild(sprite);
        sprite->runAction(CCMoveBy::create(kFallTileTime * extension, ccp(0,-kTileSize*extension)));
		destTile->value = value;
		destTile->sprite = sprite;
	}
	return extension;
}

bool GameBox::haveMore()
{
	for (int y=0; y<size.height; y++)
    {
		for (int x=0; x<size.width; x++)
        {
            GameTile* aTile = objectAtXandY(x, y);
			//v 1 2
			if (aTile->y-1 >= 0) {
                GameTile* bTile = objectAtXandY(x, y-1);
				if (aTile->value == bTile->value) {
					{
                        GameTile* cTile = objectAtXandY(x, y+2);
						if (cTile->value == aTile->value)
                        {
							return true;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x-1, y+1);
						if (cTile->value == aTile->value)
                        {
							return true;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x+1, y+1);
						if (cTile->value == aTile->value)
                        {
							return true;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x,y-3);
						if (cTile->value == aTile->value)
                        {
							return true;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x-1, y-2);
						if (cTile->value == aTile->value)
                        {
							return true;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x+1, y-2);
						if (cTile->value == aTile->value)
                        {
							return true;
                        }
					}
                }
			}
			//v 1 3
			if (aTile->y-2 >= 0) {
				GameTile *bTile = objectAtXandY(x, y-2);
				if (aTile->value == bTile->value)
                {
					{
                        GameTile* cTile = objectAtXandY(x, y+1);
						if (cTile->value == aTile->value)
                        {
							return true;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x,y-3);
						if (cTile->value == aTile->value)
                        {
							return true;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x-1, y-1);
						if (cTile->value == aTile->value)
                        {
							return true;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x+1, y-1);
						if (cTile->value == aTile->value)
                        {
							return true;
                        }
					}
				}
			}
			// h 1 2
			if (aTile->x+1 < kBoxWidth) {
                GameTile* bTile = objectAtXandY(x+1, y);
				if (aTile->value == bTile->value) {
					{
                        GameTile* cTile = objectAtXandY(x-2, y);
						if (cTile->value == aTile->value)
                        {
							return true;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x-1, y-1);
						if (cTile->value == aTile->value)
                        {
							return true;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x-1, y+1);
						if (cTile->value == aTile->value)
                        {
							return true;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x+3, y);
						if (cTile->value == aTile->value)
                        {
							return true;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x+2, y-1);
						if (cTile->value == aTile->value)
                        {
							return true;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x+2, y+1);
						if (cTile->value == aTile->value)
                        {
							return true;
                        }
					}
				}
			}			
			//h 1 3
			if (aTile->x+2 >= kBoxWidth) {
                GameTile* bTile = objectAtXandY(x+2, y);
				if (aTile->value == bTile->value)
                {
					{
                        GameTile* cTile = objectAtXandY(x+3, y);
						if (cTile->value == aTile->value)
                        {
							return true;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x-1, y);
						if (cTile->value == aTile->value)
                        {
							return true;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x+1, y-1);
						if (cTile->value == aTile->value)
                        {
							return true;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x+1, y+1);
						if (cTile->value == aTile->value)
                        {
							return true;
                        }
					}
				}
			}
		}
	}
	return false;
}

CCSprite* GameBox::showHint()
{
	for (int y=0; y<size.height; y++)
    {
		for (int x=0; x<size.width; x++)
        {
            GameTile* aTile = objectAtXandY(x, y);
			//v 1 2
			if (aTile->y-1 >= 0) {
                GameTile* bTile = objectAtXandY(x, y-1);
				if (aTile->value == bTile->value) {
					{
                        GameTile* cTile = objectAtXandY(x, y+2);
						if (cTile->value == aTile->value)
                        {
							return cTile->sprite;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x-1, y+1);
						if (cTile->value == aTile->value)
                        {
							return cTile->sprite;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x+1, y+1);
						if (cTile->value == aTile->value)
                        {
							return cTile->sprite;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x,y-3);
						if (cTile->value == aTile->value)
                        {
							return cTile->sprite;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x-1, y-2);
						if (cTile->value == aTile->value)
                        {
							return cTile->sprite;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x+1, y-2);
						if (cTile->value == aTile->value)
                        {
							return cTile->sprite;
                        }
					}
                }
			}
			//v 1 3
			if (aTile->y-2 >= 0) {
				GameTile *bTile = objectAtXandY(x, y-2);
				if (aTile->value == bTile->value)
                {
					{
                        GameTile* cTile = objectAtXandY(x, y+1);
						if (cTile->value == aTile->value)
                        {
							return cTile->sprite;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x,y-3);
						if (cTile->value == aTile->value)
                        {
							return cTile->sprite;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x-1, y-1);
						if (cTile->value == aTile->value)
                        {
							return cTile->sprite;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x+1, y-1);
						if (cTile->value == aTile->value)
                        {
							return cTile->sprite;
                        }
					}
				}
			}
			// h 1 2
			if (aTile->x+1 < kBoxWidth) {
                GameTile* bTile = objectAtXandY(x+1, y);
				if (aTile->value == bTile->value) {
					{
                        GameTile* cTile = objectAtXandY(x-2, y);
						if (cTile->value == aTile->value)
                        {
							return cTile->sprite;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x-1, y-1);
						if (cTile->value == aTile->value)
                        {
							return cTile->sprite;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x-1, y+1);
						if (cTile->value == aTile->value)
                        {
							return cTile->sprite;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x+3, y);
						if (cTile->value == aTile->value)
                        {
							return cTile->sprite;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x+2, y-1);
						if (cTile->value == aTile->value)
                        {
							return cTile->sprite;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x+2, y+1);
						if (cTile->value == aTile->value)
                        {
							return cTile->sprite;
                        }
					}
				}
			}
			//h 1 3
			if (aTile->x+2 >= kBoxWidth) {
                GameTile* bTile = objectAtXandY(x+2, y);
				if (aTile->value == bTile->value)
                {
					{
                        GameTile* cTile = objectAtXandY(x+3, y);
						if (cTile->value == aTile->value)
                        {
							return cTile->sprite;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x-1, y);
						if (cTile->value == aTile->value)
                        {
							return cTile->sprite;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x+1, y-1);
						if (cTile->value == aTile->value)
                        {
							return cTile->sprite;
                        }
					}
					{
                        GameTile* cTile = objectAtXandY(x+1, y+1);
						if (cTile->value == aTile->value)
                        {
							return cTile->sprite;
                        }
					}
				}
			}
		}
	}
	return NULL;
}

void GameBox::setEventCallBack(cocos2d::CCObject *targetListener, SEL_CallFuncND matchedCompeleted, SEL_CallFunc allActionDoneCompeleted)
{
    this->targetListener = targetListener;
    this->matchedCompeleted = matchedCompeleted;
    this->allActionDoneCompeleted = allActionDoneCompeleted;
}

void GameBox::reset()
{
    CCLog("is reset");
    for (int y=0; y< kBoxHeight; y++) {
        for (int x=0; x< kBoxWidth; x++) {
            GameTile* tile = objectAtXandY(x, y);
            tile->value = 0;
        }
    }
    check(false);
}
