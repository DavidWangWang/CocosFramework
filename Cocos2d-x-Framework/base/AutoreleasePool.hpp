//
//  AutoreleasePool.hpp
//  Cocos2d-x-Framework
//
//  Created by David on 2020/4/22.
//  Copyright © 2020 David. All rights reserved.
//

#ifndef AutoreleasePool_hpp
#define AutoreleasePool_hpp

#include <stdio.h>
#include "PlatformDefine-ios.h"
#include "PlatformMacros.h"
#include <string>
#include "Ref.hpp"
#include "ccMacros.h"
#include <vector>

NS_CC_BEGIN

class CC_DLL AutoreleasePool
{
public:
    
    AutoreleasePool();
    
    AutoreleasePool(const std::string &name);
    
    ~AutoreleasePool();
  
    void addObject(Ref *object);
    void clear();
   
    #if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
        /**
         * Whether the autorelease pool is doing `clear` operation.
         *
         * @return True if autorelease pool is clearing, false if not.
         *
         * @js NA
         * @lua NA
         */
        bool isClearing() const { return _isClearing; };
    #endif
    
    bool contains(Ref *object) const;
    
    void dump();
    
private:
    
    std::vector<Ref *> _manageObjectArray;
    std::string _name;
    
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
        /**
         *  The flag for checking whether the pool is doing `clear` operation.
         */
    bool _isClearing;
#endif
    
};




NS_CC_END






#endif /* AutoreleasePool_hpp */
