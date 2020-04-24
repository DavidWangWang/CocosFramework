//
//  PoolManager.hpp
//  Cocos2d-x-Framework
//
//  Created by David on 2020/4/21.
//  Copyright © 2020 David. All rights reserved.
//

#ifndef PoolManager_hpp
#define PoolManager_hpp

#include <stdio.h>
#include "PlatformDefine-ios.h"
#include "PoolManager.hpp"
#include "PlatformMacros.h"
#include "AutoreleasePool.hpp"
#include <vector>

NS_CC_BEGIN

class CC_DLL PoolManager
{
public:
    CC_DEPRECATED_ATTRIBUTE static PoolManager* sharePoolManager() {
        return getInstance();
    };
    static PoolManager* getInstance();
    CC_DEPRECATED_ATTRIBUTE static void purgePoolManager() {
        destroyInstance();
    }
    static void destroyInstance();
    
    AutoreleasePool *getCurrentPool() const;
    bool isObjectInPool(Ref *ref) const;
    
    friend class AutoreleasePool;
    
private:
    PoolManager();
    ~PoolManager();
//
    void push(AutoreleasePool *pool);
    void pop();
    
    static PoolManager* s_singleInstance;
    
    std::vector<AutoreleasePool *> _releasePoolStack;
};

NS_CC_END


#endif /* PoolManager_hpp */
