//
//  RemoveMatchingData.cpp
//  RedHat
//
//  Created by Mac-8 on 13/9/25.
//
//

#include "RemoveMatchingData.h"

RemoveMatchingData::RemoveMatchingData()
{
    
}

RemoveMatchingData::~RemoveMatchingData()
{
    removeObjects->removeAllObjects();
}

RemoveMatchingData* RemoveMatchingData::create(cocos2d::CCArray* needToRemoveObjects, int removeCount)
{
    RemoveMatchingData* object = new RemoveMatchingData();
    
    object->removeObjects = needToRemoveObjects;
    object->count = removeCount;
    
    object->autorelease();
    
    return object;
}

int RemoveMatchingData::getCount()
{
    return count;
}

CCArray* RemoveMatchingData::getRemoveObjects()
{
    return removeObjects;
}