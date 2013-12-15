//
//  ITestCase.h
//  GameXProtocolTest
//
//  Created by 马 俊 on 13-11-25.
//  Copyright (c) 2013年 马 俊. All rights reserved.
//

#ifndef __GameXProtocolTest__ITestCase__
#define __GameXProtocolTest__ITestCase__

#include <functional>
#include <queue>
#include <string>

class ITestCase
{
public:
    enum TASK_STATE
    {
        TASK_NONE,
        TASK_RUNNING,
        TASK_OK,
        TASK_FAIL,
    };
    
    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;
    
    
    virtual void update();
    virtual void setOver(){ m_isOver = true; }
    virtual bool isOver(){ return m_isOver; }
    
    typedef std::function<void(void)> TASK_FUNC;
    virtual void addTask(TASK_FUNC f);
    virtual TASK_FUNC popTask();
    
    virtual void setTaskName(const std::string& name) {
        printf("Task begin-----> Name: %s\n", name.c_str());
        m_curTaskName = name;
    }
    virtual std::string getTaskName() { return m_curTaskName; }
    virtual void setTaskState(TASK_STATE s){ m_taskState = s; }
    virtual TASK_STATE getTaskState(){ return m_taskState; }

protected:
    
private:
    std::queue<TASK_FUNC> m_tasks;
    std::string m_curTaskName;
    TASK_STATE m_taskState = TASK_NONE;
    
    bool m_isOver = false;
};

#endif /* defined(__GameXProtocolTest__ITestCase__) */
