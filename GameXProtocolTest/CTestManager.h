//
//  CTestManager.h
//  GameXProtocolTest
//
//  Created by 马 俊 on 13-11-25.
//  Copyright (c) 2013年 马 俊. All rights reserved.
//

#ifndef __GameXProtocolTest__CTestManager__
#define __GameXProtocolTest__CTestManager__

#include "CSingleton.h"
#include <vector>

using namespace std;


#define ADD_CASE(__CLASS_NAME__) \
class __addCase##__CLASS_NAME__\
{\
    public:\
    __addCase##__CLASS_NAME__()\
    {\
        TEST_MGR->addCase(new __CLASS_NAME__);\
    }\
};\
static __addCase##__CLASS_NAME__ ____add_case;


class ITestCase;

class CTestManager
: public CSingleton<CTestManager>
{
public:
    CTestManager();
    ~CTestManager();

    bool addCase(ITestCase* cs);
    void run();

protected:
    vector<ITestCase*> m_cases;
};


#define TEST_MGR        (CTestManager::getInstance())

#endif /* defined(__GameXProtocolTest__CTestManager__) */
