//
//  Ref.cpp
//  CocosFramework
//
//  Created by David on 2020/4/13.
//  Copyright © 2020 David. All rights reserved.
//

#include "Ref.hpp"
#include "CCScriptSupport.hpp"
#include "PlatformDefine-ios.h"
#include "ccMacros.h"
#include "PoolManager.hpp"
#include <mutex>
NS_CC_BEGIN

extern void log(std::string &name);

#if CC_REF_LEAK_DETECTION
static void trackRef(Ref* ref);
static void untrackRef(Ref* ref);
#endif

Ref::Ref()
: _referenceCount(1)
#if CC_ENABLE_SCRIPT_BINDING
, _luaID(0)
, _scriptObject(nullptr)
, _rooted(false)
#endif
{
#if CC_ENABLE_SCRIPT_BINDING
    static unsigned int uObjectCount = 0;
    this->_ID  = ++uObjectCount;
#endif

#if CC_REF_LEAK_DETECTION
    trackRef(this);
#endif
}


Ref::~Ref()
{
#if CC_ENABLE_SCRIPT_BINDING
    ScriptEngineProtocol* pEngine = ScriptEngineManager::getInstance()->getScriptEngine();
    if (pEngine != nullptr && _luaID) {
        pEngine->removeScriptObjectByObject(this);
    }
#if !CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    else
    {
        if (pEngine != nullptr && pEngine->getScriptType() == kScriptTypeJavascript)
        {
            pEngine->removeScriptObjectByObject(this);
        }
    }
#endif
#endif
    
#if CC_REF_LEAK_DETECTION
    if (_referenceCount != 0) {
        untrackRef(this);
    }
#endif
}

void Ref::retain()
{
    CCASSERT(_referenceCount > 0, "reference count should be greater than 0");
    ++ this->_referenceCount;
}

void Ref::release()
{
    CCASSERT(_referenceCount > 0, "reference count should be greater than 0");
    -- this->_referenceCount;
    if (this->_referenceCount == 0) {
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
        auto poolManager = PoolManager::getInstance();
        if (!poolManager->getCurrentPool()->isClearing() && poolManager->isObjectInPool(this)) {
            CCASSERT(false, "The reference shouldn't be 0 because it is still in autorelease pool.");
        }
#endif
#if CC_ENABLE_SCRIPT_BINDING
        ScriptEngineProtocol *pEngine = ScriptEngineManager::getInstance()->getScriptEngine();
        if (nullptr != pEngine && pEngine->getScriptType() == kScriptTypeJavascript) {
            pEngine->removeObjectProxy(this);
        }
#endif
        #if CC_REF_LEAK_DETECTION
                untrackRef(this);
        #endif
        delete this;
    }
}

Ref* Ref::autorelease()
{
    PoolManager::getInstance()->getCurrentPool()->addObject(this);
    return this;
}

unsigned int Ref::getReferenceCount() const
{
    return _referenceCount;
}

#if CC_REF_LEAK_DETECTION

static std::vector<Ref *> __refAllocationList;
static std::mutex __refMutex;   // 互斥锁

void Ref::printLeaks()
{
    std::lock_guard<std::mutex> refLockGuard(__refMutex);
    if (__refAllocationList.empty()) {
        log("[memory] All Ref objects successfully cleaned up (no leaks detected).\n");
    } else {
        log("[memory] WARNING: %d Ref objects still active in memory.\n", (int)__refAllocationList.size());
        for (const auto &ref : __refAllocationList) {
             CC_ASSERT(ref);
             const char* type = typeid(*ref).name();
             log("[memory] LEAK: Ref object '%s' still active with reference count %d.\n", (type ? type : ""), ref->getReferenceCount());
        }
    }
}

static void traceRef(Ref *ref)
{
    std::lock_guard<std::mutex> refLockGuard(__refMutex);
    CCASSERT(ref, "Invalid parameter, ref should not be null!");
    __refAllocationList.push_back(ref);
}

// 遍历并打印
static void untrackRef(Ref *ref)
{
    std::lock_guard<std::mutex> refLockGuard(__refMutex);
    auto iter = std::find(__refAllocationList.begin(), __refAllocationList.end(), ref);
    if (iter == __refAllocationList.end()) {
        log("[memory] CORRUPTION: Attempting to free (%s) with invalid ref tracking record.\n", typeid(*ref).name());
        return;
    }
    __refAllocationList.erase(iter);
}

#endif

NS_CC_END


