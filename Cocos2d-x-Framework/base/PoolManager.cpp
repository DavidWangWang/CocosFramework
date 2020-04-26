//
//  PoolManager.cpp
//  Cocos2d-x-Framework
//
//  Created by David on 2020/4/21.
//  Copyright © 2020 David. All rights reserved.
//

#include "PoolManager.hpp"
#include "PlatformDefine-ios.h"
#include <string>
//#include "Action.hpp"

NS_CC_BEGIN

PoolManager* PoolManager::s_singleInstance = nullptr;

PoolManager* PoolManager::getInstance()
{
    if (s_singleInstance == nullptr)
    {
        s_singleInstance = new (std::nothrow) PoolManager();
        // Add the first auto release pool
        new AutoreleasePool("cocos2d autorelease pool");
    }
    return s_singleInstance;
}

void PoolManager::destroyInstance()
{
    delete s_singleInstance;
    s_singleInstance = nullptr;
}

PoolManager::PoolManager()
{
    _releasePoolStack.reserve(10);
}

PoolManager::~PoolManager()
{
    
}

void PoolManager::push(AutoreleasePool *pool)
{
    this->_releasePoolStack.push_back(pool);
}


void PoolManager::pop()
{
    CC_ASSERT(!_releasePoolStack.empty());
    _releasePoolStack.pop_back();
}

bool PoolManager::isObjectInPool(Ref *ref) const
{
    for (auto &obj : _releasePoolStack) {
        if (obj->contains(ref)) {
            return true;
        }
    }
    return false;
}

AutoreleasePool *PoolManager::getCurrentPool() const
{
    return _releasePoolStack.back();
}



NS_CC_END
