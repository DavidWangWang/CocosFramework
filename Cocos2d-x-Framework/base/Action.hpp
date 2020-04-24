//
//  Action.hpp
//  Cocos2d-x-Framework
//
//  Created by David on 2020/4/21.
//  Copyright © 2020 David. All rights reserved.
//

#ifndef Action_hpp
#define Action_hpp

#include <stdio.h>
#include <string>
#include "Ref.hpp"
#include "CCScriptSupport.hpp"

NS_CC_BEGIN

class Node;

class CC_DLL Action : public Ref, public Clonable
{
public:

    static const int INVALID_TAG = -1;

    virtual std::string description() const;

    virtual Action* clone() const
    {
        CC_ASSERT(0);
        return nullptr;
    };

    virtual Action* reverse() const
    {
        CC_ASSERT(0);
        return nullptr;
    };

    virtual bool isDone() const;

    /** Called before the action start. It will also set the target.
    *
    * @param target A certain target.
    */
    virtual void startWithTarget(Node *target);
    /**
    * Called after the action has finished. It will set the 'target' to nil.
    * IMPORTANT: You should never call "Action::stop()" manually. Instead, use: "target->stopAction(action);".
    */
    virtual void stop();

    virtual void step(float dt);

    virtual void update(float time);

    Node* getTarget() { return _target; };

    void setTarget(Node *target) { _target = target; }


private:

    Node *_target;
};



NS_CC_END

#endif /* Action_hpp */
