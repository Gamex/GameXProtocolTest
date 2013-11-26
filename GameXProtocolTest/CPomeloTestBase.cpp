//
//  CPomeloTestBase.cpp
//  GameXProtocolTest
//
//  Created by 马 俊 on 13-11-25.
//  Copyright (c) 2013年 马 俊. All rights reserved.
//

#include "CPomeloTestBase.h"
#include "CCPomelo.h"


bool CPomeloTestBase::onEnter()
{
    return 0 == POMELO->connect(m_addr.c_str(), m_port);
}



bool CPomeloTestBase::onExit()
{
    delete POMELO;
	return true;
}



void CPomeloTestBase::update()
{
    ITestCase::update();
    POMELO->dispatchCallbacks(0);
}
