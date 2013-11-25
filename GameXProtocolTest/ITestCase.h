//
//  ITestCase.h
//  GameXProtocolTest
//
//  Created by 马 俊 on 13-11-25.
//  Copyright (c) 2013年 马 俊. All rights reserved.
//

#ifndef __GameXProtocolTest__ITestCase__
#define __GameXProtocolTest__ITestCase__

class ITestCase
{
public:
    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;
    
    virtual bool test() = 0;
};

#endif /* defined(__GameXProtocolTest__ITestCase__) */
