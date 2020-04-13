//
//  Ref.cpp
//  CocosFramework
//
//  Created by David on 2020/4/13.
//  Copyright © 2020 David. All rights reserved.
//

#include "Ref.hpp"
#include "CCScriptSupport.h"
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
    
    
#endif
    
}

NS_CC_END


