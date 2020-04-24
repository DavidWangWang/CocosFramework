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
NS_CC_BEGIN

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
            
#endif
        
    }
    
}


NS_CC_END


