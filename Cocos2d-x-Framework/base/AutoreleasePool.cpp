//
//  AutoreleasePool.cpp
//  Cocos2d-x-Framework
//
//  Created by David on 2020/4/22.
//  Copyright © 2020 David. All rights reserved.
//

#include "AutoreleasePool.hpp"
#include "PoolManager.hpp"
#include "PlatformMacros.h"

NS_CC_BEGIN

AutoreleasePool::AutoreleasePool()
:_name("")
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
, _isClearing(false)
#endif
{
//    改变当前vecotr所分配空间的大小
    _manageObjectArray.reserve(150);
    PoolManager::getInstance()->push(this);
    
}

AutoreleasePool::AutoreleasePool(const std::string &name)
: _name(name)
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
, _isClearing(false)
#endif
{
    _manageObjectArray.reserve(150);
    PoolManager::getInstance()->push(this);
}

AutoreleasePool::~AutoreleasePool()
{
    CCLOGINFO("deallocing AutoreleasePool: %p", this);
    this->clear();
    PoolManager::getInstance()->pop();
}

void AutoreleasePool::clear()
{
    #if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
        _isClearing = true;
    #endif
    std::vector<Ref *> releasings;
    releasings.swap(_manageObjectArray);
    for (const auto &obj : releasings) {
        obj->release();
    }
    #if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
        _isClearing = false;
    #endif
}

void AutoreleasePool::addObject(Ref *object)
{
    if (nullptr == object) {
        return;
    }
    this->_manageObjectArray.push_back(object);
}

bool AutoreleasePool::contains(Ref *object) const
{
    for (const auto &obj : _manageObjectArray) {
        if (obj == object) {
            return true;
        }
    }
    return false;
}

void AutoreleasePool::dump()
{
    CCLOG("autorelease pool: %s, number of managed object %d\n", _name.c_str(), static_cast<int>(_managedObjectArray.size()));
    CCLOG("%20s%20s%20s", "Object pointer", "Object id", "reference count");
    for (const auto &obj : _manageObjectArray)
    {
       CCLOG("%20p%20u\n", obj, obj->getReferenceCount());
    }
}

NS_CC_END
