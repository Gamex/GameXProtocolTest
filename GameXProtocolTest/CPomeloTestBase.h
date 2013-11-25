//
//  CPomeloTestBase.h
//  GameXProtocolTest
//
//  Created by 马 俊 on 13-11-25.
//  Copyright (c) 2013年 马 俊. All rights reserved.
//

#ifndef __GameXProtocolTest__CPomeloTestBase__
#define __GameXProtocolTest__CPomeloTestBase__

#include "ITestCase.h"

#include "jansson.h"
#include "pomelo.h"

#include <string>



using namespace std;

class CPomeloTestBase
: public ITestCase
{
public:
    virtual bool onEnter() override;
    virtual bool onExit() override;
    
protected:
    pc_client_t *client = nullptr;
    string m_addr = "127.0.0.1";
    int m_port = 3017;
};


#endif /* defined(__GameXProtocolTest__CPomeloTestBase__) */
