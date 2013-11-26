//
//  ITestCase.cpp
//  GameXProtocolTest
//
//  Created by 马 俊 on 13-11-25.
//  Copyright (c) 2013年 马 俊. All rights reserved.
//

#include "ITestCase.h"


void ITestCase::addTask(TASK_FUNC f)
{
    if (f)
    {
        m_tasks.push(f);
    }
}


ITestCase::TASK_FUNC ITestCase::popTask()
{
    if (m_tasks.size() == 0)
    {
        return TASK_FUNC();
    }
    TASK_FUNC f = m_tasks.front();
    m_tasks.pop();
    return f;
}



void ITestCase::update()
{
    switch (getTaskState()) {
        case ITestCase::TASK_NONE:
        {
            TASK_FUNC f = popTask();
            if (f)
            {
                setTaskState(TASK_RUNNING);
                f();
            }
            else
            {
                setOver();
            }
            break;
        }
        case ITestCase::TASK_RUNNING:
            break;
        case ITestCase::TASK_OK:
            printf("Task pass!!! Name: %s\n", getTaskName().c_str());
            setTaskState(TASK_NONE);
            break;
        case ITestCase::TASK_FAIL:
            printf("Task failed!!! Name: %s\n", getTaskName().c_str());
            setTaskState(TASK_NONE);
            break;
        default:
            break;
    }
}


