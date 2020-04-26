//
//  ccMacros.h
//  Cocos2d-x-Framework
//
//  Created by David on 2020/4/21.
//  Copyright © 2020 David. All rights reserved.
//

#ifndef ccMacros_h
#define ccMacros_h

#include <string>

#ifndef CCASSERT
#if COCOS2D_DEBUG > 0
    #if CC_ENABLE_SCRIPT_BINDING
    extern bool CC_DLL cc_assert_script_compatible(const char *msg);
    #define CCASSERT(cond, msg) do {                              \
          if (!(cond)) {                                          \
            if (!cc_assert_script_compatible(msg) && strlen(msg)) \
                        \
            CC_ASSERT(cond);                                      \
          } \
        } while (0)
    #else
    #define CCASSERT(cond, msg) CC_ASSERT(cond)
    #endif
#else
    #define CCASSERT(cond, msg)
#endif

#include "Config.h"

#endif /* ccMacros_h */
#endif
