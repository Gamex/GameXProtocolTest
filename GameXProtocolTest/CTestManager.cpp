//
//  CTestManager.cpp
//  GameXProtocolTest
//
//  Created by 马 俊 on 13-11-25.
//  Copyright (c) 2013年 马 俊. All rights reserved.
//

#include "CTestManager.h"
#include "ITestCase.h"
#include <unistd.h> 

IMPLEMENT_SINGLETON(CTestManager);

CTestManager::CTestManager()
{
}



CTestManager::~CTestManager()
{
}



bool CTestManager::addCase(ITestCase* cs)
{
    m_cases.push_back(cs);
	return true;
}



void CTestManager::run()
{
    auto it = m_cases.begin();
    for (; it != m_cases.end(); ++it)
    {
        (*it)->onEnter();
        while (!(*it)->isOver())
        {
            (*it)->update();
            sleep(0);
        }
        (*it)->onExit();
    }
    printf("DONE~~~~!");
}



