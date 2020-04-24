//
//  CCScriptSupport.cpp
//  Cocos2d-x-Framework
//
//  Created by David on 2020/4/21.
//  Copyright © 2020 David. All rights reserved.
//

#include "CCScriptSupport.hpp"

bool CC_DLL cc_assert_script_compatible(const char *msg)
{
    cocos2d::ScriptEngineProtocol* engine = cocos2d::ScriptEngineManager::getInstance()->getScriptEngine();
    if (engine && engine->handleAssert(msg)) {
        return true;
    }
    return false;
}

NS_CC_BEGIN

static ScriptEngineManager* s_pSharedScriptEngineManager = nullptr;

void ScriptEngineManager::setScriptEngine(ScriptEngineProtocol *scriptEngine)
{
    if (_scriptEngine != scriptEngine) {
        removeScriptEngine();
        _scriptEngine = scriptEngine;
    }
}

void ScriptEngineManager::removeScriptEngine()
{
    if (_scriptEngine) {
        delete _scriptEngine;
        _scriptEngine = nullptr;
    }
}

ScriptEngineManager* ScriptEngineManager::getInstance()
{
    if (!s_pSharedScriptEngineManager)
    {
        s_pSharedScriptEngineManager = new (std::nothrow) ScriptEngineManager();
    }
    return s_pSharedScriptEngineManager;
}




NS_CC_END
