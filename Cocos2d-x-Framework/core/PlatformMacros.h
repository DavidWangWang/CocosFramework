//
//  CCPlatformMacros.h
//  Cocos2d-x-Framework
//
//  Created by David on 2020/4/13.
//  Copyright © 2020 David. All rights reserved.
//

#ifndef CCPlatformMacros_h
#define CCPlatformMacros_h



#ifdef __cplusplus
    #define NS_CC_BEGIN  namespace cocos2d {
    #define NS_CC_END    }
    #define USING_NS_CC  using namespace cocos2d
    #define NS_CC   ::cocos2d
#else
    #define NS_CC_BEGIN
    #define NS_CC_END
    #define USING_NS_CC
    #define NS_CC
#endif

#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
    #define CC_DEPRECATED_ATTRIBUTE __attribute__((deprecated))
#endif

#define CCLOGINFO(format,...)   do {} while (0)
#define CCLOG(format, ...)      //cocos2d::log(format, ##__VA_ARGS__)


#endif /* CCPlatformMacros_h */
