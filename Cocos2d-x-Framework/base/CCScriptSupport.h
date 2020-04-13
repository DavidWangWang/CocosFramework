//
//  CCScriptSupport.h
//  Cocos2d-x-Framework
//
//  Created by David on 2020/4/13.
//  Copyright © 2020 David. All rights reserved.
//

#ifndef CCScriptSupport_h
#define CCScriptSupport_h
#include "PlatformDefine-ios.h"
#include "Ref.hpp"
#include <string>

NS_CC_BEGIN

enum ccScriptType {
    kScriptTypeNone = 0,
    kScriptTypeLua,
    kScriptTypeJavascript
};

/** ScriptEventType enum*/
enum ScriptEventType
{
    kNodeEvent = 0,
    kMenuClickedEvent,
    kCallFuncEvent,
    kScheduleEvent,
    kTouchEvent,
    kTouchesEvent,
    kKeypadEvent,
    kAccelerometerEvent,
    kControlEvent,
    kCommonEvent,
    kComponentEvent,
    kRestartGame,
    kScriptActionEvent
};

struct ScriptEvent
{
    ScriptEventType type;

    void* data;

    ScriptEvent(ScriptEventType inType, void* inData)
    : type(inType),
    data(inData)
    {

    }
};


class Node;

class CC_DLL ScriptEngineProtocol
{
public:
    ScriptEngineProtocol()
      {}
      
      /**
       * Destructor of ScriptEngineProtocol.
       *
       * @lua NA
       * @js NA
       */
    virtual ~ScriptEngineProtocol() {}
    
    virtual ccScriptType getScriptType() {return  kScriptTypeNone;}
    /**
     * Reflect the retain relationship to script scope
     */
    virtual void retainScriptObject(Ref* /*owner*/, Ref* /*target*/) {}
    
    virtual void rootScriptObject(Ref*) {}
    
    /**
     * Reflect the release relationship to script scope
     */
    virtual void releaseScriptObject(Ref* /*owner*/, Ref* /*target*/) {}
    
    virtual void unrootScriptObject(Ref* /*target*/) {}
    
    virtual void releaseAllChildrenRecusize(Node* /*node*/) {}
    
    virtual void eleaseAllNativeRefs(Ref* /*owner*/) {}
    
    virtual void removeScriptObjectByObject(Ref* /*obj*/) {}
    
    virtual void removeScriptHandler(int) {}
    
    virtual int reallocateScriptHandler(int /*handler*/) { return 0; }

    virtual int executeString(const char* codes) = 0;
    
    virtual int executeScriptFile(const char* filename) = 0;
    
    virtual int executeGlobalFunction(const char* functionName) = 0;
    
    virtual int sendEvent(ScriptEventType* evt) = 0;
    
    virtual bool handleAssert(const char *msg) = 0;
    
    /**
     * Useless for Lua.
     *
     * @lua NA
     * @js NA
     */
    virtual void setCalledFromScript(bool /*callFromScript*/) {}

    virtual bool isCalledFromScript() {return  false; }
    
    enum class ConfigType
    {
        NONE,
        COCOSTUDIO
    };
    
    virtual bool parseConfig(ConfigType type, const std::string& str) = 0;
    
    virtual void rootObject(Ref* /*obj*/) {}
    
    virtual void unrootObject(Ref* /*obj*/) {}
    
    virtual void removeObjectProxy(Ref* obj) {}
    
    virtual void garbageCollect() {}
};


NS_CC_END

#endif /* CCScriptSupport_h */
