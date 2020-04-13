//
//  Ref.hpp
//  CocosFramework
//
//  Created by David on 2020/4/13.
//  Copyright © 2020 David. All rights reserved.
//

#ifndef Ref_hpp
#define Ref_hpp
#include "PlatformDefine-ios.h"
#include "Config.h"
#include "PlatformMacros.h"

#include <stdio.h>

#define CC_REF_LEAK_DETECTION 0

NS_CC_BEGIN

class Ref;

// abstract class
class CC_DLL Clonable
{
public:
    // return a copy of the Ref
    virtual Clonable* clone() const = 0;
    
    virtual ~Clonable() {};
    
};


class CC_DLL Ref
{
public:
    
    void retain();
    
    void release();
    
    Ref* autorelease();
    // 返回引用计数
    unsigned int getReferenceCount() const;
    
protected:
    
    Ref();
    
public:
    
   virtual ~Ref();
    
protected:
    
    unsigned int _referenceCount;
    
    friend class AutoreleasePool;
    
#if CC_ENABLE_SCRIPT_BINDING
public:
    
    unsigned int _ID;
    int _luaID;
    void* _scriptObject;
    bool _rooted;
    
#endif

#if CC_REF_LEAK_DETECTION
public:
    static void printLeaks();
#endif
};

class Node;

typedef void (Ref::*SEL_CallFunc)();
typedef void (Ref::*SEL_CallFuncN)(Node*);
typedef void (Ref::*SEL_CallFuncND)(Node*, void*);
typedef void (Ref::*SEL_CallFuncO)(Ref*);
typedef void (Ref::*SEL_MenuHandler)(Ref*);
typedef void (Ref::*SEL_SCHEDULE)(float);

#define CC_CALLFUNC_SELECTOR(_SELECTOR) static_cast<cocos2d::SEL_CallFunc>(&_SELECTOR);
#define CC_CALLFUNCN_SELECTOR(_SELECTOR) static_cast<cocos2d::SEL_CallFuncN>(&_SELECTOR)
#define CC_CALLFUNCND_SELECTOR(_SELECTOR) static_cast<cocos2d::SEL_CallFuncND>(&_SELECTOR)
#define CC_CALLFUNCO_SELECTOR(_SELECTOR) static_cast<cocos2d::SEL_CallFuncO>(&_SELECTOR)
#define CC_MENU_SELECTOR(_SELECTOR) static_cast<cocos2d::SEL_MenuHandler>(&_SELECTOR)
#define CC_SCHEDULE_SELECTOR(_SELECTOR) static_cast<cocos2d::SEL_SCHEDULE>(&_SELECTOR)

// Deprecated
#define callfunc_selector(_SELECTOR) CC_CALLFUNC_SELECTOR(_SELECTOR)
#define callfuncN_selector(_SELECTOR) CC_CALLFUNCN_SELECTOR(_SELECTOR)
#define callfuncND_selector(_SELECTOR) CC_CALLFUNCND_SELECTOR(_SELECTOR)
#define callfuncO_selector(_SELECTOR) CC_CALLFUNCO_SELECTOR(_SELECTOR)
#define menu_selector(_SELECTOR) CC_MENU_SELECTOR(_SELECTOR)
#define schedule_selector(_SELECTOR) CC_SCHEDULE_SELECTOR(_SELECTOR)


NS_CC_END

#endif /* Ref_hpp */
