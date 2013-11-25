//
//  CTestLogin.h
//  GameXProtocolTest
//
//  Created by 马 俊 on 13-11-25.
//  Copyright (c) 2013年 马 俊. All rights reserved.
//

#ifndef __GameXProtocolTest__CTestLogin__
#define __GameXProtocolTest__CTestLogin__

#include "CPomeloTestBase.h"

class CTestLogin
: public CPomeloTestBase
{
public:
    virtual bool onEnter() override;
    virtual bool onExit() override;
    
    virtual bool test() override;
};

#endif /* defined(__GameXProtocolTest__CTestLogin__) */
