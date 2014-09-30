//
//  RemoveMatchingData.h
//  RedHat
//
//  Created by Mac-8 on 13/9/25.
//
//

#ifndef __RedHat__RemoveMatchingData__
#define __RedHat__RemoveMatchingData__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class RemoveMatchingData : public CCObject
{
public:
    RemoveMatchingData();
    ~RemoveMatchingData();

    static RemoveMatchingData* create(CCArray* needToRemoveObjects, int removeCount);
    
    int getCount();
    
    CCArray* getRemoveObjects();

private:
    CCArray* removeObjects;
    int count;

};

#endif /* defined(__RedHat__RemoveMatchingData__) */
